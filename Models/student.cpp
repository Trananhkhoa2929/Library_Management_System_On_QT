#include "student.h"
#include <QDebug>

Student::Student(const QString& name, const QString& email, const QString& password, const QString& studentId)
    : Person(name, email, password), studentId(studentId) {
    // Khởi tạo các giá trị mặc định cho sinh viên
    major = "Chưa xác định";
    year = 1;
    totalFines = 0.0;
}

// Thêm tiền phạt cho sinh viên
void Student::addFine(double amount) {
    if (amount > 0) {
        totalFines += amount;
    } else {
        qWarning() << "Fine amount must be positive.";
    }
}

// Sinh viên thanh toán tiền phạt
void Student::payFine(double amount) {
    if (amount <= 0) {
        qWarning() << "Payment amount must be positive.";
        return;
    }
    if (amount > totalFines) {
        qWarning() << "Payment amount exceeds total fines.";
        return;
    }
    totalFines -= amount;
}
