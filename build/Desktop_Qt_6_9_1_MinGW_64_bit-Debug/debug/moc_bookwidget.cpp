/****************************************************************************
** Meta object code from reading C++ file 'bookwidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../GUI/bookwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bookwidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10BookWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto BookWidget::qt_create_metaobjectdata<qt_meta_tag_ZN10BookWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BookWidget",
        "setCurrentWidget",
        "",
        "getBookInfo",
        "string",
        "Book",
        "borrowBook",
        "backIsClicked",
        "borrowIsClicked",
        "bookInfo",
        "error",
        "okkkButtonClicked",
        "setCurrentBook",
        "b",
        "setLoggedInUserName",
        "name"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'setCurrentWidget'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'getBookInfo'
        QtMocHelpers::SignalData<void(string)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 },
        }}),
        // Signal 'getBookInfo'
        QtMocHelpers::SignalData<void(Book)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 2 },
        }}),
        // Signal 'borrowBook'
        QtMocHelpers::SignalData<void(string, string, int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 }, { 0x80000000 | 4, 2 }, { QMetaType::Int, 2 },
        }}),
        // Slot 'backIsClicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'borrowIsClicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'bookInfo'
        QtMocHelpers::SlotData<void(Book)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 2 },
        }}),
        // Slot 'error'
        QtMocHelpers::SlotData<void(string)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 2 },
        }}),
        // Slot 'okkkButtonClicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setCurrentBook'
        QtMocHelpers::SlotData<void(Book)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 13 },
        }}),
        // Slot 'setLoggedInUserName'
        QtMocHelpers::SlotData<void(string)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 15 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BookWidget, qt_meta_tag_ZN10BookWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BookWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BookWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BookWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10BookWidgetE_t>.metaTypes,
    nullptr
} };

void BookWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BookWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->setCurrentWidget((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->getBookInfo((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 2: _t->getBookInfo((*reinterpret_cast< std::add_pointer_t<Book>>(_a[1]))); break;
        case 3: _t->borrowBook((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->backIsClicked(); break;
        case 5: _t->borrowIsClicked(); break;
        case 6: _t->bookInfo((*reinterpret_cast< std::add_pointer_t<Book>>(_a[1]))); break;
        case 7: _t->error((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 8: _t->okkkButtonClicked(); break;
        case 9: _t->setCurrentBook((*reinterpret_cast< std::add_pointer_t<Book>>(_a[1]))); break;
        case 10: _t->setLoggedInUserName((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BookWidget::*)(int )>(_a, &BookWidget::setCurrentWidget, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BookWidget::*)(string )>(_a, &BookWidget::getBookInfo, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BookWidget::*)(Book )>(_a, &BookWidget::getBookInfo, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BookWidget::*)(string , string , int )>(_a, &BookWidget::borrowBook, 3))
            return;
    }
}

const QMetaObject *BookWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BookWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10BookWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BookWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BookWidget::setCurrentWidget(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void BookWidget::getBookInfo(string _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void BookWidget::getBookInfo(Book _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void BookWidget::borrowBook(string _t1, string _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
