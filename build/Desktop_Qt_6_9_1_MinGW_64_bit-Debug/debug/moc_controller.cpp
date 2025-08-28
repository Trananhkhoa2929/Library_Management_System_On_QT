/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../controller.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10ControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto Controller::qt_create_metaobjectdata<qt_meta_tag_ZN10ControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Controller",
        "error",
        "",
        "string",
        "error_login",
        "studentLoggedin",
        "Student",
        "publisherLoggedin",
        "Publisher",
        "setCurrentWidget",
        "index",
        "error_noBook",
        "bookInfo",
        "Book",
        "error_return",
        "bookReturned",
        "borrowedBooks",
        "vector<Book>",
        "booksFound",
        "searchedBooks",
        "vector<string>",
        "log_in",
        "name",
        "password",
        "choice",
        "sign_up",
        "Upload_book",
        "updatePublisher",
        "updateStudent",
        "searchBookByName",
        "searchBookByType",
        "searchBookByPrice",
        "searchBookByPub",
        "borrowBook",
        "returnBook",
        "aa",
        "getBookInfo",
        "getSearchHistory",
        "getAllBooks",
        "map<string,string>"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'error'
        QtMocHelpers::SignalData<void(string)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'error_login'
        QtMocHelpers::SignalData<void(string)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'studentLoggedin'
        QtMocHelpers::SignalData<void(Student)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 2 },
        }}),
        // Signal 'publisherLoggedin'
        QtMocHelpers::SignalData<void(Publisher)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 2 },
        }}),
        // Signal 'setCurrentWidget'
        QtMocHelpers::SignalData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 },
        }}),
        // Signal 'error_noBook'
        QtMocHelpers::SignalData<void(string)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'bookInfo'
        QtMocHelpers::SignalData<void(Book)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 2 },
        }}),
        // Signal 'error_return'
        QtMocHelpers::SignalData<void(string)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'bookReturned'
        QtMocHelpers::SignalData<void(int, int)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 }, { QMetaType::Int, 2 },
        }}),
        // Signal 'borrowedBooks'
        QtMocHelpers::SignalData<void(vector<Book>)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 2 },
        }}),
        // Signal 'booksFound'
        QtMocHelpers::SignalData<void(vector<Book>)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 2 },
        }}),
        // Signal 'searchedBooks'
        QtMocHelpers::SignalData<void(vector<string>)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 2 },
        }}),
        // Slot 'log_in'
        QtMocHelpers::SlotData<void(string, string, int)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 22 }, { 0x80000000 | 3, 23 }, { QMetaType::Int, 24 },
        }}),
        // Slot 'sign_up'
        QtMocHelpers::SlotData<void(string, string, string, int)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'Upload_book'
        QtMocHelpers::SlotData<void(string, string, string, int)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'updatePublisher'
        QtMocHelpers::SlotData<void(string, string, string, string, int)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
            { QMetaType::Int, 2 },
        }}),
        // Slot 'updateStudent'
        QtMocHelpers::SlotData<void(string, string, string, string, int)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
            { QMetaType::Int, 2 },
        }}),
        // Slot 'searchBookByName'
        QtMocHelpers::SlotData<void(string, string)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Slot 'searchBookByType'
        QtMocHelpers::SlotData<void(string, string)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Slot 'searchBookByPrice'
        QtMocHelpers::SlotData<void(int, string)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Slot 'searchBookByPub'
        QtMocHelpers::SlotData<void(string, string)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Slot 'borrowBook'
        QtMocHelpers::SlotData<void(string, string, int)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'returnBook'
        QtMocHelpers::SlotData<void(string, string)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Slot 'aa'
        QtMocHelpers::SlotData<void(string)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Slot 'getBookInfo'
        QtMocHelpers::SlotData<void(string)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Slot 'getSearchHistory'
        QtMocHelpers::SlotData<void(string)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Slot 'getAllBooks'
        QtMocHelpers::SlotData<map<string,string>()>(38, 2, QMC::AccessPublic, 0x80000000 | 39),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Controller, qt_meta_tag_ZN10ControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Controller::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10ControllerE_t>.metaTypes,
    nullptr
} };

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Controller *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 1: _t->error_login((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 2: _t->studentLoggedin((*reinterpret_cast< std::add_pointer_t<Student>>(_a[1]))); break;
        case 3: _t->publisherLoggedin((*reinterpret_cast< std::add_pointer_t<Publisher>>(_a[1]))); break;
        case 4: _t->setCurrentWidget((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->error_noBook((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 6: _t->bookInfo((*reinterpret_cast< std::add_pointer_t<Book>>(_a[1]))); break;
        case 7: _t->error_return((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 8: _t->bookReturned((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 9: _t->borrowedBooks((*reinterpret_cast< std::add_pointer_t<vector<Book>>>(_a[1]))); break;
        case 10: _t->booksFound((*reinterpret_cast< std::add_pointer_t<vector<Book>>>(_a[1]))); break;
        case 11: _t->searchedBooks((*reinterpret_cast< std::add_pointer_t<vector<string>>>(_a[1]))); break;
        case 12: _t->log_in((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 13: _t->sign_up((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 14: _t->Upload_book((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 15: _t->updatePublisher((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 16: _t->updateStudent((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 17: _t->searchBookByName((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 18: _t->searchBookByType((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 19: _t->searchBookByPrice((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 20: _t->searchBookByPub((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 21: _t->borrowBook((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 22: _t->returnBook((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 23: _t->aa((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 24: _t->getBookInfo((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 25: _t->getSearchHistory((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 26: { map<string,string> _r = _t->getAllBooks();
            if (_a[0]) *reinterpret_cast< map<string,string>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(string )>(_a, &Controller::error, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(string )>(_a, &Controller::error_login, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(Student )>(_a, &Controller::studentLoggedin, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(Publisher )>(_a, &Controller::publisherLoggedin, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(int )>(_a, &Controller::setCurrentWidget, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(string )>(_a, &Controller::error_noBook, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(Book )>(_a, &Controller::bookInfo, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(string )>(_a, &Controller::error_return, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(int , int )>(_a, &Controller::bookReturned, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(vector<Book> )>(_a, &Controller::borrowedBooks, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(vector<Book> )>(_a, &Controller::booksFound, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(vector<string> )>(_a, &Controller::searchedBooks, 11))
            return;
    }
}

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void Controller::error(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Controller::error_login(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Controller::studentLoggedin(Student _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Controller::publisherLoggedin(Publisher _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Controller::setCurrentWidget(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Controller::error_noBook(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Controller::bookInfo(Book _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void Controller::error_return(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void Controller::bookReturned(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void Controller::borrowedBooks(vector<Book> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void Controller::booksFound(vector<Book> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void Controller::searchedBooks(vector<string> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}
QT_WARNING_POP
