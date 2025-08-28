#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations
class QStackedWidget;
class QPushButton;
class QLabel;
class LibraryService;
class Person;

// Khai báo trước các widget con
class DashboardWidget;
class BookCatalogWidget;
class TransactionWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor nhận vào LibraryService
    explicit MainWindow(LibraryService& service, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots để chuyển đổi giữa các màn hình
    void showDashboard();
    void showBookCatalog();
    void showTransactionManagement();
    void logout();

private:
    void setupUI();
    void createPages();
    void setupConnections();
    void updateUserInfo();

    // --- UI Components ---
    QStackedWidget* centralStack;
    QLabel* userInfoLabel;
    QPushButton* dashboardButton;
    QPushButton* booksButton;
    QPushButton* transactionsButton;
    QPushButton* logoutButton;

    // --- Pages ---
    DashboardWidget* dashboardPage;
    BookCatalogWidget* bookCatalogPage;
    TransactionWidget* transactionPage;

    // --- Backend Service ---
    LibraryService& libraryService;
};

#endif // MAINWINDOW_H
