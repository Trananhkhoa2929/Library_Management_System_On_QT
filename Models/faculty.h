#ifndef FACULTY_H
#define FACULTY_H

#include "person.h"

class Faculty : public Person {
public:
    Faculty(const QString& name, const QString& email, const QString& password, const QString& employeeId);

    // --- Getters ---
    QString getDepartment() const { return department; }
    QString getPosition() const { return position; }

    // --- Setters ---
    void setDepartment(const QString& newDept) { department = newDept; }
    void setPosition(const QString& newPos) { position = newPos; }

    // --- Ghi đè phương thức ảo ---
    QString getUserId() const override { return employeeId; }
    QString getUserType() const override { return "Faculty"; }
    int getMaxBooksAllowed() const override { return 15; }

private:
    QString employeeId;
    QString department; // Khoa
    QString position;   // Chức vụ
};

#endif // FACULTY_H
