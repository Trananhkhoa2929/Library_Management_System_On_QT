#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H

#include <QWidget>
#include <memory>
#include <vector>

// Forward declarations
class QTableWidget;
class QLineEdit;
class QPushButton;
class LibraryService;
class Transaction;
class QShowEvent; // Thêm forward declaration cho QShowEvent

class TransactionWidget : public QWidget {
    Q_OBJECT
public:
    explicit TransactionWidget(LibraryService& service, QWidget *parent = nullptr);

protected:
    // SỬA LỖI: Khai báo showEvent để ghi đè hàm của QWidget
    void showEvent(QShowEvent *event) override;

public slots:
    void refreshData();

private slots:
    void onProcessBorrow();
    void onProcessReturn();
    void onTableItemSelected();

private:
    void setupUI();
    void setupConnections();
    void populateTable(const std::vector<std::unique_ptr<Transaction>>& transactions);

    // --- UI Components ---
    QLineEdit* borrowUserIdEdit;
    QLineEdit* borrowBookIsbnEdit;
    QPushButton* borrowButton;
    QLineEdit* returnTransactionIdEdit;
    QPushButton* returnButton;
    QTableWidget* transactionTable;
    QPushButton* refreshButton;

    // --- Backend Service ---
    LibraryService& libraryService;
};

#endif // TRANSACTIONWIDGET_H
