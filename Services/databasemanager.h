#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QDebug>
#include <memory>
#include <mutex>

// Forward declarations
class Person;
class Book;
class Transaction;

class DatabaseManager {
private:
    // Singleton Pattern Implementation
    static std::unique_ptr<DatabaseManager> instance;
    static std::mutex mtx;
    QSqlDatabase database;

    DatabaseManager(); // Constructor riêng tư

public:
    // Xóa copy constructor và toán tử gán
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // Lấy instance duy nhất của class
    static DatabaseManager& getInstance();

    // Khởi tạo và kết nối database
    bool initialize(const QString& dbPath = "library.db");
    void close();

    // --- Các hàm thao tác với Database ---

    // Lấy dữ liệu
    QSqlQuery getUserDataByEmail(const QString& email);
    QSqlQuery getUserDataById(const QString& userId);
    QSqlQuery getBookDataByIsbn(const QString& isbn);
    QSqlQuery getAllBooksData();
    QSqlQuery getTransactionsDataByUserId(const QString& userId);
    QSqlQuery getActiveTransactionData(const QString& userId, const QString& bookIsbn);
    QSqlQuery getAllTransactionsData();
    QSqlQuery getTransactionById(int transactionId);
    QSqlQuery executeQuery(const QString& queryString, const QVariantList& params = {});

    // Lấy thống kê
    int getBookCount();
    int getUserCount();
    int getActiveTransactionCount();

    // Lưu/Cập nhật dữ liệu
    bool saveNewUser(const Person& user, const QString& hashedPassword); // Sửa: Nhận mật khẩu đã băm
    bool saveNewBook(const Book& book);
    bool updateBook(const Book& book, int newAvailableCopies); // Sửa: Tách riêng available copies
    bool deleteBook(const QString& isbn);
    bool saveNewTransaction(const Transaction& transaction);
    bool updateBookCopies(const QString& isbn, int available);
    bool updateTransactionOnReturn(int transactionId);
};

#endif // DATABASEMANAGER_H
