#include "dashboardwidget.h"
#include "Services/libraryservice.h"
#include "Models/person.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QTimer>
#include <QListWidget>
#include <QDateTime>
#include <QGroupBox>

DashboardWidget::DashboardWidget(LibraryService& service, QWidget *parent)
    : QWidget(parent), libraryService(service) {
    setupUI();

    // --- Thiết lập Timer để tự động làm mới ---
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &DashboardWidget::updateStatistics);
    refreshTimer->start(30000); // Làm mới sau mỗi 30 giây
}

void DashboardWidget::showEvent(QShowEvent *event) {
    // Gọi hàm này mỗi khi widget được hiển thị
    updateStatistics();
    QWidget::showEvent(event);
}

void DashboardWidget::setupUI() {
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // --- Header ---
    auto welcomeLabel = new QLabel(this);
    Person* currentUser = libraryService.getCurrentUser();
    if (currentUser) {
        welcomeLabel->setText(QString("Chào mừng trở lại, %1!").arg(currentUser->getName()));
    }
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
    mainLayout->addWidget(welcomeLabel);

    // --- Main Content Layout (Split) ---
    auto contentLayout = new QHBoxLayout();

    // --- Cột trái: Thống kê ---
    auto statsContainer = new QWidget();
    auto statsLayout = new QGridLayout(statsContainer);
    statsLayout->setSpacing(20);

    QFrame* totalBooksCard = createStatCard("Tổng số sách", "📚", "#4a90e2");
    totalBooksLabel = totalBooksCard->findChild<QLabel*>("valueLabel");

    QFrame* totalUsersCard = createStatCard("Tổng số người dùng", "👥", "#17a2b8");
    totalUsersLabel = totalUsersCard->findChild<QLabel*>("valueLabel");

    QFrame* borrowedCard = createStatCard("Sách đang mượn", "💳", "#ffc107");
    borrowedBooksLabel = borrowedCard->findChild<QLabel*>("valueLabel");

    QFrame* overdueCard = createStatCard("Sách quá hạn", "⚠️", "#dc3545");
    overdueBooksLabel = overdueCard->findChild<QLabel*>("valueLabel");

    statsLayout->addWidget(totalBooksCard, 0, 0);
    statsLayout->addWidget(totalUsersCard, 0, 1);
    statsLayout->addWidget(borrowedCard, 1, 0);
    statsLayout->addWidget(overdueCard, 1, 1);

    // --- Cột phải: Hoạt động gần đây ---
    auto activityGroup = new QGroupBox("Hoạt động gần đây");
    auto activityLayout = new QVBoxLayout(activityGroup);
    recentActivityList = new QListWidget();
    activityLayout->addWidget(recentActivityList);

    contentLayout->addWidget(statsContainer, 2); // Cột thống kê chiếm 2/3
    contentLayout->addWidget(activityGroup, 1);  // Cột hoạt động chiếm 1/3

    mainLayout->addLayout(contentLayout);
}

QFrame* DashboardWidget::createStatCard(const QString& title, const QString& icon, const QString& color) {
    // ... (Hàm này giữ nguyên như trước)
    auto card = new QFrame();
    card->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    card->setStyleSheet(QString(
        "QFrame { background-color: white; border-radius: 8px; padding: 15px; border: 1px solid #e0e0e0; }"
        ));

    auto cardLayout = new QVBoxLayout(card);
    auto topLayout = new QHBoxLayout();
    auto iconLabel = new QLabel(icon);
    iconLabel->setStyleSheet("font-size: 28px;");

    auto valueLabel = new QLabel("0");
    valueLabel->setObjectName("valueLabel");
    valueLabel->setAlignment(Qt::AlignRight);
    valueLabel->setStyleSheet(QString("font-size: 26px; font-weight: bold; color: %1;").arg(color));

    topLayout->addWidget(iconLabel);
    topLayout->addWidget(valueLabel);

    auto titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 14px; color: #555;");

    cardLayout->addLayout(topLayout);
    cardLayout->addWidget(titleLabel);

    return card;
}

void DashboardWidget::updateStatistics() {
    // Kiểm tra sách quá hạn trước
    libraryService.checkOverdueBooks();

    // Gọi service để lấy dữ liệu mới nhất
    int bookCount = libraryService.getTotalBooksCount();
    int userCount = libraryService.getTotalUsersCount();
    int borrowedCount = libraryService.getActiveTransactionsCount();
    int overdueCount = libraryService.getOverdueTransactionsCount(); // Thêm dòng này

    // Cập nhật giao diện
    totalBooksLabel->setText(QString::number(bookCount));
    totalUsersLabel->setText(QString::number(userCount));
    borrowedBooksLabel->setText(QString::number(borrowedCount));
    overdueBooksLabel->setText(QString::number(overdueCount)); // Cập nhật số lượng quá hạn

    // Thêm một mục vào hoạt động gần đây
    addRecentActivity(QString("Bảng điều khiển đã được làm mới."));
}

void DashboardWidget::addRecentActivity(const QString& activity) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    recentActivityList->insertItem(0, QString("[%1] %2").arg(timestamp, activity));

    // Giới hạn chỉ hiển thị 100 hoạt động gần nhất
    if (recentActivityList->count() > 100) {
        delete recentActivityList->takeItem(100);
    }
}
