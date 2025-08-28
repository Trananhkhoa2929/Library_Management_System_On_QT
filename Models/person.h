#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <vector>

class Person {
public:
    Person(const QString& name, const QString& email, const QString& password);
    virtual ~Person() {}

    // --- Getters ---
    QString getName() const { return name; }
    QString getEmail() const { return email; }
    const std::vector<int>& getTransactionHistory() const { return transactionIds; }

    // --- Quản lý giao dịch ---
    void addTransaction(int transactionId);
    bool canBorrowMore(int currentBorrows) const;

    // --- Phương thức ảo ---
    virtual QString getUserId() const = 0;
    virtual QString getUserType() const = 0;
    virtual int getMaxBooksAllowed() const = 0;

protected:
    QString name;
    QString email;
    QString password;
    std::vector<int> transactionIds; // Lưu ID của tất cả các giao dịch (cả cũ và mới)
};

#endif // PERSON_H
