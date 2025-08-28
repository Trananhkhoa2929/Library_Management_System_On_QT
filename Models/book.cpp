#include "book.h"
#include <QDebug>

// Constructor mặc định
Book::Book()
    : isbn(""), title(""), author(""), status(BookStatus::Available), totalCopies(0), availableCopies(0) {
}

// Constructor với các tham số cần thiết
Book::Book(QString isbn, QString title, QString author, int totalCopies)
    : isbn(isbn), title(title), author(author), status(BookStatus::Available), totalCopies(totalCopies), availableCopies(totalCopies) {
    // Đảm bảo số lượng sách không phải là số âm
    if (totalCopies < 0) {
        this->totalCopies = 0;
        this->availableCopies = 0;
    }
}

// Cập nhật tổng số bản sách
void Book::setTotalCopies(int count) {
    if (count < 0) {
        qWarning() << "Total copies cannot be negative.";
        return;
    }

    // Tính toán số sách đang được mượn
    int borrowedCount = totalCopies - availableCopies;
    if (count < borrowedCount) {
        qWarning() << "New total copies cannot be less than the number of currently borrowed books.";
        return;
    }

    totalCopies = count;
    availableCopies = totalCopies - borrowedCount; // Cập nhật lại số sách có sẵn
}

// Kiểm tra xem sách có sẵn để mượn không
bool Book::isAvailable() const {
    return availableCopies > 0;
}

// Xử lý hành động mượn sách
bool Book::borrowBook() {
    if (isAvailable()) {
        availableCopies--;
        if (availableCopies == 0) {
            status = BookStatus::Borrowed; // Cập nhật trạng thái nếu hết sách
        }
        return true; // Mượn thành công
    }
    return false; // Không thể mượn
}

// Xử lý hành động trả sách
bool Book::returnBook() {
    if (availableCopies < totalCopies) {
        availableCopies++;
        status = BookStatus::Available; // Sách lại có sẵn
        return true; // Trả thành công
    }
    return false; // Lỗi: không thể có nhiều sách hơn tổng số
}

void Book::setAvailableCopies(int count) {
    availableCopies = count;
}
