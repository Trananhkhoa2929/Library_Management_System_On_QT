#include "mainwindow.h"
#include "dashboardwidget.h"
#include "bookCatalogwidget.h"
#include "transactionwidget.h"
#include "Services/libraryservice.h"
#include "Models/person.h"

#include <QToolBar>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(LibraryService& service, QWidget *parent)
    : QMainWindow(parent), libraryService(service) {
    setWindowTitle("EduLibrary Manager");
    setMinimumSize(1024, 768);

    setupUI();
    createPages();
    setupConnections();

    // Mặc định hiển thị Dashboard khi khởi động
    showDashboard();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUI() {
    // --- Thanh công cụ (Toolbar) ---
    auto toolBar = new QToolBar("Main Toolbar", this);
    addToolBar(toolBar);
    toolBar->setMovable(false);

    dashboardButton = new QPushButton("Bảng điều khiển");
    booksButton = new QPushButton("Quản lý Sách");
    transactionsButton = new QPushButton("Giao dịch");
    toolBar->addWidget(dashboardButton);
    toolBar->addWidget(booksButton);
    toolBar->addWidget(transactionsButton);

    // Spacer để đẩy các mục sau sang phải
    auto spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->addWidget(spacer);

    userInfoLabel = new QLabel(this);
    toolBar->addWidget(userInfoLabel);
    updateUserInfo(); // Cập nhật tên người dùng

    logoutButton = new QPushButton("Đăng xuất");
    toolBar->addWidget(logoutButton);

    // --- Khu vực trung tâm ---
    centralStack = new QStackedWidget(this);
    setCentralWidget(centralStack);
}

void MainWindow::createPages() {
    // Tạo các trang chức năng và thêm vào StackedWidget
    dashboardPage = new DashboardWidget(libraryService, this);
    bookCatalogPage = new BookCatalogWidget(libraryService, this);
    transactionPage = new TransactionWidget(libraryService, this);
    centralStack->addWidget(dashboardPage);
    centralStack->addWidget(bookCatalogPage);
    centralStack->addWidget(transactionPage);
}

void MainWindow::setupConnections() {
    connect(dashboardButton, &QPushButton::clicked, this, &MainWindow::showDashboard);
    connect(booksButton, &QPushButton::clicked, this, &MainWindow::showBookCatalog);
    connect(transactionsButton, &QPushButton::clicked, this, &MainWindow::showTransactionManagement);
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::logout);

    // --- KẾT NỐI TÍN HIỆU TỪ SERVICE ĐẾN CÁC WIDGET ---
    connect(&libraryService, &LibraryService::dataChanged, bookCatalogPage, &BookCatalogWidget::refreshData);
    connect(&libraryService, &LibraryService::dataChanged, transactionPage, &TransactionWidget::refreshData);

    // Cũng nên kết nối với Dashboard để cập nhật số liệu
    connect(&libraryService, &LibraryService::dataChanged,
            dashboardPage, &DashboardWidget::updateStatistics);

}

void MainWindow::updateUserInfo() {
    Person* currentUser = libraryService.getCurrentUser();
    if (currentUser) {
        userInfoLabel->setText(QString("Xin chào, %1").arg(currentUser->getName()));
    }
}

void MainWindow::showDashboard() {
    centralStack->setCurrentWidget(dashboardPage);
    statusBar()->showMessage("Hiển thị Bảng điều khiển", 3000);
}

void MainWindow::showBookCatalog() {
    centralStack->setCurrentWidget(bookCatalogPage);
    statusBar()->showMessage("Hiển thị trang Quản lý Sách", 3000);
}

void MainWindow::showTransactionManagement() {
    centralStack->setCurrentWidget(transactionPage);
    statusBar()->showMessage("Hiển thị trang Quản lý Giao dịch", 3000);
}

void MainWindow::logout() {
    // Phát tín hiệu để main.cpp có thể xử lý việc hiển thị lại cửa sổ đăng nhập
    QMessageBox::information(this, "Đăng xuất", "Bạn đã đăng xuất thành công.");
    close(); // Đóng cửa sổ chính
    // Trong một ứng dụng thực tế, bạn sẽ phát một tín hiệu để mở lại LoginWidget
    QApplication::quit(); // Tạm thời thoát ứng dụng
}
