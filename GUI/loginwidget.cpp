#include "loginwidget.h"
#include "Services/libraryservice.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

LoginWidget::LoginWidget(LibraryService& service, QWidget *parent)
    : QWidget(parent), libraryService(service) {
    setupUI();
    setupConnections();
}

LoginWidget::~LoginWidget() = default;

void LoginWidget::onLoginAttempt() {
    QString email = loginEmailEdit->text().trimmed();
    QString password = loginPasswordEdit->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập email và mật khẩu.");
        return;
    }

    // Sửa: Gọi hàm login mới và kiểm tra kết quả bool
    if (libraryService.login(email, password)) {
        statusLabel->setText("Đăng nhập thành công!");
        emit loginSuccessful(); // Phát tín hiệu thành công
    } else {
        statusLabel->setText("Sai email hoặc mật khẩu.");
        QMessageBox::critical(this, "Đăng nhập thất bại", "Email hoặc mật khẩu không chính xác.");
    }
}

void LoginWidget::onRegisterAttempt() {
    QString name = regNameEdit->text().trimmed();
    QString email = regEmailEdit->text().trimmed();
    QString password = regPasswordEdit->text();
    QString confirmPassword = regConfirmPasswordEdit->text();
    QString userType = regUserTypeCombo->currentText();

    if (name.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Lỗi Đăng ký", "Vui lòng điền đầy đủ các trường bắt buộc.");
        return;
    }
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Lỗi Đăng ký", "Mật khẩu và xác nhận mật khẩu không khớp.");
        return;
    }
    if (password.length() < 6) {
        QMessageBox::warning(this, "Lỗi Đăng ký", "Mật khẩu phải có ít nhất 6 ký tự.");
        return;
    }

    if (libraryService.registerUser(name, email, password, userType)) {
        QMessageBox::information(this, "Đăng ký thành công",
                                 "Tài khoản của bạn đã được tạo thành công!\n"
                                 "Vui lòng chuyển qua tab Đăng nhập để tiếp tục.");
        // Xóa form và chuyển qua tab đăng nhập
        regNameEdit->clear();
        regEmailEdit->clear();
        regPasswordEdit->clear();
        regConfirmPasswordEdit->clear();
        tabWidget->setCurrentIndex(0);
        loginEmailEdit->setText(email);
        loginPasswordEdit->setFocus();
    } else {
        QMessageBox::critical(this, "Đăng ký thất bại",
                              "Không thể tạo tài khoản. Email có thể đã tồn tại.");
    }
}


void LoginWidget::setupUI() {
    setWindowTitle("EduLibrary - Đăng nhập");
    setFixedSize(400, 450);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    auto titleLabel = new QLabel("EduLibrary Manager", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c5aa0;");
    mainLayout->addWidget(titleLabel);

    tabWidget = new QTabWidget(this);

    // --- Login Tab ---
    auto loginTab = new QWidget();
    auto loginLayout = new QFormLayout(loginTab);
    loginLayout->setSpacing(15);
    loginEmailEdit = new QLineEdit();
    loginEmailEdit->setPlaceholderText("your.email@example.com");
    loginPasswordEdit = new QLineEdit();
    loginPasswordEdit->setPlaceholderText("••••••••");
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Đăng nhập");
    loginButton->setStyleSheet("padding: 8px; background-color: #2c5aa0; color: white; border-radius: 4px;");

    loginLayout->addRow("Email:", loginEmailEdit);
    loginLayout->addRow("Mật khẩu:", loginPasswordEdit);
    loginLayout->addWidget(loginButton);

    // --- Register Tab ---
    auto registerTab = new QWidget();
    auto registerLayout = new QFormLayout(registerTab);
    registerLayout->setSpacing(15);
    regNameEdit = new QLineEdit();
    regEmailEdit = new QLineEdit();
    regPasswordEdit = new QLineEdit();
    regPasswordEdit->setEchoMode(QLineEdit::Password);
    regConfirmPasswordEdit = new QLineEdit();
    regConfirmPasswordEdit->setEchoMode(QLineEdit::Password);
    regUserTypeCombo = new QComboBox();
    regUserTypeCombo->addItems({"Student", "Faculty"});
    registerButton = new QPushButton("Đăng ký");

    registerLayout->addRow("Họ và Tên:", regNameEdit);
    registerLayout->addRow("Email:", regEmailEdit);
    registerLayout->addRow("Mật khẩu:", regPasswordEdit);
    registerLayout->addRow("Xác nhận Mật khẩu:", regConfirmPasswordEdit);
    registerLayout->addRow("Bạn là:", regUserTypeCombo);
    registerLayout->addWidget(registerButton);

    tabWidget->addTab(loginTab, "Đăng nhập");
    tabWidget->addTab(registerTab, "Đăng ký");
    mainLayout->addWidget(tabWidget);

    statusLabel = new QLabel("", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statusLabel);
}

void LoginWidget::setupConnections() {
    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginAttempt);
    connect(registerButton, &QPushButton::clicked, this, &LoginWidget::onRegisterAttempt);
    connect(loginPasswordEdit, &QLineEdit::returnPressed, this, &LoginWidget::onLoginAttempt);
}
