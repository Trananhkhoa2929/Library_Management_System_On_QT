#ifndef BOOK_H
#define BOOK_H

#include <QString>

// Trạng thái của sách
enum class BookStatus {
    Available, // Có sẵn
    Borrowed   // Đã được mượn
};

class Book {
public:
    // Constructors
    Book();
    Book(QString isbn, QString title, QString author, int totalCopies = 1);

    // --- Getters ---
    QString getIsbn() const { return isbn; }
    QString getTitle() const { return title; }
    QString getAuthor() const { return author; }
    BookStatus getStatus() const { return status; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }

    // --- Setters ---
    void setTitle(const QString& newTitle) { title = newTitle; }
    void setAuthor(const QString& newAuthor) { author = newAuthor; }
    void setTotalCopies(int count);
    void setAvailableCopies(int count);

    // --- Logic chính ---
    bool isAvailable() const;
    bool borrowBook(); // Trả về true nếu mượn thành công
    bool returnBook(); // Trả về true nếu trả thành công

private:
    QString isbn;          // Mã số sách (không thay đổi)
    QString title;
    QString author;
    BookStatus status;
    int totalCopies;       // Tổng số bản sách
    int availableCopies;   // Số bản có sẵn
};

#endif // BOOK_H
