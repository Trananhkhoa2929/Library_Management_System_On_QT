#ifndef USERFACTORY_H
#define USERFACTORY_H

#include <memory>
#include <QString>

// Forward declarations để tránh phải include toàn bộ file header
class Person;
class Student;
class Faculty;
class Librarian;

class UserFactory {
public:
    /**
     * @brief Tạo một đối tượng Person (Student, Faculty, hoặc Librarian)
     * @param userType Chuỗi định danh loại người dùng (ví dụ: "Student", "Faculty")
     * @param id Mã định danh (Mã SV, Mã GV)
     * @param name Tên người dùng
     * @param email Email
     * @param password Mật khẩu
     * @return Con trỏ thông minh đến đối tượng Person đã được tạo, hoặc nullptr nếu thất bại.
     */
    static std::unique_ptr<Person> create(
        const QString& userType,
        const QString& id,
        const QString& name,
        const QString& email,
        const QString& password
        );
};

#endif // USERFACTORY_H
