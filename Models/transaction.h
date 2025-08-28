#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

// Loại giao dịch
enum class TransactionType {
    Borrow, // Mượn sách
    Return  // Trả sách
};

// Trạng thái giao dịch
enum class TransactionStatus {
    Active,    // Đang diễn ra (sách đang được mượn)
    Completed, // Đã hoàn tất (sách đã được trả)
    Overdue    // Quá hạn
};

class Transaction {
public:
    Transaction(int id, const QString& userId, const QString& bookIsbn);

    // --- Getters ---
    int getId() const { return transactionId; }
    QString getUserId() const { return userId; }
    QString getBookIsbn() const { return bookIsbn; }
    QDateTime getBorrowDate() const { return borrowDate; }
    QDateTime getDueDate() const { return dueDate; }
    QDateTime getReturnDate() const { return returnDate; }
    TransactionStatus getStatus() const { return status; }

    QString getUserName() const { return userName; }
    QString getBookTitle() const { return bookTitle; }

    // Setters
    void setStatus(TransactionStatus newStatus) { status = newStatus; }
    void setBorrowDate(const QDateTime& date) { borrowDate = date; }
    // --- Setters cho dữ liệu JOIN ---
    void setUserName(const QString& name) { userName = name; }
    void setBookTitle(const QString& title) { bookTitle = title; }

    // --- Logic ---
    void completeTransaction(); // Đánh dấu giao dịch là đã hoàn thành (khi trả sách)
    void checkForOverdue();     // Kiểm tra xem có bị quá hạn không

private:
    int transactionId;
    QString userId;      // ID của người mượn
    QString bookIsbn;    // ISBN của sách được mượn
    QDateTime borrowDate;
    QDateTime dueDate;
    QDateTime returnDate;
    TransactionStatus status;

    QString userName;
    QString bookTitle;
};

#endif // TRANSACTION_H
