#include <QApplication>
#include <QMessageBox>
#include "GUI/loginwidget.h"
#include "GUI/mainwindow.h"
#include "Services/databasemanager.h"
#include "Services/libraryservice.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("EduLibraryManager");
    app.setOrganizationName("EduSolutions");

    DatabaseManager& dbManager = DatabaseManager::getInstance();
    if (!dbManager.initialize("library.db")) {
        QMessageBox::critical(nullptr, "Lỗi Database", "Không thể khởi tạo cơ sở dữ liệu.");
        return -1;
    }

    LibraryService libraryService;
    libraryService.seedDatabaseFromResources();

    LoginWidget loginWidget(libraryService);
    MainWindow* mainWindow = nullptr;

    // SỬA LỖI: Lambda giờ đây không nhận tham số, khớp với tín hiệu mới
    QObject::connect(&loginWidget, &LoginWidget::loginSuccessful,
                     [&]() {
                         // User đã được đặt trong libraryService
                         mainWindow = new MainWindow(libraryService);
                         mainWindow->setAttribute(Qt::WA_DeleteOnClose);
                         mainWindow->show();
                         loginWidget.close();
                     });

    loginWidget.show();

    int result = app.exec();
    dbManager.close();
    return result;
}
