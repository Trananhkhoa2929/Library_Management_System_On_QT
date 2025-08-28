#include "databasemanager.h"
#include "Models/person.h"
#include "Models/book.h"
#include "Models/transaction.h"
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

// Khởi tạo các biến static
std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;
std::mutex DatabaseManager::mtx;

DatabaseManager::DatabaseManager() {
    // Constructor để trống
}

DatabaseManager& DatabaseManager::getInstance() {
    std::lock_guard<std::mutex> lock(mtx);
    if (instance == nullptr) {
        instance.reset(new DatabaseManager());
    }
    return *instance;
}

bool DatabaseManager::initialize(const QString& dbPath) {
    if (QSqlDatabase::contains("mainConnection")) {
        database = QSqlDatabase::database("mainConnection");
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE", "mainConnection");
    }

    // SỬA ĐỔI: Thay đổi đường dẫn lưu database
    // Thay vì lưu vào AppData, chúng ta sẽ lưu vào cùng thư mục
    // với file thực thi (.exe) của chương trình.
    QString appDir = QCoreApplication::applicationDirPath();
    QString fullPath = appDir + "/" + dbPath; // dbPath là "library.db"

    database.setDatabaseName(fullPath);

    if (!database.open()) {
        qCritical() << "Database connection failed:" << database.lastError().text();
        return false;
    }

    qInfo() << "Database connected successfully at" << fullPath;

    // Bật foreign keys để đảm bảo toàn vẹn dữ liệu
    executeQuery("PRAGMA foreign_keys = ON;");

    // Tạo bảng nếu chưa tồn tại
    executeQuery("CREATE TABLE IF NOT EXISTS users (id TEXT PRIMARY KEY, name TEXT, email TEXT UNIQUE, password TEXT, user_type TEXT);");
    executeQuery("CREATE TABLE IF NOT EXISTS books (isbn TEXT PRIMARY KEY, title TEXT, author TEXT, total_copies INTEGER, available_copies INTEGER);");
    executeQuery("CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id TEXT, book_isbn TEXT, borrow_date TEXT, due_date TEXT, return_date TEXT, status TEXT, FOREIGN KEY(user_id) REFERENCES users(id), FOREIGN KEY(book_isbn) REFERENCES books(isbn));");

    return true;
}

void DatabaseManager::close() {
    if (database.isOpen()) {
        database.close();
    }
}

QSqlQuery DatabaseManager::executeQuery(const QString& queryString, const QVariantList& params) {
    QSqlQuery query(database);
    query.prepare(queryString);
    for (int i = 0; i < params.size(); ++i) {
        query.bindValue(i, params.at(i));
    }
    if (!query.exec()) {
        qWarning() << "Query failed:" << query.lastError().text();
        qWarning() << "Failing query:" << queryString;
    }
    return query;
}

// --- Implement các hàm truy vấn ---

QSqlQuery DatabaseManager::getUserDataByEmail(const QString& email) {
    return executeQuery("SELECT * FROM users WHERE email = ?", {email});
}

QSqlQuery DatabaseManager::getBookDataByIsbn(const QString& isbn) {
    return executeQuery("SELECT * FROM books WHERE isbn = ?", {isbn});
}

QSqlQuery DatabaseManager::getAllBooksData() {
    return executeQuery("SELECT * FROM books ORDER BY title");
}

QSqlQuery DatabaseManager::getTransactionsDataByUserId(const QString& userId) {
    return executeQuery("SELECT * FROM transactions WHERE user_id = ? ORDER BY borrow_date DESC", {userId});
}

QSqlQuery DatabaseManager::getActiveTransactionData(const QString& userId, const QString& bookIsbn) {
    return executeQuery("SELECT * FROM transactions WHERE user_id = ? AND book_isbn = ? AND status = 'Active'", {userId, bookIsbn});
}

// Sửa: Nhận mật khẩu đã được băm
bool DatabaseManager::saveNewUser(const Person& user, const QString& hashedPassword) {
    QSqlQuery query = executeQuery("INSERT INTO users (id, name, email, password, user_type) VALUES (?, ?, ?, ?, ?)",
                                   {user.getUserId(), user.getName(), user.getEmail(), hashedPassword, user.getUserType()});
    return query.isActive();
}

bool DatabaseManager::saveNewBook(const Book& book) {
    QSqlQuery query = executeQuery("INSERT INTO books (isbn, title, author, total_copies, available_copies) VALUES (?, ?, ?, ?, ?)",
                                   {book.getIsbn(), book.getTitle(), book.getAuthor(), book.getTotalCopies(), book.getAvailableCopies()});
    return query.isActive();
}

bool DatabaseManager::saveNewTransaction(const Transaction& transaction) {
    QSqlQuery query = executeQuery("INSERT INTO transactions (user_id, book_isbn, borrow_date, due_date, status) VALUES (?, ?, ?, ?, 'Active')",
                                   {transaction.getUserId(), transaction.getBookIsbn(), transaction.getBorrowDate().toString(Qt::ISODate), transaction.getDueDate().toString(Qt::ISODate)});
    return query.isActive();
}

bool DatabaseManager::updateBookCopies(const QString& isbn, int availableCopies) {
    QSqlQuery query = executeQuery("UPDATE books SET available_copies = ? WHERE isbn = ?",
                                   {availableCopies, isbn});
    return query.isActive();
}

bool DatabaseManager::updateTransactionOnReturn(int transactionId) {
    QSqlQuery query = executeQuery("UPDATE transactions SET return_date = ?, status = 'Completed' WHERE id = ?",
                                   {QDateTime::currentDateTime().toString(Qt::ISODate), transactionId});
    return query.isActive();
}

// Sửa: Tách riêng available copies để logic được tập trung hơn
bool DatabaseManager::updateBook(const Book& book, int newAvailableCopies) {
    QSqlQuery query = executeQuery("UPDATE books SET title = ?, author = ?, total_copies = ?, available_copies = ? WHERE isbn = ?",
                                   {book.getTitle(), book.getAuthor(), book.getTotalCopies(), newAvailableCopies, book.getIsbn()});
    return query.isActive();
}

bool DatabaseManager::deleteBook(const QString& isbn) {
    // Kiểm tra xem sách có đang được mượn không
    QSqlQuery checkQuery = executeQuery("SELECT COUNT(*) FROM transactions WHERE book_isbn = ? AND (status = 'Active' OR status = 'Overdue')", {isbn});
    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        qWarning() << "Delete book failed: Book is currently borrowed.";
        return false;
    }

    QSqlQuery query = executeQuery("DELETE FROM books WHERE isbn = ?", {isbn});
    return query.isActive();
}

int DatabaseManager::getBookCount() {
    QSqlQuery query = executeQuery("SELECT COUNT(*) FROM books");
    return query.next() ? query.value(0).toInt() : 0;
}

int DatabaseManager::getUserCount() {
    QSqlQuery query = executeQuery("SELECT COUNT(*) FROM users");
    return query.next() ? query.value(0).toInt() : 0;
}

int DatabaseManager::getActiveTransactionCount() {
    QSqlQuery query = executeQuery("SELECT COUNT(*) FROM transactions WHERE status = 'Active'");
    return query.next() ? query.value(0).toInt() : 0;
}

QSqlQuery DatabaseManager::getAllTransactionsData() {
    // Sử dụng JOIN để lấy thêm tên người dùng và tên sách hiệu quả
    QString queryString = R"(
        SELECT t.*, u.name AS user_name, b.title AS book_title
        FROM transactions t
        LEFT JOIN users u ON t.user_id = u.id
        LEFT JOIN books b ON t.book_isbn = b.isbn
        ORDER BY t.borrow_date DESC
    )";

    return executeQuery(queryString);
}

QSqlQuery DatabaseManager::getTransactionById(int transactionId) {
    return executeQuery("SELECT * FROM transactions WHERE id = ?", {transactionId});
}

// THÊM ĐỊNH NGHĨA CHO HÀM MỚI
QSqlQuery DatabaseManager::getUserDataById(const QString& userId) {
    return executeQuery("SELECT * FROM users WHERE id = ?", {userId});
}
