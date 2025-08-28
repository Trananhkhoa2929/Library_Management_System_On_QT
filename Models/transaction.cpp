#include "transaction.h"

// Giả sử thời gian mượn sách tiêu chuẩn là 14 ngày
const int LOAN_DURATION_DAYS = 14;

Transaction::Transaction(int id, const QString& userId, const QString& bookIsbn)
    : transactionId(id), userId(userId), bookIsbn(bookIsbn) {
    // Thiết lập thời gian và trạng thái ban đầu cho giao dịch
    borrowDate = QDateTime::currentDateTime();
    dueDate = borrowDate.addDays(LOAN_DURATION_DAYS);
    status = TransactionStatus::Active;
    // returnDate sẽ không hợp lệ cho đến khi sách được trả
}

// Hoàn thành một giao dịch (khi trả sách)
void Transaction::completeTransaction() {
    returnDate = QDateTime::currentDateTime();
    status = TransactionStatus::Completed;
}

// Kiểm tra và cập nhật trạng thái nếu giao dịch bị quá hạn
void Transaction::checkForOverdue() {
    if (status == TransactionStatus::Active && QDateTime::currentDateTime() > dueDate) {
        status = TransactionStatus::Overdue;
    }
}
