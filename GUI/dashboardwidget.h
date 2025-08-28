#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>

// Forward declarations
class QLabel;
class QFrame;
class QTimer;
class QListWidget;
class LibraryService;

class DashboardWidget : public QWidget {
    Q_OBJECT
public:
    explicit DashboardWidget(LibraryService& service, QWidget *parent = nullptr);
    // Hiển thị widget này sẽ kích hoạt làm mới dữ liệu
    void showEvent(QShowEvent *event) override;
    void addRecentActivity(const QString& activity);

public slots:
    void updateStatistics();

private:
    void setupUI();
    QFrame* createStatCard(const QString& title, const QString& icon, const QString& color);

    // --- UI Components ---
    QLabel* totalBooksLabel;
    QLabel* totalUsersLabel;
    QLabel* borrowedBooksLabel; // Sẽ cập nhật sau
    QLabel* overdueBooksLabel;  // Sẽ cập nhật sau
    QListWidget* recentActivityList;

    // --- Backend Service ---
    LibraryService& libraryService;

    // --- Timer ---
    QTimer* refreshTimer;
};

#endif // DASHBOARDWIDGET_H
