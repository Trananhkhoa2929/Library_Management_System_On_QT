#include "person.h"

Person::Person(const QString& name, const QString& email, const QString& password)
    : name(name), email(email), password(password) {
    // Hàm khởi tạo lớp cơ sở
}

// Thêm một ID giao dịch vào lịch sử của người dùng
void Person::addTransaction(int transactionId) {
    transactionIds.push_back(transactionId);
}

// Kiểm tra xem người dùng có thể mượn thêm sách không
bool Person::canBorrowMore(int currentBorrows) const {
    // So sánh số sách đang mượn với giới hạn cho phép của từng loại người dùng
    return currentBorrows < getMaxBooksAllowed();
}
