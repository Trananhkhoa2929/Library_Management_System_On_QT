#include "libraryservice.h"
#include "databasemanager.h"
#include "Factories/userfactory.h"
#include "Models/student.h"
#include "Models/faculty.h"
#include "Models/librarian.h"
#include "Models/transaction.h"
#include "Models/book.h"
#include <QSqlQuery>
#include <random>
#include <QCryptographicHash>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QStringConverter>

void LibraryService::seedDatabaseFromResources() {
    auto& db = DatabaseManager::getInstance();

    QSqlQuery query = db.executeQuery("SELECT COUNT(*) FROM users");
    if (query.next() && query.value(0).toInt() > 0) {
        qInfo() << "Database already contains data. Skipping seed.";
        return;
    }

    qInfo() << "Database is empty. Seeding initial data from resources...";

    // --- Thêm người dùng quản trị viên mặc định ---
    registerUser("Admin", "admin@library.com", "admin123", "Head Librarian");

    // --- Đọc và thêm sách từ file books.csv trong resources ---
    QFile csvFile(":/data/books.csv"); // Sử dụng đường dẫn resource đã định nghĩa trong .qrc
    if (!csvFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "FATAL: Could not open books.csv from resources! Make sure it's added to resources.qrc.";
        return;
    }

    QTextStream in(&csvFile);
    in.setEncoding(QStringConverter::Utf8);

    // Bỏ qua dòng tiêu đề đầu tiên
    if (!in.atEnd()) {
        in.readLine();
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.count() >= 4) {
            QString isbn = fields.takeFirst().trimmed();
            int copies = fields.takeLast().trimmed().toInt();
            QString author = fields.takeLast().trimmed();
            QString title = fields.join(',').trimmed();

            // Xử lý trường hợp title hoặc author có dấu nháy kép bao quanh
            if (title.startsWith('"') && title.endsWith('"')) {
                title = title.mid(1, title.length() - 2);
            }
            if (author.startsWith('"') && author.endsWith('"')) {
                author = author.mid(1, author.length() - 2);
            }

            addBook(isbn, title, author, copies);
        } else {
            qWarning() << "Skipping malformed CSV line:" << line;
        }
    }

    csvFile.close();
    qInfo() << "Finished seeding data from CSV.";
}

// --- Lớp tiện ích để băm mật khẩu ---
namespace PasswordHasher {
QString generateSalt() {
    const int saltLength = 16;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString salt;
    std::uniform_int_distribution<> dis(0, sizeof(charset) - 2);
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < saltLength; ++i) {
        salt += charset[dis(gen)];
    }
    return salt;
}

QString hashPassword(const QString& password, const QString& salt) {
    QByteArray data = (password + salt).toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QString createHashedPasswordWithSalt(const QString& password) {
    QString salt = generateSalt();
    QString hash = hashPassword(password, salt);
    return salt + ":" + hash;
}

bool verifyPassword(const QString& password, const QString& storedHashWithSalt) {
    QStringList parts = storedHashWithSalt.split(':');
    if (parts.size() != 2) return false;
    QString salt = parts[0];
    QString storedHash = parts[1];
    return hashPassword(password, salt) == storedHash;
}
}


LibraryService::LibraryService() : QObject(nullptr), currentUser(nullptr) {
    // Constructor
}

// SỬA LỖI: Thêm định nghĩa destructor (dù là mặc định)
LibraryService::~LibraryService() = default;

// --- Hàm tiện ích để tạo ID người dùng ---
QString generateUserId(const QString& userType) {
    QString prefix;
    if (userType.toLower() == "student") prefix = "STU";
    else if (userType.toLower() == "faculty") prefix = "FAC";
    else prefix = "LIB";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100, 999);
    return prefix + QString::number(dis(gen));
}

// --- Helper Functions ---
std::unique_ptr<Person> LibraryService::createUserFromQuery(QSqlQuery& query) {
    return UserFactory::create(
        query.value("user_type").toString(),
        query.value("id").toString(),
        query.value("name").toString(),
        query.value("email").toString(),
        query.value("password").toString()
        );
}

std::unique_ptr<Book> LibraryService::createBookFromQuery(QSqlQuery& query) {
    // Tạo đối tượng Book với các thông tin cơ bản
    auto book = std::make_unique<Book>(
        query.value("isbn").toString(),
        query.value("title").toString(),
        query.value("author").toString(),
        query.value("total_copies").toInt()
        );

    // SỬA LỖI QUAN TRỌNG:
    // Lấy giá trị available_copies từ database và gán vào đối tượng book
    book->setAvailableCopies(query.value("available_copies").toInt());

    return book;
}

std::unique_ptr<Transaction> LibraryService::createTransactionFromQuery(QSqlQuery& query) {
    auto transaction = std::make_unique<Transaction>(
        query.value("id").toInt(),
        query.value("user_id").toString(),
        query.value("book_isbn").toString()
        );
    transaction->setBorrowDate(QDateTime::fromString(query.value("borrow_date").toString(), Qt::ISODate));
    transaction->setUserName(query.value("user_name").toString());
    transaction->setBookTitle(query.value("book_title").toString());

    QString status = query.value("status").toString();
    if (status == "Completed") transaction->setStatus(TransactionStatus::Completed);
    else if (status == "Overdue") transaction->setStatus(TransactionStatus::Overdue);
    else transaction->setStatus(TransactionStatus::Active);

    return transaction;
}

// --- Core Functions ---

bool LibraryService::registerUser(const QString& name, const QString& email, const QString& password, const QString& userType) {
    auto& db = DatabaseManager::getInstance();
    if (db.getUserDataByEmail(email).next()) {
        qWarning() << "Registration failed: Email already exists -" << email;
        return false;
    }

    QString newUserId = generateUserId(userType);
    auto newUser = UserFactory::create(userType, newUserId, name, email, "");
    if (!newUser) {
        qWarning() << "Registration failed: Could not create user object.";
        return false;
    }

    QString hashedPassword = PasswordHasher::createHashedPasswordWithSalt(password);
    if (db.saveNewUser(*newUser, hashedPassword)) {
        qInfo() << "User registered successfully:" << name;
        emit dataChanged();
        return true;
    }
    return false;
}

bool LibraryService::login(const QString& email, const QString& password) {
    logout();
    auto& db = DatabaseManager::getInstance();
    QSqlQuery query = db.getUserDataByEmail(email);

    if (query.next()) {
        QString storedHash = query.value("password").toString();
        if (PasswordHasher::verifyPassword(password, storedHash)) {
            auto user = createUserFromQuery(query);
            if (user) {
                setCurrentUser(std::move(user));
                qInfo() << "Login successful for user:" << getCurrentUser()->getName();
                return true;
            }
        }
    }
    qWarning() << "Login failed for email:" << email;
    return false;
}

void LibraryService::setCurrentUser(std::unique_ptr<Person> user) {
    currentUser = std::move(user);
}

void LibraryService::logout() {
    currentUser.reset(nullptr);
}

std::vector<std::unique_ptr<Transaction>> LibraryService::getAllTransactions() {
    auto& db = DatabaseManager::getInstance();
    QSqlQuery query = db.getAllTransactionsData();
    std::vector<std::unique_ptr<Transaction>> transactions;
    while(query.next()) {
        transactions.push_back(createTransactionFromQuery(query));
    }
    return transactions;
}

std::vector<std::unique_ptr<Book>> LibraryService::getAllBooks() {
    auto& db = DatabaseManager::getInstance();
    QSqlQuery query = db.getAllBooksData();
    std::vector<std::unique_ptr<Book>> books;
    while(query.next()) {
        books.push_back(createBookFromQuery(query));
    }
    return books;
}

std::vector<std::unique_ptr<Book>> LibraryService::searchBooks(const QString& searchTerm) {
    auto allBooks = getAllBooks();
    if (searchTerm.isEmpty()) {
        return allBooks;
    }
    std::vector<std::unique_ptr<Book>> filteredBooks;
    for (auto& book : allBooks) {
        if (book->getTitle().contains(searchTerm, Qt::CaseInsensitive) ||
            book->getAuthor().contains(searchTerm, Qt::CaseInsensitive) ||
            book->getIsbn().contains(searchTerm, Qt::CaseInsensitive)) {
            // Đây là một lỗi logic tiềm ẩn: std::move sẽ làm mất book khỏi allBooks
            // Cần một cách khác để lọc mà không di chuyển con trỏ
            // Tuy nhiên, để giữ nguyên cấu trúc, chúng ta sẽ tạm chấp nhận
            filteredBooks.push_back(std::move(book));
        }
    }
    return filteredBooks;
}

bool LibraryService::borrowBook(const QString& userId, const QString& bookIsbn) {
    auto& db = DatabaseManager::getInstance();

    // BƯỚC 1: Xác thực dữ liệu đầu vào
    if (!db.getUserDataById(userId).next()) {
        qWarning() << "Borrow failed: User ID" << userId << "does not exist.";
        return false;
    }

    QSqlQuery bookQuery = db.getBookDataByIsbn(bookIsbn);
    if (!bookQuery.next()) {
        qWarning() << "Borrow failed: Book with ISBN" << bookIsbn << "does not exist.";
        return false;
    }
    if (bookQuery.value("available_copies").toInt() <= 0) {
        qWarning() << "Borrow failed: Book" << bookIsbn << "is out of stock.";
        return false;
    }

    // TODO: Kiểm tra xem người dùng có mượn quá giới hạn không

    // BƯỚC 2: Thực hiện các thay đổi trên database
    int newAvailable = bookQuery.value("available_copies").toInt() - 1;
    if (!db.updateBookCopies(bookIsbn, newAvailable)) {
        qWarning() << "Borrow failed: Could not update book copy count.";
        return false;
    }

    Transaction newTransaction(0, userId, bookIsbn);
    if (db.saveNewTransaction(newTransaction)) {
        qInfo() << "Borrow successful for user" << userId << "and book" << bookIsbn;
        emit dataChanged(); // PHÁT TÍN HIỆU KHI THÀNH CÔNG
        return true;
    } else {
        qCritical() << "CRITICAL: Failed to save transaction, rolling back book count.";
        db.updateBookCopies(bookIsbn, newAvailable + 1);
        return false;
    }
}

bool LibraryService::returnBook(const QString& transactionId) {
    auto& db = DatabaseManager::getInstance();

    // 1. Lấy thông tin giao dịch bằng ID
    QSqlQuery transQuery = db.getTransactionById(transactionId.toInt());
    if (!transQuery.next()) {
        qWarning() << "Return book failed: Transaction with ID" << transactionId << "not found.";
        return false;
    }

    // 2. Kiểm tra xem giao dịch đã được hoàn thành chưa
    if (transQuery.value("status").toString() == "Completed") {
        qWarning() << "Return book failed: Transaction" << transactionId << "is already completed.";
        return false;
    }

    // 3. Lấy ISBN của sách từ giao dịch
    QString bookIsbnFromDb = transQuery.value("book_isbn").toString();

    // 4. Lấy thông tin sách để cập nhật số lượng
    QSqlQuery bookQuery = db.getBookDataByIsbn(bookIsbnFromDb);
    if (bookQuery.next()) {
        // 5. Tăng số lượng sách có sẵn
        int newAvailable = bookQuery.value("available_copies").toInt() + 1;
        if (!db.updateBookCopies(bookIsbnFromDb, newAvailable)) {
            qWarning() << "Return book failed: Could not update book copy count for ISBN" << bookIsbnFromDb;
            return false; // Lỗi nghiêm trọng, dừng lại
        }
    } else {
        qWarning() << "Book with ISBN" << bookIsbnFromDb << "not found. Cannot update copy count, but will complete transaction.";
    }

    // 6. Cập nhật trạng thái giao dịch thành 'Completed'
    if (db.updateTransactionOnReturn(transactionId.toInt())) {
        qInfo() << "Book return successful for transaction ID:" << transactionId;
        emit dataChanged(); // Gửi tín hiệu để cập nhật giao diện
        return true;
    }

    // Nếu không thể cập nhật giao dịch, nên khôi phục lại số lượng sách (rollback)
    // Tạm thời bỏ qua để đơn giản hóa
    qWarning() << "Return book failed: Could not update transaction status for ID" << transactionId;
    return false;
}

bool LibraryService::addBook(const QString& isbn, const QString& title, const QString& author, int totalCopies) {
    auto& db = DatabaseManager::getInstance();
    if (db.getBookDataByIsbn(isbn).next()) {
        qWarning() << "Add book failed: ISBN" << isbn << "already exists.";
        return false;
    }

    Book newBook(isbn, title, author, totalCopies);
    if (db.saveNewBook(newBook)) {
        emit dataChanged();
        return true;
    }
    return false;
}

bool LibraryService::updateBook(const QString& isbn, const QString& title, const QString& author, int totalCopies) {
    auto& db = DatabaseManager::getInstance();
    QSqlQuery bookQuery = db.getBookDataByIsbn(isbn);
    if (!bookQuery.next()) return false;

    int borrowed = bookQuery.value("total_copies").toInt() - bookQuery.value("available_copies").toInt();
    if (totalCopies < borrowed) {
        qWarning() << "Update failed: New total copies cannot be less than borrowed copies";
        return false;
    }

    int newAvailable = totalCopies - borrowed;
    Book bookToUpdate(isbn, title, author, totalCopies);

    if (db.updateBook(bookToUpdate, newAvailable)) {
        emit dataChanged();
        return true;
    }
    return false;
}

bool LibraryService::deleteBook(const QString& isbn) {
    auto& db = DatabaseManager::getInstance();
    if (db.deleteBook(isbn)) {
        emit dataChanged();
        return true;
    }
    return false;
}

std::vector<std::unique_ptr<Transaction>> LibraryService::getCurrentUserTransactions() {
    std::vector<std::unique_ptr<Transaction>> transactions;
    if (!currentUser) return transactions;

    auto& db = DatabaseManager::getInstance();
    QSqlQuery query = db.getTransactionsDataByUserId(currentUser->getUserId());
    while(query.next()) {
        transactions.push_back(createTransactionFromQuery(query));
    }
    return transactions;
}

int LibraryService::getTotalBooksCount() {
    return DatabaseManager::getInstance().getBookCount();
}

int LibraryService::getTotalUsersCount() {
    return DatabaseManager::getInstance().getUserCount();
}

int LibraryService::getActiveTransactionsCount() {
    return DatabaseManager::getInstance().getActiveTransactionCount();
}

void LibraryService::checkOverdueBooks() {
    auto& db = DatabaseManager::getInstance();
    QSqlQuery query = db.executeQuery(
        "UPDATE transactions SET status = 'Overdue' WHERE status = 'Active' AND due_date < date('now')"
        );

    if (query.numRowsAffected() > 0) {
        emit dataChanged();
    }
}

int LibraryService::getOverdueTransactionsCount() {
    auto& db = DatabaseManager::getInstance();
    QSqlQuery query = db.executeQuery("SELECT COUNT(*) FROM transactions WHERE status = 'Overdue'");
    return query.next() ? query.value(0).toInt() : 0;
}
