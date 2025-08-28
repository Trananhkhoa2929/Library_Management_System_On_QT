#include "usermanagementwidget.h"
#include "Services/libraryservice.h"
#include "Services/notificationservice.h"
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
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFormLayout>
#include <QGridLayout>

UserManagementWidget::UserManagementWidget(LibraryService* libService,
                                          NotificationService* notifService,
                                          QWidget *parent)
    : QWidget(parent)
    , mainSplitter(nullptr)
    , rightTabWidget(nullptr)
    , searchEdit(nullptr)
    , userTypeFilterCombo(nullptr)
    , statusFilterCombo(nullptr)
    , userTable(nullptr)
    , userCountLabel(nullptr)
    , userFormGroup(nullptr)
    , libraryService(libService)
    , notificationService(notifService)
    , currentUserId("")
    , isEditMode(false)
{
    setupUI();
    loadUsers();
}

void UserManagementWidget::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Header
    QLabel* headerLabel = new QLabel("👥 User Management");
    headerLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "    color: #2c5aa0;"
        "    margin-bottom: 15px;"
        "}"
    );
    mainLayout->addWidget(headerLabel);

    // Main content splitter
    mainSplitter = new QSplitter(Qt::Horizontal);
    mainLayout->addWidget(mainSplitter);

    // Left side - User list
    QWidget* leftWidget = new QWidget();
    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);

    // Search and filters
    QHBoxLayout* searchLayout = new QHBoxLayout();

    QLabel* searchLabel = new QLabel("🔍 Search:");
    searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Search by name, email, ID...");
    searchEdit->setStyleSheet("QLineEdit { padding: 6px; border: 1px solid #ddd; border-radius: 4px; }");

    QLabel* typeLabel = new QLabel("Type:");
    userTypeFilterCombo = new QComboBox();
    userTypeFilterCombo->addItems({"All Types", "Student", "Faculty", "Librarian"});

    QLabel* statusLabel = new QLabel("Status:");
    statusFilterCombo = new QComboBox();
    statusFilterCombo->addItems({"All Status", "Active", "Inactive", "Suspended"});

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit, 2);
    searchLayout->addWidget(typeLabel);
    searchLayout->addWidget(userTypeFilterCombo);
    searchLayout->addWidget(statusLabel);
    searchLayout->addWidget(statusFilterCombo);

    leftLayout->addLayout(searchLayout);

    setupUserTable();
    leftLayout->addWidget(userTable);

    // User count and action buttons
    QHBoxLayout* bottomLeftLayout = new QHBoxLayout();
    userCountLabel = new QLabel("Total Users: 0");
    userCountLabel->setStyleSheet("font-weight: bold; color: #666;");
    bottomLeftLayout->addWidget(userCountLabel);

    bottomLeftLayout->addStretch();

    refreshBtn = new QPushButton("🔄 Refresh");
    exportBtn = new QPushButton("📤 Export");
    sendNotificationBtn = new QPushButton("📧 Send Notification");

    refreshBtn->setStyleSheet("QPushButton { padding: 6px 12px; }");
    exportBtn->setStyleSheet("QPushButton { padding: 6px 12px; }");
    sendNotificationBtn->setStyleSheet("QPushButton { padding: 6px 12px; }");

    bottomLeftLayout->addWidget(refreshBtn);
    bottomLeftLayout->addWidget(exportBtn);
    bottomLeftLayout->addWidget(sendNotificationBtn);

    leftLayout->addLayout(bottomLeftLayout);
    mainSplitter->addWidget(leftWidget);

    // Right side - Tabbed interface
    rightTabWidget = new QTabWidget();

    // User form tab
    setupUserForm();
    rightTabWidget->addTab(userFormGroup, "User Form");

    // User details tab
    setupUserDetailsTab();
    rightTabWidget->addTab(userDetailsWidget, "User Details");

    mainSplitter->addWidget(rightTabWidget);

    // Set splitter proportions
    mainSplitter->setSizes({700, 500});

    // Connect signals
    connect(searchEdit, &QLineEdit::textChanged, this, &UserManagementWidget::onSearchTextChanged);
    connect(userTypeFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UserManagementWidget::onUserTypeChanged);
    connect(userTable, &QTableWidget::itemSelectionChanged, this, &UserManagementWidget::onUserTableSelectionChanged);
    connect(addUserBtn, &QPushButton::clicked, this, &UserManagementWidget::onAddUserClicked);
    connect(editUserBtn, &QPushButton::clicked, this, &UserManagementWidget::onEditUserClicked);
    connect(deleteUserBtn, &QPushButton::clicked, this, &UserManagementWidget::onDeleteUserClicked);
    connect(refreshBtn, &QPushButton::clicked, this, &UserManagementWidget::onRefreshClicked);
    connect(exportBtn, &QPushButton::clicked, this, &UserManagementWidget::onExportUsersClicked);
    connect(sendNotificationBtn, &QPushButton::clicked, this, &UserManagementWidget::onSendNotificationClicked);
    connect(clearFormBtn, &QPushButton::clicked, this, &UserManagementWidget::clearUserForm);
    connect(viewDetailsBtn, &QPushButton::clicked, this, &UserManagementWidget::onViewUserDetailsClicked);
}

void UserManagementWidget::setupUserTable() {
    userTable = new QTableWidget();
    userTable->setColumnCount(7);

    QStringList headers = {"User ID", "Name", "Email", "Type", "Status", "Joined", "Last Active"};
    userTable->setHorizontalHeaderLabels(headers);

    // Table styling
    userTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: white;"
        "    alternate-background-color: #f8f9fa;"
        "    selection-background-color: #4a90e2;"
        "    gridline-color: #e0e0e0;"
        "    border: 1px solid #ddd;"
        "}"
        "QTableWidget::item {"
        "    padding: 8px;"
        "    border-bottom: 1px solid #f0f0f0;"
        "}"
        "QHeaderView::section {"
        "    background-color: #f8f9fa;"
        "    padding: 10px;"
        "    border: none;"
        "    font-weight: bold;"
        "    color: #333;"
        "}"
    );

    userTable->setAlternatingRowColors(true);
    userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    userTable->setSelectionMode(QAbstractItemView::SingleSelection);
    userTable->setSortingEnabled(true);

    // Set column widths
    userTable->horizontalHeader()->setStretchLastSection(true);
    userTable->setColumnWidth(0, 100); // User ID
    userTable->setColumnWidth(1, 180); // Name
    userTable->setColumnWidth(2, 220); // Email
    userTable->setColumnWidth(3, 100); // Type
    userTable->setColumnWidth(4, 80);  // Status
    userTable->setColumnWidth(5, 100); // Joined
}

void UserManagementWidget::setupUserForm() {
    userFormGroup = new QGroupBox("User Information");
    userFormGroup->setStyleSheet(
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #ddd;"
        "    border-radius: 8px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 10px 0 10px;"
        "}"
    );

    QVBoxLayout* formLayout = new QVBoxLayout(userFormGroup);

    // Basic user information
    QGridLayout* basicInfoLayout = new QGridLayout();

    int row = 0;

    // User ID (for editing)
    basicInfoLayout->addWidget(new QLabel("User ID:"), row, 0);
    userIdEdit = new QLineEdit();
    userIdEdit->setReadOnly(true);
    userIdEdit->setStyleSheet("QLineEdit { background-color: #f8f9fa; }");
    basicInfoLayout->addWidget(userIdEdit, row++, 1);

    // Name
    basicInfoLayout->addWidget(new QLabel("Full Name *:"), row, 0);
    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Enter full name");
    basicInfoLayout->addWidget(nameEdit, row++, 1);

    // Email
    basicInfoLayout->addWidget(new QLabel("Email *:"), row, 0);
    emailEdit = new QLineEdit();
    emailEdit->setPlaceholderText("user@example.com");
    basicInfoLayout->addWidget(emailEdit, row++, 1);

    // Password
    basicInfoLayout->addWidget(new QLabel("Password *:"), row, 0);
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Minimum 6 characters");
    basicInfoLayout->addWidget(passwordEdit, row++, 1);

    // User Type
    basicInfoLayout->addWidget(new QLabel("User Type *:"), row, 0);
    userTypeCombo = new QComboBox();
    userTypeCombo->addItems({"Student", "Faculty", "Librarian"});
    basicInfoLayout->addWidget(userTypeCombo, row++, 1);

    // Phone
    basicInfoLayout->addWidget(new QLabel("Phone:"), row, 0);
    phoneEdit = new QLineEdit();
    phoneEdit->setPlaceholderText("+1-555-123-4567");
    basicInfoLayout->addWidget(phoneEdit, row++, 1);

    // Address
    basicInfoLayout->addWidget(new QLabel("Address:"), row, 0);
    addressEdit = new QLineEdit();
    addressEdit->setPlaceholderText("Full address");
    basicInfoLayout->addWidget(addressEdit, row++, 1);

    // Date of Birth
    basicInfoLayout->addWidget(new QLabel("Date of Birth:"), row, 0);
    dateOfBirthEdit = new QDateEdit(QDate::currentDate().addYears(-20));
    dateOfBirthEdit->setCalendarPopup(true);
    basicInfoLayout->addWidget(dateOfBirthEdit, row++, 1);

    formLayout->addLayout(basicInfoLayout);

    // User type specific fields
    setupUserTypeSpecificFields();
    formLayout->addWidget(studentFields);
    formLayout->addWidget(facultyFields);
    formLayout->addWidget(librarianFields);

    // Action buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    addUserBtn = new QPushButton("👤 Add User");
    editUserBtn = new QPushButton("✏️ Update User");
    deleteUserBtn = new QPushButton("🗑️ Delete User");
    clearFormBtn = new QPushButton("🧹 Clear Form");
    viewDetailsBtn = new QPushButton("👁️ View Details");

    addUserBtn->setStyleSheet("QPushButton { background-color: #28a745; color: white; padding: 8px 16px; font-weight: bold; }");
    editUserBtn->setStyleSheet("QPushButton { background-color: #ffc107; color: black; padding: 8px 16px; font-weight: bold; }");
    deleteUserBtn->setStyleSheet("QPushButton { background-color: #dc3545; color: white; padding: 8px 16px; font-weight: bold; }");
    clearFormBtn->setStyleSheet("QPushButton { background-color: #6c757d; color: white; padding: 8px 16px; }");
    viewDetailsBtn->setStyleSheet("QPushButton { background-color: #17a2b8; color: white; padding: 8px 16px; }");

    buttonLayout->addWidget(addUserBtn);
    buttonLayout->addWidget(editUserBtn);
    buttonLayout->addWidget(deleteUserBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(viewDetailsBtn);
    buttonLayout->addWidget(clearFormBtn);

    formLayout->addLayout(buttonLayout);

    // Initially show add mode
    editUserBtn->setVisible(false);
    deleteUserBtn->setEnabled(false);

    // Connect user type combo change
    connect(userTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &UserManagementWidget::showUserTypeFields);
}

void UserManagementWidget::setupUserTypeSpecificFields() {
    // Student fields
    studentFields = new QWidget();
    QFormLayout* studentLayout = new QFormLayout(studentFields);
    studentLayout->addRow("Student ID:", studentIdEdit = new QLineEdit());
    studentLayout->addRow("Major:", majorEdit = new QLineEdit());
    yearCombo = new QComboBox();
    yearCombo->addItems({"1", "2", "3", "4", "5", "6"});
    studentLayout->addRow("Year:", yearCombo);
    studentLayout->addRow("GPA:", gpaEdit = new QLineEdit());
    gpaEdit->setPlaceholderText("0.00 - 4.00");
    studentFields->setVisible(true);

    // Faculty fields
    facultyFields = new QWidget();
    QFormLayout* facultyLayout = new QFormLayout(facultyFields);
    facultyLayout->addRow("Employee ID:", employeeIdEdit = new QLineEdit());
    facultyLayout->addRow("Department:", departmentEdit = new QLineEdit());
    facultyLayout->addRow("Position:", positionEdit = new QLineEdit());
    facultyLayout->addRow("Years of Service:", yearsOfServiceEdit = new QLineEdit());
    facultyLayout->addRow("Office Room:", officeRoomEdit = new QLineEdit());
    facultyFields->setVisible(false);

    // Librarian fields
    librarianFields = new QWidget();
    QFormLayout* librarianLayout = new QFormLayout(librarianFields);
    librarianLayout->addRow("Employee ID:", libEmployeeIdEdit = new QLineEdit());
    shiftCombo = new QComboBox();
    shiftCombo->addItems({"Morning", "Afternoon", "Evening"});
    librarianLayout->addRow("Shift:", shiftCombo);
    librarianLayout->addRow("Specialization:", specializationEdit = new QLineEdit());
    librarianLayout->addRow("Salary:", salaryEdit = new QLineEdit());
    salaryEdit->setPlaceholderText("Annual salary");
    librarianFields->setVisible(false);
}

void UserManagementWidget::setupUserDetailsTab() {
    userDetailsWidget = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(userDetailsWidget);

    // User info section
    detailsUserInfo = new QLabel("Select a user to view details");
    detailsUserInfo->setStyleSheet(
        "QLabel {"
        "    background-color: #f8f9fa;"
        "    border: 1px solid #ddd;"
        "    padding: 15px;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "}"
    );
    detailsLayout->addWidget(detailsUserInfo);

    // User statistics
    userStatsLabel = new QLabel();
    userStatsLabel->setStyleSheet(
        "QLabel {"
        "    background-color: #e7f3ff;"
        "    border: 1px solid #b3d9ff;"
        "    padding: 10px;"
        "    border-radius: 8px;"
        "    font-weight: bold;"
        "}"
    );
    detailsLayout->addWidget(userStatsLabel);

    // Borrow history table
    QLabel* historyLabel = new QLabel("📚 Borrowing History");
    historyLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #333; margin-top: 10px;");
    detailsLayout->addWidget(historyLabel);

    userBorrowHistoryTable = new QTableWidget();
    userBorrowHistoryTable->setColumnCount(5);
    userBorrowHistoryTable->setHorizontalHeaderLabels({"Book Title", "Borrow Date", "Due Date", "Return Date", "Status"});
    userBorrowHistoryTable->horizontalHeader()->setStretchLastSection(true);
    detailsLayout->addWidget(userBorrowHistoryTable);
}

void UserManagementWidget::loadUsers() {
    // Mock data for demonstration
    userTable->setRowCount(0);

    // Sample users
    QStringList sampleUsers = {
        "STU001|John Doe|john.doe@student.edu|Student|Active|2024-01-15|2024-08-25",
        "STU002|Jane Smith|jane.smith@student.edu|Student|Active|2024-02-20|2024-08-24",
        "FAC001|Dr. Robert Johnson|r.johnson@faculty.edu|Faculty|Active|2023-09-01|2024-08-23",
        "FAC002|Prof. Emily Davis|e.davis@faculty.edu|Faculty|Active|2022-08-15|2024-08-22",
        "LIB001|Admin Librarian|admin@library.edu|Librarian|Active|2022-01-01|2024-08-26",
        "STU003|Mike Wilson|mike.w@student.edu|Student|Suspended|2024-03-10|2024-07-15",
        "FAC003|Dr. Sarah Brown|s.brown@faculty.edu|Faculty|Inactive|2023-06-01|2024-06-30"
    };

    for (int i = 0; i < sampleUsers.size(); ++i) {
        QStringList parts = sampleUsers[i].split('|');
        if (parts.size() >= 7) {
            userTable->insertRow(i);
            for (int j = 0; j < parts.size(); ++j) {
                QTableWidgetItem* item = new QTableWidgetItem(parts[j]);
                if (j == 4) { // Status column
                    if (parts[j] == "Active") {
                        item->setBackground(QBrush(QColor(200, 255, 200)));
                    } else if (parts[j] == "Suspended") {
                        item->setBackground(QBrush(QColor(255, 200, 200)));
                    } else if (parts[j] == "Inactive") {
                        item->setBackground(QBrush(QColor(255, 255, 200)));
                    }
                }
                userTable->setItem(i, j, item);
            }
        }
    }

    updateUserCount();
}

void UserManagementWidget::updateUserCount() {
    int totalUsers = userTable->rowCount();
    int activeUsers = 0;

    for (int i = 0; i < totalUsers; ++i) {
        QTableWidgetItem* statusItem = userTable->item(i, 4);
        if (statusItem && statusItem->text() == "Active") {
            activeUsers++;
        }
    }

    userCountLabel->setText(QString("Total Users: %1 | Active: %2").arg(totalUsers).arg(activeUsers));
}

void UserManagementWidget::showUserTypeFields() {
    QString userType = userTypeCombo->currentText();

    studentFields->setVisible(userType == "Student");
    facultyFields->setVisible(userType == "Faculty");
    librarianFields->setVisible(userType == "Librarian");
}

// Implement remaining slots...
void UserManagementWidget::onAddUserClicked() {
    if (!validateUserForm()) return;

    // Create new user (simplified)
    QString name = nameEdit->text();
    QString email = emailEdit->text();
    QString userType = userTypeCombo->currentText();

    // Generate user ID
    QString userIdPrefix = userType == "Student" ? "STU" : (userType == "Faculty" ? "FAC" : "LIB");
    QString userId = QString("%1%2").arg(userIdPrefix).arg(QString::number(userTable->rowCount() + 1).rightJustified(3, '0'));

    // Add to table
    int row = userTable->rowCount();
    userTable->insertRow(row);

    userTable->setItem(row, 0, new QTableWidgetItem(userId));
    userTable->setItem(row, 1, new QTableWidgetItem(name));
    userTable->setItem(row, 2, new QTableWidgetItem(email));
    userTable->setItem(row, 3, new QTableWidgetItem(userType));

    QTableWidgetItem* statusItem = new QTableWidgetItem("Active");
    statusItem->setBackground(QBrush(QColor(200, 255, 200)));
    userTable->setItem(row, 4, statusItem);

    userTable->setItem(row, 5, new QTableWidgetItem(QDate::currentDate().toString("yyyy-MM-dd")));
    userTable->setItem(row, 6, new QTableWidgetItem(QDate::currentDate().toString("yyyy-MM-dd")));

    QMessageBox::information(this, "Success", QString("User '%1' added successfully!").arg(name));

    // Send notification
    notificationService->sendWelcomeMessage(email, name, userType);

    clearUserForm();
    updateUserCount();
}

void UserManagementWidget::onEditUserClicked() {
    // Implementation similar to onAddUserClicked but for editing
    QMessageBox::information(this, "Edit User", "Edit functionality will be fully implemented soon!");
}

void UserManagementWidget::onDeleteUserClicked() {
    int currentRow = userTable->currentRow();
    if (currentRow >= 0) {
        QString name = userTable->item(currentRow, 1)->text();

        int ret = QMessageBox::question(this, "Confirm Delete",
            QString("Are you sure you want to delete user '%1'?").arg(name),
            QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::Yes) {
            userTable->removeRow(currentRow);
            QMessageBox::information(this, "Success", "User deleted successfully!");
            clearUserForm();
            updateUserCount();
        }
    }
}

void UserManagementWidget::onRefreshClicked() {
    loadUsers();
    QMessageBox::information(this, "Refreshed", "User list has been refreshed!");
}

void UserManagementWidget::onSendNotificationClicked() {
    int currentRow = userTable->currentRow();
    if (currentRow >= 0) {
        QString userEmail = userTable->item(currentRow, 2)->text();
        QString userName = userTable->item(currentRow, 1)->text();

        bool ok;
        QString message = QInputDialog::getMultiLineText(this, "Send Notification",
            QString("Send notification to %1:").arg(userName), "", &ok);

        if (ok && !message.isEmpty()) {
            if (notificationService->sendSimpleNotification(userEmail, message)) {
                QMessageBox::information(this, "Notification Sent",
                                         QString("Notification sent successfully to %1").arg(userName));
            } else {
                QMessageBox::warning(this, "Send Failed", "Failed to send notification!");
            }
        }
    } else {
        QMessageBox::warning(this, "No Selection", "Please select a user first!");
    }
}

void UserManagementWidget::onExportUsersClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Users", "users_export.csv", "CSV Files (*.csv)");
    if (!fileName.isEmpty()) {
        QMessageBox::information(this, "Export", "Export functionality will be implemented soon!");
    }
}

void UserManagementWidget::onViewUserDetailsClicked() {
    int currentRow = userTable->currentRow();
    if (currentRow >= 0) {
        rightTabWidget->setCurrentIndex(1); // Switch to details tab

        QString userId = userTable->item(currentRow, 0)->text();
        QString name = userTable->item(currentRow, 1)->text();
        QString email = userTable->item(currentRow, 2)->text();
        QString userType = userTable->item(currentRow, 3)->text();
        QString status = userTable->item(currentRow, 4)->text();
        QString joinDate = userTable->item(currentRow, 5)->text();

        // Update user info display
        detailsUserInfo->setText(
            QString("<b>%1</b><br>"
                    "📧 Email: %2<br>"
                    "🆔 User ID: %3<br>"
                    "👤 Type: %4<br>"
                    "📊 Status: %5<br>"
                    "📅 Joined: %6")
                .arg(name, email, userId, userType, status, joinDate)
            );

        // Update statistics
        userStatsLabel->setText(
            "📚 Books Borrowed: 12 | 📖 Currently Reading: 3 | ⚠️ Overdue: 0 | 💰 Total Fines: $0.00"
            );

        // Load mock borrow history
        userBorrowHistoryTable->setRowCount(0);
        QStringList mockHistory = {
            "Clean Code|2024-08-01|2024-08-15|2024-08-14|Returned",
            "Design Patterns|2024-08-10|2024-08-24||Active",
            "Python Basics|2024-07-20|2024-08-03|2024-08-05|Returned Late",
            "JavaScript Guide|2024-08-20|2024-09-03||Active"
        };

        for (int i = 0; i < mockHistory.size(); ++i) {
            QStringList parts = mockHistory[i].split('|');
            userBorrowHistoryTable->insertRow(i);
            for (int j = 0; j < parts.size(); ++j) {
                QTableWidgetItem* item = new QTableWidgetItem(parts[j]);
                if (j == 4) { // Status column
                    if (parts[j] == "Active") {
                        item->setBackground(QBrush(QColor(200, 255, 200)));
                    } else if (parts[j] == "Returned Late") {
                        item->setBackground(QBrush(QColor(255, 200, 200)));
                    }
                }
                userBorrowHistoryTable->setItem(i, j, item);
            }
        }
    }
}

void UserManagementWidget::onSearchTextChanged() {
    filterUsers();
}

void UserManagementWidget::onUserTypeChanged() {
    filterUsers();
}

void UserManagementWidget::onUserTableSelectionChanged() {
    int currentRow = userTable->currentRow();
    if (currentRow >= 0) {
        // Populate form with selected user data
        userIdEdit->setText(userTable->item(currentRow, 0)->text());
        nameEdit->setText(userTable->item(currentRow, 1)->text());
        emailEdit->setText(userTable->item(currentRow, 2)->text());
        userTypeCombo->setCurrentText(userTable->item(currentRow, 3)->text());

        // Switch to edit mode
        isEditMode = true;
        addUserBtn->setVisible(false);
        editUserBtn->setVisible(true);
        deleteUserBtn->setEnabled(true);

        showUserTypeFields();
    }
}

void UserManagementWidget::clearUserForm() {
    userIdEdit->clear();
    nameEdit->clear();
    emailEdit->clear();
    passwordEdit->clear();
    userTypeCombo->setCurrentIndex(0);
    phoneEdit->clear();
    addressEdit->clear();
    dateOfBirthEdit->setDate(QDate::currentDate().addYears(-20));

    // Clear user type specific fields
    studentIdEdit->clear();
    majorEdit->clear();
    yearCombo->setCurrentIndex(0);
    gpaEdit->clear();

    employeeIdEdit->clear();
    departmentEdit->clear();
    positionEdit->clear();
    yearsOfServiceEdit->clear();
    officeRoomEdit->clear();

    libEmployeeIdEdit->clear();
    shiftCombo->setCurrentIndex(0);
    specializationEdit->clear();
    salaryEdit->clear();

    // Reset to add mode
    isEditMode = false;
    addUserBtn->setVisible(true);
    editUserBtn->setVisible(false);
    deleteUserBtn->setEnabled(false);

    showUserTypeFields();
}

bool UserManagementWidget::validateUserForm() {
    if (nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Name is required!");
        nameEdit->setFocus();
        return false;
    }

    if (emailEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Email is required!");
        emailEdit->setFocus();
        return false;
    }

    if (!isEditMode && passwordEdit->text().length() < 6) {
        QMessageBox::warning(this, "Validation Error", "Password must be at least 6 characters!");
        passwordEdit->setFocus();
        return false;
    }

    return true;
}

void UserManagementWidget::filterUsers() {
    QString searchText = searchEdit->text().toLower();
    QString typeFilter = userTypeFilterCombo->currentText();

    for (int i = 0; i < userTable->rowCount(); ++i) {
        bool shouldShow = true;

        // Search filter
        if (!searchText.isEmpty()) {
            bool matchFound = false;
            for (int j = 0; j < 3; ++j) { // Search in ID, Name, Email columns
                QTableWidgetItem* item = userTable->item(i, j);
                if (item && item->text().toLower().contains(searchText)) {
                    matchFound = true;
                    break;
                }
            }
            if (!matchFound) shouldShow = false;
        }

        // Type filter
        if (typeFilter != "All Types" && shouldShow) {
            QTableWidgetItem* typeItem = userTable->item(i, 3);
            if (!typeItem || typeItem->text() != typeFilter) {
                shouldShow = false;
            }
        }

        userTable->setRowHidden(i, !shouldShow);
    }
}
