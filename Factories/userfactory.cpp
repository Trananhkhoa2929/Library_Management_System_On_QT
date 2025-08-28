#include "userfactory.h"
#include "Models/student.h"
#include "Models/faculty.h"
#include "Models/librarian.h"
#include <QDebug>

std::unique_ptr<Person> UserFactory::create(
    const QString& userType,
    const QString& id,
    const QString& name,
    const QString& email,
    const QString& password)
{
    // Chuyển đổi chuỗi userType về chữ thường để so sánh không phân biệt hoa/thường
    QString typeLower = userType.toLower();

    if (typeLower == "student") {
        return std::make_unique<Student>(name, email, password, id);
    }
    else if (typeLower == "faculty") {
        return std::make_unique<Faculty>(name, email, password, id);
    }
    else if (typeLower == "librarian") {
        return std::make_unique<Librarian>(name, email, password, id);
    }
    else if (typeLower == "head librarian") {
        // Xử lý trường hợp đặc biệt cho thủ thư chính
        auto librarian = std::make_unique<Librarian>(name, email, password, id);
        librarian->setAsHeadLibrarian(true);
        return librarian;
    }
    else {
        qWarning() << "UserFactory: Không nhận dạng được loại người dùng:" << userType;
        return nullptr; // Trả về con trỏ rỗng nếu không khớp loại nào
    }
}
