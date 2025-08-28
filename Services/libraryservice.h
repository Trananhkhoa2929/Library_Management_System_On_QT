#ifndef LIBRARYSERVICE_H
#define LIBRARYSERVICE_H

#include <QObject>
#include <memory>
#include <vector>
#include <QSqlQuery>

// Forward declarations
class Person;
class Book;
class Transaction;

class LibraryService : public QObject {
    Q_OBJECT

public:
    LibraryService();
    ~LibraryService(); // SỬA LỖI: Thêm destructor declaration

    // đọc sách từ .csv
    void seedDatabaseFromResources();

    // --- Chức năng chính ---
    bool registerUser(const QString& name, const QString& email, const QString& password, const QString& userType);

    // Xác thực người dùng
    bool login(const QString& email, const QString& password);
    void logout();
    Person* getCurrentUser() const { return currentUser.get(); }

    // Quản lý sách
    std::vector<std::unique_ptr<Book>> getAllBooks();
    std::vector<std::unique_ptr<Book>> searchBooks(const QString& searchTerm);
    bool addBook(const QString& isbn, const QString& title, const QString& author, int totalCopies);
    bool updateBook(const QString& isbn, const QString& title, const QString& author, int totalCopies);
    bool deleteBook(const QString& isbn);

    // Quản lý mượn/trả
    bool borrowBook(const QString& userId, const QString& bookIsbn);
    bool returnBook(const QString& transactionId);
    std::vector<std::unique_ptr<Transaction>> getAllTransactions();
    std::vector<std::unique_ptr<Transaction>> getCurrentUserTransactions();

    // Thống kê và tác vụ nền
    void checkOverdueBooks();
    int getTotalBooksCount();
    int getTotalUsersCount();
    int getActiveTransactionsCount();
    int getOverdueTransactionsCount();

signals:
    void dataChanged();

private:
    // Helper để chuyển đổi QSqlQuery thành Object
    std::unique_ptr<Person> createUserFromQuery(QSqlQuery& query);
    std::unique_ptr<Book> createBookFromQuery(QSqlQuery& query);
    std::unique_ptr<Transaction> createTransactionFromQuery(QSqlQuery& query);

    void setCurrentUser(std::unique_ptr<Person> user);

    std::unique_ptr<Person> currentUser;
};

#endif // LIBRARYSERVICE_H
