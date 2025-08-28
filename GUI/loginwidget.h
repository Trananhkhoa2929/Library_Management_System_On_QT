#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

// Forward declarations
class QLineEdit;
class QPushButton;
class QTabWidget;
class QLabel;
class QComboBox;
class LibraryService;

class LoginWidget : public QWidget {
    Q_OBJECT

public:
    explicit LoginWidget(LibraryService& service, QWidget *parent = nullptr);
    ~LoginWidget();

signals:
    // Sửa: Tín hiệu không cần gửi userId, vì các widget khác có thể lấy từ service
    void loginSuccessful();

private slots:
    void onLoginAttempt();
    void onRegisterAttempt();

private:
    void setupUI();
    void setupConnections();

    // --- UI Components ---
    QTabWidget* tabWidget;
    // Login tab
    QLineEdit* loginEmailEdit;
    QLineEdit* loginPasswordEdit;
    QPushButton* loginButton;
    // Register tab
    QLineEdit* regNameEdit;
    QLineEdit* regEmailEdit;
    QLineEdit* regPasswordEdit;
    QLineEdit* regConfirmPasswordEdit;
    QComboBox* regUserTypeCombo;
    QPushButton* registerButton;
    // Status
    QLabel* statusLabel;

    // --- Backend Service ---
    LibraryService& libraryService;
};

#endif // LOGINWIDGET_H
