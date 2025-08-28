#ifndef USERMANAGEMENTWIDGET_H
#define USERMANAGEMENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QDateEdit>
#include <QSplitter>
#include <QTabWidget>

class LibraryService;
class NotificationService;
class Person;

class UserManagementWidget : public QWidget {
public:
    explicit UserManagementWidget(LibraryService* libService,
                                  NotificationService* notifService,
                                  QWidget *parent = nullptr);

private slots:
    void onAddUserClicked();
    void onEditUserClicked();
    void onDeleteUserClicked();
    void onSearchTextChanged();
    void onUserTypeChanged();
    void onUserTableSelectionChanged();
    void onRefreshClicked();
    void onSendNotificationClicked();
    void onExportUsersClicked();
    void onViewUserDetailsClicked();

private:
    void setupUI();
    void setupUserTable();
    void setupUserForm();
    void loadUsers();
    void clearUserForm();
    void populateUserForm(const Person* user);
    bool validateUserForm();
    void filterUsers();
    void updateUserCount();
    void showUserDetails(int userId);

    // ✅ ADD MISSING METHODS
    void setupUserDetailsTab();
    void setupUserTypeSpecificFields();
    void showUserTypeFields();

    // UI Components - keep all existing ones...
    QSplitter* mainSplitter;
    QTabWidget* rightTabWidget;

    // Left side - User list and search
    QLineEdit* searchEdit;
    QComboBox* userTypeFilterCombo;
    QComboBox* statusFilterCombo;
    QTableWidget* userTable;
    QLabel* userCountLabel;

    // Right side - User form tab
    QGroupBox* userFormGroup;
    QLineEdit* userIdEdit;
    QLineEdit* nameEdit;
    QLineEdit* emailEdit;
    QLineEdit* passwordEdit;
    QComboBox* userTypeCombo;
    QLineEdit* phoneEdit;
    QLineEdit* addressEdit;
    QDateEdit* dateOfBirthEdit;

    // User type specific fields
    QWidget* studentFields;
    QLineEdit* studentIdEdit;
    QLineEdit* majorEdit;
    QComboBox* yearCombo;
    QLineEdit* gpaEdit;

    QWidget* facultyFields;
    QLineEdit* employeeIdEdit;
    QLineEdit* departmentEdit;
    QLineEdit* positionEdit;
    QLineEdit* yearsOfServiceEdit;
    QLineEdit* officeRoomEdit;

    QWidget* librarianFields;
    QLineEdit* libEmployeeIdEdit;
    QComboBox* shiftCombo;
    QLineEdit* specializationEdit;
    QLineEdit* salaryEdit;

    // Action buttons
    QPushButton* addUserBtn;
    QPushButton* editUserBtn;
    QPushButton* deleteUserBtn;
    QPushButton* refreshBtn;
    QPushButton* exportBtn;
    QPushButton* clearFormBtn;
    QPushButton* sendNotificationBtn;
    QPushButton* viewDetailsBtn;

    // User details tab
    QWidget* userDetailsWidget;
    QLabel* detailsUserInfo;
    QTableWidget* userBorrowHistoryTable;
    QLabel* userStatsLabel;

    // Services
    LibraryService* libraryService;
    NotificationService* notificationService;

    // Current selected user
    QString currentUserId;
    bool isEditMode;
};

#endif // USERMANAGEMENTWIDGET_H
