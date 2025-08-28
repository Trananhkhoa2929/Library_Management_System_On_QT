QT       += core gui sql widgets

CONFIG += c++17 # Sử dụng C++17 để hỗ trợ tốt hơn cho smart pointers
TARGET = EduLibraryManager
TEMPLATE = app

# Đường dẫn tương đối đến các thư mục
INCLUDEPATH += $$PWD

# SOURCES: Liệt kê tất cả các file .cpp
SOURCES += \
    main.cpp \
    # GUI
    gui/LoginWidget.cpp \
    gui/MainWindow.cpp \
    gui/BookCatalogWidget.cpp \
    gui/DashboardWidget.cpp \
    gui/TransactionWidget.cpp \
    # Models
    models/Person.cpp \
    models/Student.cpp \
    models/Faculty.cpp \
    models/Librarian.cpp \
    models/Book.cpp \
    models/Transaction.cpp \
    # Services
    services/DatabaseManager.cpp \
    services/LibraryService.cpp \
    # Factories
    factories/UserFactory.cpp

# HEADERS: Liệt kê tất cả các file .h
HEADERS += \
    # GUI
    gui/BookCatalogWidget.h \
    gui/LoginWidget.h \
    gui/MainWindow.h \
    gui/DashboardWidget.h \
    gui/TransactionWidget.h \
    # Models
    models/Person.h \
    models/Student.h \
    models/Faculty.h \
    models/Librarian.h \
    models/Book.h \
    models/Transaction.h \
    # Services
    services/DatabaseManager.h \
    services/LibraryService.h \
    # Factories
    factories/UserFactory.h

# FORMS: Nếu bạn có các file .ui từ Qt Designer
# FORMS +=

RESOURCES += \
    Resources.qrc

