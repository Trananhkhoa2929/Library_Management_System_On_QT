```markdown
# EduLibrary Manager

EduLibrary Manager là một ứng dụng quản lý thư viện dành cho máy tính, được xây dựng bằng C++ (C++17), Qt (Widgets, Core, SQL) và SQLite. Dự án cung cấp giao diện trực quan để quản lý sách, người dùng và các giao dịch mượn/trả — phù hợp làm ví dụ học tập hoặc nền tảng để mở rộng.

---

Mục lục
- Tính năng chính
- Cấu trúc dự án
- Bắt đầu
  - Bước 1: Yêu cầu hệ thống
  - Bước 2: Tải mã nguồn
  - Bước 3: Biên dịch và chạy
- Sử dụng
- Luồng hoạt động hệ thống
- Xử lý lỗi thường gặp
- Đóng gói ứng dụng

---

Tính năng chính
- Quản lý Người dùng: Đăng ký / Đăng nhập với vai trò Student, Faculty, Librarian (Head Librarian).
- Quản lý Sách: Thêm, sửa, xóa, tìm kiếm sách.
- Quản lý Giao dịch: Mượn, trả và lịch sử giao dịch; trạng thái Active / Completed / Overdue.
- Dashboard: Thống kê tổng số sách, người dùng, giao dịch đang mượn, giao dịch quá hạn.
- Bảo mật: Mật khẩu được băm kèm salt (SHA-256) và lưu dưới dạng `salt:hash`.
- Dữ liệu mẫu: Seed tự động từ `resources/data/books.csv` và tạo user admin mặc định khi database rỗng.
- UI phản hồi: Qt Signals/Slots để tự động cập nhật giao diện khi dữ liệu thay đổi.

---

Cấu trúc dự án
Ứng dụng được chia theo lớp: GUI, Services, Models, Factories, Resources.

Ví dụ cây thư mục (quan sát trong repo):
.
├── Library.pro
├── main.cpp
├── Resources.qrc
├── resources/
│   └── data/
│       └── books.csv
├── gui/
│   ├── LoginWidget.*
│   ├── MainWindow.*
│   ├── DashboardWidget.*
│   ├── BookCatalogWidget.*
│   └── TransactionWidget.*
├── services/
│   ├── DatabaseManager.*
│   └── LibraryService.*
├── models/
│   ├── Person.*
│   ├── Book.*
│   └── Transaction.*
└── factories/
    └── UserFactory.*

Các file chính:
- Library.pro — project qmake
- main.cpp — khởi tạo app, DB và UI
- Resources.qrc + resources/data/books.csv — dữ liệu mẫu
- services/DatabaseManager.* — wrapper QSqlDatabase + các truy vấn
- services/LibraryService.* — logic nghiệp vụ, seed, authentication
- gui/* — widget/ giao diện

---

Bắt đầu

Bước 1: Yêu cầu hệ thống
- Qt 5.12+ hoặc Qt 6.x (modules: Core, Widgets, SQL).
- Trình biên dịch hỗ trợ C++17:
  - Windows: MinGW (theo Qt) hoặc MSVC (Visual Studio).
  - Linux: gcc hoặc clang.
  - macOS: Xcode command-line tools / clang.
- qmake (thuộc Qt kit) / Qt Creator.
- Git (nếu muốn clone).

Bước 2: Tải mã nguồn
- Clone (khuyến nghị):
```bash
git clone https://github.com/Trananhkhoa2929/Library_Management_System_On_QT.git
cd Library_Management_System_On_QT
```
- Hoặc tải ZIP từ trang GitHub → Code → Download ZIP → giải nén.

Bước 3: Biên dịch và chạy

Cách 1 — Qt Creator (khuyến nghị)
1. Mở Qt Creator.
2. File → Open File or Project → chọn `Library.pro`.
3. Chọn Kit (Qt version + compiler).
4. Build (Ctrl+B), Run (Ctrl+R).

Cách 2 — Dòng lệnh (Linux / macOS)
```bash
cd /path/to/Library_Management_System_On_QT
mkdir build && cd build
/path/to/qt/bin/qmake ../Library.pro   # hoặc 'qmake ../Library.pro' nếu PATH đã thiết lập
make -j$(nproc)                         # macOS: make
./EduLibraryManager
```

Cách 2 — Dòng lệnh (Windows, MinGW / MSVC)
- Mở Qt Command Prompt tương ứng (MinGW hoặc MSVC) để qmake có trong PATH.

MinGW:
```powershell
cd C:\path\to\Library_Management_System_On_QT
mkdir build
cd build
qmake ..\Library.pro
mingw32-make
.\EduLibraryManager.exe
```

MSVC:
```powershell
cd C:\path\to\Library_Management_System_On_QT
mkdir build
cd build
qmake ..\Library.pro -spec win32-msvc
nmake
.\EduLibraryManager.exe
```

Lưu ý:
- qmake phải tương ứng với phiên bản Qt bạn muốn dùng.
- Project sử dụng C++17 (CONFIG += c++17).

---

Sử dụng
- Khi chạy lần đầu, ứng dụng sẽ tạo file SQLite `library.db` trong thư mục chứa file thực thi (được lấy từ QCoreApplication::applicationDirPath()).
- Nếu DB trống, ứng dụng sẽ seed dữ liệu từ resource `:/data/books.csv` và tạo user admin mặc định:
  - Email: admin@library.com
  - Mật khẩu: admin123
- Reset dữ liệu phát triển: đóng ứng dụng → xóa `library.db` → khởi động lại (seed lại).

---

Luồng hoạt động hệ thống (tóm tắt)
Mô hình dữ liệu/năng lực:
GUI ↔ LibraryService ↔ DatabaseManager ↔ SQLite

- GUI (widgets) gọi API của LibraryService cho các thao tác: đăng ký / đăng nhập / add/update/delete book / borrow / return.
- LibraryService xử lý logic (băm mật khẩu, kiểm tra business rules, tạo Transaction/Book/Person), gọi DatabaseManager để thực hiện truy vấn/ghi.
- DatabaseManager thực thi SQL và trả QSqlQuery cho LibraryService.
- LibraryService chuyển QSqlQuery thành các Model (Book, Transaction, Person) và emit tín hiệu dataChanged().
- GUI lắng nghe dataChanged() để refresh hiển thị.

Các luồng chính:
- Đăng ký: GUI → LibraryService::registerUser → DatabaseManager::saveNewUser → emit dataChanged()
- Đăng nhập: GUI → LibraryService::login → verify hash → setCurrentUser
- Mượn sách: GUI → LibraryService::borrowBook → kiểm tra available → updateBookCopies + saveNewTransaction → emit dataChanged()
- Trả sách: GUI → LibraryService::returnBook → updateBookCopies + updateTransactionOnReturn → emit dataChanged()

Xử lý lỗi thường gặp

1) "QSQLITE driver not loaded" / "Database connection failed"
- Nguyên nhân: plugin SQLite (sqldrivers) không được tìm thấy tại runtime.
- Giải pháp:
  - Chạy ứng dụng từ Qt Creator (thường tự thiết lập PATH).
  - Khi chạy ngoài Qt Creator, sử dụng:
    - Windows: `windeployqt path\to\EduLibraryManager.exe` để copy dll & plugins.
    - macOS: `macdeployqt /path/to/EduLibraryManager.app`.
  - Trên Linux: cài package Qt SQLite plugin (ví dụ: `libqt5sql5-sqlite` trên Debian/Ubuntu).

2) Không thể tạo/ghi `library.db`
- Nguyên nhân: thiếu quyền ghi tại thư mục chạy.
- Giải pháp: chạy ứng dụng trong thư mục người dùng có quyền ghi, hoặc chỉ định đường dẫn DB khác khi khởi tạo.

3) Resource / CSV không nạp được
- Nguyên nhân: `Resources.qrc` không chứa `books.csv` hoặc resource không được biên dịch.
- Giải pháp: kiểm tra `Resources.qrc` và .pro (RESOURCES += Resources.qrc), đảm bảo `:/data/books.csv` tồn tại.

4) Lỗi build do case-sensitive paths
- Trên Linux/macOS hệ file phân biệt hoa/thường: kiểm tra đúng tên file và đường dẫn trong .pro.

5) Qt ABI / Compiler mismatch
- Build và chạy bằng cùng Qt kit; không dùng binary build từ kit khác (khác compiler hoặc version).

---

Đóng gói ứng dụng (nhanh)

Windows
- Mở Qt Command Prompt:
```powershell
windeployqt --release path\to\release\EduLibraryManager.exe
```
- Kết quả: copy các .dll, plugins (platforms, sqldrivers) vào thư mục chạy. Đóng gói thư mục đó (zip/installer).

macOS
- Tạo bundle .app và chạy:
```bash
macdeployqt /path/to/EduLibraryManager.app
```

Linux
- Tạo AppImage / Snap / Flatpak hoặc build package (.deb/.rpm).
- Thông thường cần chuẩn bị script để copy các lib Qt nếu target không có Qt.

---

Liên hệ / Ghi chú
- Repo: https://github.com/Trananhkhoa2929/Library_Management_System_On_QT
- Nếu cần, có thể:
  - Chia README thành các file riêng (BUILD.md, ARCHITECTURE.md, CONTRIBUTING.md).
  - Thêm script build (build.sh / build.ps1).
  - Viết test unit cho LibraryService và DatabaseManager.

Cảm ơn bạn đã xem qua EduLibrary Manager!
```
