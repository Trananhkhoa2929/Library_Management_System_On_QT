/****************************************************************************
** Meta object code from reading C++ file 'studentwidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../GUI/studentwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'studentwidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13StudentWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto StudentWidget::qt_create_metaobjectdata<qt_meta_tag_ZN13StudentWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "StudentWidget",
        "updateStudent",
        "",
        "string",
        "getBookInfo",
        "Book",
        "returnBook",
        "aa",
        "searchBookByName",
        "searchBookByType",
        "searchBookByPrice",
        "searchBookByPub",
        "getSearchHistory",
        "setCurrentWidget",
        "setLoggedInUserName",
        "getAllBooks",
        "map<string,string>",
        "studentLoggedIn",
        "Student",
        "ButtonClicked",
        "QAction*",
        "action",
        "editButtonClicked",
        "okButtonClicked",
        "backButtonClicked",
        "okkButtonClicked",
        "increaseIsClicked",
        "error_return",
        "bookReturned",
        "borrowedBooks",
        "vector<Book>",
        "ok1ButtonClicked",
        "okButtonhClicked",
        "nameButtonClicked",
        "typeButtonClicked",
        "priceButtonClicked",
        "pubButtonClicked",
        "doneButtonClicked",
        "booksFound",
        "searchedBooks",
        "vector<string>",
        "bookClicked",
        "name"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'updateStudent'
        QtMocHelpers::SignalData<void(string, string, string, string, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
            { QMetaType::Int, 2 },
        }}),
        // Signal 'getBookInfo'
        QtMocHelpers::SignalData<void(string)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'getBookInfo'
        QtMocHelpers::SignalData<void(Book)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 2 },
        }}),
        // Signal 'returnBook'
        QtMocHelpers::SignalData<void(string, string)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Signal 'aa'
        QtMocHelpers::SignalData<void(string)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'searchBookByName'
        QtMocHelpers::SignalData<void(string, string)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Signal 'searchBookByType'
        QtMocHelpers::SignalData<void(string, string)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Signal 'searchBookByPrice'
        QtMocHelpers::SignalData<void(int, string)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Signal 'searchBookByPub'
        QtMocHelpers::SignalData<void(string, string)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
        }}),
        // Signal 'getSearchHistory'
        QtMocHelpers::SignalData<void(string)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'setCurrentWidget'
        QtMocHelpers::SignalData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'setLoggedInUserName'
        QtMocHelpers::SignalData<void(string)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Signal 'getAllBooks'
        QtMocHelpers::SignalData<map<string,string>()>(15, 2, QMC::AccessPublic, 0x80000000 | 16),
        // Slot 'studentLoggedIn'
        QtMocHelpers::SlotData<void(Student)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 18, 2 },
        }}),
        // Slot 'ButtonClicked'
        QtMocHelpers::SlotData<void(QAction *)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 21 },
        }}),
        // Slot 'editButtonClicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'okButtonClicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'backButtonClicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'okkButtonClicked'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'increaseIsClicked'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'error_return'
        QtMocHelpers::SlotData<void(string)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Slot 'bookReturned'
        QtMocHelpers::SlotData<void(int, int)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'borrowedBooks'
        QtMocHelpers::SlotData<void(vector<Book>)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 30, 2 },
        }}),
        // Slot 'ok1ButtonClicked'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'okButtonhClicked'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'nameButtonClicked'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'typeButtonClicked'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'priceButtonClicked'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'pubButtonClicked'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'doneButtonClicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'booksFound'
        QtMocHelpers::SlotData<void(vector<Book>)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 30, 2 },
        }}),
        // Slot 'searchedBooks'
        QtMocHelpers::SlotData<void(vector<string>)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 40, 2 },
        }}),
        // Slot 'bookClicked'
        QtMocHelpers::SlotData<void(string)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 42 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<StudentWidget, qt_meta_tag_ZN13StudentWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject StudentWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13StudentWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13StudentWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13StudentWidgetE_t>.metaTypes,
    nullptr
} };

void StudentWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<StudentWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->updateStudent((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 1: _t->getBookInfo((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 2: _t->getBookInfo((*reinterpret_cast< std::add_pointer_t<Book>>(_a[1]))); break;
        case 3: _t->returnBook((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 4: _t->aa((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 5: _t->searchBookByName((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 6: _t->searchBookByType((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 7: _t->searchBookByPrice((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 8: _t->searchBookByPub((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 9: _t->getSearchHistory((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 10: _t->setCurrentWidget((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->setLoggedInUserName((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 12: { map<string,string> _r = _t->getAllBooks();
            if (_a[0]) *reinterpret_cast< map<string,string>*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->studentLoggedIn((*reinterpret_cast< std::add_pointer_t<Student>>(_a[1]))); break;
        case 14: _t->ButtonClicked((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 15: _t->editButtonClicked(); break;
        case 16: _t->okButtonClicked(); break;
        case 17: _t->backButtonClicked(); break;
        case 18: _t->okkButtonClicked(); break;
        case 19: _t->increaseIsClicked(); break;
        case 20: _t->error_return((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 21: _t->bookReturned((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 22: _t->borrowedBooks((*reinterpret_cast< std::add_pointer_t<vector<Book>>>(_a[1]))); break;
        case 23: _t->ok1ButtonClicked(); break;
        case 24: _t->okButtonhClicked(); break;
        case 25: _t->nameButtonClicked(); break;
        case 26: _t->typeButtonClicked(); break;
        case 27: _t->priceButtonClicked(); break;
        case 28: _t->pubButtonClicked(); break;
        case 29: _t->doneButtonClicked(); break;
        case 30: _t->booksFound((*reinterpret_cast< std::add_pointer_t<vector<Book>>>(_a[1]))); break;
        case 31: _t->searchedBooks((*reinterpret_cast< std::add_pointer_t<vector<string>>>(_a[1]))); break;
        case 32: _t->bookClicked((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string , string , string , string , int )>(_a, &StudentWidget::updateStudent, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string )>(_a, &StudentWidget::getBookInfo, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(Book )>(_a, &StudentWidget::getBookInfo, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string , string )>(_a, &StudentWidget::returnBook, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string )>(_a, &StudentWidget::aa, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string , string )>(_a, &StudentWidget::searchBookByName, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string , string )>(_a, &StudentWidget::searchBookByType, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(int , string )>(_a, &StudentWidget::searchBookByPrice, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string , string )>(_a, &StudentWidget::searchBookByPub, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string )>(_a, &StudentWidget::getSearchHistory, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(int )>(_a, &StudentWidget::setCurrentWidget, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudentWidget::*)(string )>(_a, &StudentWidget::setLoggedInUserName, 11))
            return;
        if (QtMocHelpers::indexOfMethod<map<string,string> (StudentWidget::*)()>(_a, &StudentWidget::getAllBooks, 12))
            return;
    }
}

const QMetaObject *StudentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StudentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13StudentWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int StudentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void StudentWidget::updateStudent(string _t1, string _t2, string _t3, string _t4, int _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4, _t5);
}

// SIGNAL 1
void StudentWidget::getBookInfo(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void StudentWidget::getBookInfo(Book _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void StudentWidget::returnBook(string _t1, string _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void StudentWidget::aa(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void StudentWidget::searchBookByName(string _t1, string _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void StudentWidget::searchBookByType(string _t1, string _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void StudentWidget::searchBookByPrice(int _t1, string _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void StudentWidget::searchBookByPub(string _t1, string _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void StudentWidget::getSearchHistory(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void StudentWidget::setCurrentWidget(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void StudentWidget::setLoggedInUserName(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
map<string,string> StudentWidget::getAllBooks()
{
    map<string,string> _t0{};
    QMetaObject::activate<map<string,string>>(this, &staticMetaObject, 12, std::addressof(_t0));
    return _t0;
}
QT_WARNING_POP
