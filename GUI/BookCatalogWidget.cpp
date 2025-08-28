#include "bookcatalogwidget.h"
#include "Services/libraryservice.h"
#include "Models/book.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHeaderView>
#include <QSplitter>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QSpinBox>

BookCatalogWidget::BookCatalogWidget(LibraryService& service, QWidget *parent)
    : QWidget(parent), libraryService(service) {
    setupUI();
    setupConnections();
    refreshData(); // Tải dữ liệu lần đầu
}

void BookCatalogWidget::setupUI() {
    auto mainLayout = new QHBoxLayout(this);
    auto splitter = new QSplitter(Qt::Horizontal, this);

    auto leftWidget = new QWidget();
    auto leftLayout = new QVBoxLayout(leftWidget);
    auto searchLayout = new QHBoxLayout();
    searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Tìm kiếm theo tên sách, tác giả, ISBN...");
    refreshButton = new QPushButton("Làm mới");
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(refreshButton);
    leftLayout->addLayout(searchLayout);

    bookTable = new QTableWidget();
    bookTable->setColumnCount(4);
    bookTable->setHorizontalHeaderLabels({"ISBN", "Tên sách", "Tác giả", "Có sẵn / Tổng"});
    bookTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bookTable->horizontalHeader()->setStretchLastSection(true);
    bookTable->verticalHeader()->setVisible(false);
    leftLayout->addWidget(bookTable);

    auto rightWidget = new QWidget();
    auto rightLayout = new QVBoxLayout(rightWidget);
    auto formGroup = new QGroupBox("Thông tin sách");
    auto formLayout = new QFormLayout(formGroup);
    isbnEdit = new QLineEdit();
    titleEdit = new QLineEdit();
    authorEdit = new QLineEdit();
    totalCopiesSpinBox = new QSpinBox();
    totalCopiesSpinBox->setRange(0, 1000);
    formLayout->addRow("ISBN:", isbnEdit);
    formLayout->addRow("Tên sách:", titleEdit);
    formLayout->addRow("Tác giả:", authorEdit);
    formLayout->addRow("Tổng số bản:", totalCopiesSpinBox);
    rightLayout->addWidget(formGroup);

    auto buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Thêm mới");
    editButton = new QPushButton("Cập nhật");
    deleteButton = new QPushButton("Xóa");
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    rightLayout->addLayout(buttonLayout);
    rightLayout->addStretch();

    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setSizes({600, 400});
    mainLayout->addWidget(splitter);

    clearForm(); // Xóa form và vô hiệu hóa nút lúc đầu
}

void BookCatalogWidget::setupConnections() {
    // Sửa: Kết nối tín hiệu dataChanged để tự động cập nhật
    connect(&libraryService, &LibraryService::dataChanged, this, &BookCatalogWidget::refreshData);

    connect(refreshButton, &QPushButton::clicked, this, &BookCatalogWidget::refreshData);
    connect(searchEdit, &QLineEdit::textChanged, this, &BookCatalogWidget::onSearchTextChanged);
    connect(bookTable, &QTableWidget::itemSelectionChanged, this, &BookCatalogWidget::onTableItemSelected);

    connect(addButton, &QPushButton::clicked, this, &BookCatalogWidget::onAddBook);
    connect(editButton, &QPushButton::clicked, this, &BookCatalogWidget::onEditBook);
    connect(deleteButton, &QPushButton::clicked, this, &BookCatalogWidget::onDeleteBook);
}

void BookCatalogWidget::refreshData() {
    auto books = libraryService.getAllBooks();
    populateTable(books);
    clearForm();
}

void BookCatalogWidget::populateTable(const std::vector<std::unique_ptr<Book>>& books) {
    bookTable->setRowCount(0);
    bookTable->blockSignals(true);
    for (const auto& book : books) {
        int row = bookTable->rowCount();
        bookTable->insertRow(row);
        bookTable->setItem(row, 0, new QTableWidgetItem(book->getIsbn()));
        bookTable->setItem(row, 1, new QTableWidgetItem(book->getTitle()));
        bookTable->setItem(row, 2, new QTableWidgetItem(book->getAuthor()));
        QString copies = QString("%1 / %2").arg(book->getAvailableCopies()).arg(book->getTotalCopies());
        bookTable->setItem(row, 3, new QTableWidgetItem(copies));
    }
    bookTable->blockSignals(false);
}

void BookCatalogWidget::clearForm() {
    isbnEdit->clear();
    titleEdit->clear();
    authorEdit->clear();
    totalCopiesSpinBox->setValue(1);
    isbnEdit->setReadOnly(false);
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    bookTable->clearSelection();
}

void BookCatalogWidget::onTableItemSelected() {
    int currentRow = bookTable->currentRow();
    if (currentRow < 0) {
        clearForm();
        return;
    }

    isbnEdit->setText(bookTable->item(currentRow, 0)->text());
    titleEdit->setText(bookTable->item(currentRow, 1)->text());
    authorEdit->setText(bookTable->item(currentRow, 2)->text());

    QString copiesText = bookTable->item(currentRow, 3)->text();
    int totalCopies = copiesText.section('/', 1, 1).trimmed().toInt();
    totalCopiesSpinBox->setValue(totalCopies);

    isbnEdit->setReadOnly(true); // Không cho phép sửa ISBN
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

void BookCatalogWidget::onSearchTextChanged(const QString& text) {
    auto books = libraryService.searchBooks(text);
    populateTable(books);
}

void BookCatalogWidget::onAddBook() {
    QString isbn = isbnEdit->text().trimmed();
    QString title = titleEdit->text().trimmed();
    QString author = authorEdit->text().trimmed();
    int copies = totalCopiesSpinBox->value();

    if (isbn.isEmpty() || title.isEmpty() || author.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng điền đầy đủ thông tin ISBN, Tên sách và Tác giả.");
        return;
    }

    if (libraryService.addBook(isbn, title, author, copies)) {
        QMessageBox::information(this, "Thành công", "Đã thêm sách mới thành công!");
        // Không cần gọi loadBooks() nữa, tín hiệu dataChanged sẽ làm việc đó
    } else {
        QMessageBox::critical(this, "Thất bại", "Không thể thêm sách. ISBN có thể đã tồn tại.");
    }
}

void BookCatalogWidget::onEditBook() {
    QString isbn = isbnEdit->text().trimmed();
    QString title = titleEdit->text().trimmed();
    QString author = authorEdit->text().trimmed();
    int copies = totalCopiesSpinBox->value();

    if (title.isEmpty() || author.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Tên sách và Tác giả không được để trống.");
        return;
    }

    if (libraryService.updateBook(isbn, title, author, copies)) {
        QMessageBox::information(this, "Thành công", "Đã cập nhật thông tin sách!");
    } else {
        QMessageBox::critical(this, "Thất bại", "Không thể cập nhật. Số lượng tổng mới không thể nhỏ hơn số sách đang được mượn.");
    }
}

void BookCatalogWidget::onDeleteBook() {
    QString isbn = isbnEdit->text().trimmed();
    QString title = titleEdit->text().trimmed();

    auto reply = QMessageBox::question(this, "Xác nhận Xóa",
                                       QString("Bạn có chắc chắn muốn xóa sách '%1'?").arg(title),
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (libraryService.deleteBook(isbn)) {
            QMessageBox::information(this, "Thành công", "Đã xóa sách thành công!");
        } else {
            QMessageBox::critical(this, "Thất bại", "Không thể xóa sách. Sách có thể đang được mượn.");
        }
    }
}
