#ifndef BOOKCATALOGWIDGET_H
#define BOOKCATALOGWIDGET_H

#include <QWidget>
#include <memory>
#include <vector>

// Forward declarations
class QTableWidget;
class QLineEdit;
class QPushButton;
class QSpinBox;
class LibraryService;
class Book;

class BookCatalogWidget : public QWidget {
    Q_OBJECT
public:
    explicit BookCatalogWidget(LibraryService& service, QWidget *parent = nullptr);

public slots:
    void refreshData(); // Sửa: Đổi tên thành một slot chung để nhận tín hiệu

private slots:
    void onSearchTextChanged(const QString& text);
    void onAddBook();
    void onEditBook();
    void onDeleteBook();
    void onTableItemSelected();

private:
    void setupUI();
    void setupConnections();
    void populateTable(const std::vector<std::unique_ptr<Book>>& books);
    void clearForm();

    // --- UI Components ---
    QTableWidget* bookTable;
    QLineEdit* searchEdit;
    QPushButton* addButton;
    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* refreshButton;

    // Form chi tiết sách (để thêm/sửa)
    QLineEdit* isbnEdit;
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;
    QSpinBox* totalCopiesSpinBox;

    // --- Backend Service ---
    LibraryService& libraryService;
};

#endif // BOOKCATALOGWIDGET_H
