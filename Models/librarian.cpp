#include "librarian.h"

Librarian::Librarian(const QString& name, const QString& email, const QString& password, const QString& employeeId)
    : Person(name, email, password), employeeId(employeeId) {
    // Giá trị mặc định khi một thủ thư mới được tạo
    hireDate = QDateTime::currentDateTime();
    headLibrarian = false; // Mặc định không phải là thủ thư chính
}

// Trả về loại người dùng, có phân biệt thủ thư chính
QString Librarian::getUserType() const {
    if (headLibrarian) {
        return "Head Librarian";
    }
    return "Librarian";
}

// Tính toán số năm đã làm việc dựa trên ngày vào làm
double Librarian::getYearsOfService() const {
    qint64 daysWorked = hireDate.daysTo(QDateTime::currentDateTime());
    // Chia cho 365.25 để tính cả năm nhuận
    return static_cast<double>(daysWorked) / 365.25;
}
