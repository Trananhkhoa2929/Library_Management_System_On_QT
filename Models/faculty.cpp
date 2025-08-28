#include "Models/faculty.h"

Faculty::Faculty(const QString& name, const QString& email, const QString& password, const QString& employeeId)
    : Person(name, email, password), employeeId(employeeId) {
    // Khởi tạo các giá trị mặc định cho giảng viên
    department = "Chưa xác định";
    position = "Giảng viên";
}
