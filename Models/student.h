#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

class Student : public Person {
public:
    Student(const QString& name, const QString& email, const QString& password, const QString& studentId);

    // --- Getters ---
    QString getMajor() const { return major; }
    int getYear() const { return year; }
    double getFines() const { return totalFines; }

    // --- Setters ---
    void setMajor(const QString& newMajor) { major = newMajor; }
    void setYear(int newYear) { year = newYear; }
    void addFine(double amount);
    void payFine(double amount);

    // --- Ghi đè phương thức ảo ---
    QString getUserId() const override { return studentId; }
    QString getUserType() const override { return "Student"; }
    int getMaxBooksAllowed() const override { return 5; }

private:
    QString studentId;
    QString major;      // Chuyên ngành
    int year;           // Năm học
    double totalFines;  // Tổng tiền phạt chưa thanh toán
};

#endif // STUDENT_H
