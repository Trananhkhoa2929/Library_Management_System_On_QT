#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "person.h"
#include <QDateTime>

class Librarian : public Person {
public:
    Librarian(const QString& name, const QString& email, const QString& password, const QString& employeeId);

    // --- Getters ---
    QDateTime getHireDate() const { return hireDate; }
    bool isHeadLibrarian() const { return headLibrarian; }

    // --- Setters ---
    void setAsHeadLibrarian(bool isHead) { headLibrarian = isHead; }

    // --- Ghi đè các phương thức ảo ---
    QString getUserId() const override { return employeeId; }
    QString getUserType() const override;
    int getMaxBooksAllowed() const override { return 10; } // Thủ thư cũng có thể mượn sách

    // --- Phương thức đặc thù ---
    double getYearsOfService() const; // Tính số năm kinh nghiệm

private:
    QString employeeId;
    QDateTime hireDate;      // Ngày vào làm
    bool headLibrarian; // true nếu là thủ thư chính (admin)
};

#endif // LIBRARIAN_H
