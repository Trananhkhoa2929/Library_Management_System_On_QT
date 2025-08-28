#include "transactionwidget.h"
#include "Services/libraryservice.h"
#include "Models/transaction.h"
#include "Models/person.h" // <-- THÊM INCLUDE NÀY ĐỂ SỬ DỤNG Person

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QShowEvent>

TransactionWidget::TransactionWidget(LibraryService& service, QWidget *parent)
    : QWidget(parent), libraryService(service) {
    setupUI();
    setupConnections();
    // Bỏ refreshData() khỏi constructor để tránh gọi thừa
}

// SỬA LỖI: Thêm lại hàm showEvent để tự động cập nhật và điền thông tin
void TransactionWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    refreshData(); // Luôn làm mới dữ liệu khi người dùng chuyển sang tab này

    // Cải thiện UX: Tự động điền ID người dùng đang đăng nhập
    Person* currentUser = libraryService.getCurrentUser();
    if (currentUser) {
        borrowUserIdEdit->setText(currentUser->getUserId());
    }
}

void TransactionWidget::setupUI() {
    auto mainLayout = new QVBoxLayout(this);
    auto actionsLayout = new QHBoxLayout();

    auto borrowGroup = new QGroupBox("Mượn sách mới");
    auto borrowForm = new QFormLayout(borrowGroup);
    borrowUserIdEdit = new QLineEdit();
    // Sửa: Làm cho ô ID không thể chỉnh sửa để tránh người dùng nhập sai
    borrowUserIdEdit->setReadOnly(true);
    borrowUserIdEdit->setPlaceholderText("ID người dùng sẽ tự động điền");
    borrowBookIsbnEdit = new QLineEdit();
    borrowBookIsbnEdit->setPlaceholderText("Nhập ISBN của sách");
    borrowButton = new QPushButton("Xác nhận Mượn");
    borrowForm->addRow("ID Người dùng:", borrowUserIdEdit);
    borrowForm->addRow("ISBN Sách:", borrowBookIsbnEdit);
    borrowForm->addWidget(borrowButton);

    auto returnGroup = new QGroupBox("Trả sách");
    auto returnForm = new QFormLayout(returnGroup);
    returnTransactionIdEdit = new QLineEdit();
    returnTransactionIdEdit->setPlaceholderText("Chọn giao dịch từ bảng hoặc nhập ID");
    returnButton = new QPushButton("Xác nhận Trả");
    returnForm->addRow("ID Giao dịch:", returnTransactionIdEdit);
    returnForm->addWidget(returnButton);

    actionsLayout->addWidget(borrowGroup);
    actionsLayout->addWidget(returnGroup);
    mainLayout->addLayout(actionsLayout);

    auto historyGroup = new QGroupBox("Lịch sử Giao dịch");
    auto historyLayout = new QVBoxLayout(historyGroup);
    refreshButton = new QPushButton("Làm mới danh sách");
    historyLayout->addWidget(refreshButton, 0, Qt::AlignRight);

    transactionTable = new QTableWidget();
    transactionTable->setColumnCount(7);
    transactionTable->setHorizontalHeaderLabels({
        "ID Giao dịch", "ID Người dùng", "Tên Người dùng",
        "ISBN Sách", "Tên Sách", "Ngày mượn", "Trạng thái"
    });
    transactionTable->horizontalHeader()->setStretchLastSection(true);
    transactionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    transactionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    historyLayout->addWidget(transactionTable);

    mainLayout->addWidget(historyGroup);
}

void TransactionWidget::setupConnections() {
    connect(&libraryService, &LibraryService::dataChanged, this, &TransactionWidget::refreshData);
    connect(refreshButton, &QPushButton::clicked, this, &TransactionWidget::refreshData);
    connect(borrowButton, &QPushButton::clicked, this, &TransactionWidget::onProcessBorrow);
    connect(returnButton, &QPushButton::clicked, this, &TransactionWidget::onProcessReturn);
    connect(transactionTable, &QTableWidget::itemSelectionChanged, this, &TransactionWidget::onTableItemSelected);
}

void TransactionWidget::refreshData() {
    auto transactions = libraryService.getAllTransactions();
    populateTable(transactions);
}

void TransactionWidget::populateTable(const std::vector<std::unique_ptr<Transaction>>& transactions) {
    transactionTable->setRowCount(0);
    transactionTable->blockSignals(true);
    for (const auto& trans : transactions) {
        int row = transactionTable->rowCount();
        transactionTable->insertRow(row);

        transactionTable->setItem(row, 0, new QTableWidgetItem(QString::number(trans->getId())));
        transactionTable->setItem(row, 1, new QTableWidgetItem(trans->getUserId()));
        transactionTable->setItem(row, 2, new QTableWidgetItem(trans->getUserName()));
        transactionTable->setItem(row, 3, new QTableWidgetItem(trans->getBookIsbn()));
        transactionTable->setItem(row, 4, new QTableWidgetItem(trans->getBookTitle()));
        transactionTable->setItem(row, 5, new QTableWidgetItem(trans->getBorrowDate().toString("dd/MM/yyyy hh:mm")));

        QTableWidgetItem* statusItem = new QTableWidgetItem();
        QString statusText;
        QColor statusColor;

        switch(trans->getStatus()) {
        case TransactionStatus::Completed:
            statusText = "Đã trả";
            statusColor = QColor("#d4edda");
            break;
        case TransactionStatus::Overdue:
            statusText = "Quá hạn";
            statusColor = QColor("#f8d7da");
            break;
        case TransactionStatus::Active:
        default:
            statusText = "Đang mượn";
            statusColor = QColor("#fff3cd");
            break;
        }
        statusItem->setText(statusText);
        statusItem->setBackground(statusColor);
        transactionTable->setItem(row, 6, statusItem);
    }
    transactionTable->blockSignals(false);
}

void TransactionWidget::onTableItemSelected() {
    int currentRow = transactionTable->currentRow();
    if (currentRow < 0) return;

    QString status = transactionTable->item(currentRow, 6)->text();
    if (status != "Đã trả") {
        returnTransactionIdEdit->setText(transactionTable->item(currentRow, 0)->text());
    }
}

void TransactionWidget::onProcessBorrow() {
    QString userId = borrowUserIdEdit->text().trimmed();
    QString bookIsbn = borrowBookIsbnEdit->text().trimmed();

    if (userId.isEmpty() || bookIsbn.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng đăng nhập và nhập ISBN sách.");
        return;
    }

    if (libraryService.borrowBook(userId, bookIsbn)) {
        QMessageBox::information(this, "Thành công", "Mượn sách thành công!");
        // Không cần clear userIdEdit vì nó là read-only và sẽ được cập nhật khi chuyển tab
        borrowBookIsbnEdit->clear();
    } else {
        QMessageBox::critical(this, "Thất bại", "Không thể mượn sách. Vui lòng kiểm tra lại ISBN và số lượng sách có sẵn.");
    }
}

void TransactionWidget::onProcessReturn() {
    QString transactionId = returnTransactionIdEdit->text().trimmed();
    if (transactionId.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập hoặc chọn một ID giao dịch cần trả.");
        return;
    }

    if (libraryService.returnBook(transactionId)) {
        QMessageBox::information(this, "Thành công", "Trả sách thành công!");
        returnTransactionIdEdit->clear();
    } else {
        QMessageBox::critical(this, "Thất bại", "Không thể trả sách. Giao dịch có thể đã được trả hoặc ID không hợp lệ.");
    }
}
