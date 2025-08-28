/****************************************************************************
** Meta object code from reading C++ file 'publisherwidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../GUI/publisherwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'publisherwidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15PublisherWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto PublisherWidget::qt_create_metaobjectdata<qt_meta_tag_ZN15PublisherWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PublisherWidget",
        "addBookData",
        "",
        "string",
        "setCurrentWidget",
        "updatePublisher",
        "bookDataCheck",
        "error",
        "buttonBack",
        "editButtonClicked",
        "okButtonClicked",
        "publisherLoggedIn",
        "Publisher",
        "showInfoBtnClicked",
        "handleToolBar",
        "QAction*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'addBookData'
        QtMocHelpers::SignalData<void(string, string, string, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { QMetaType::Int, 2 },
        }}),
        // Signal 'setCurrentWidget'
        QtMocHelpers::SignalData<void(int)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'updatePublisher'
        QtMocHelpers::SignalData<void(string, string, string, string, int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 }, { 0x80000000 | 3, 2 },
            { QMetaType::Int, 2 },
        }}),
        // Slot 'bookDataCheck'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'error'
        QtMocHelpers::SlotData<void(string)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 2 },
        }}),
        // Slot 'buttonBack'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'editButtonClicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'okButtonClicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'publisherLoggedIn'
        QtMocHelpers::SlotData<void(Publisher)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 2 },
        }}),
        // Slot 'showInfoBtnClicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleToolBar'
        QtMocHelpers::SlotData<void(QAction *)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PublisherWidget, qt_meta_tag_ZN15PublisherWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PublisherWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PublisherWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PublisherWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15PublisherWidgetE_t>.metaTypes,
    nullptr
} };

void PublisherWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PublisherWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addBookData((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 1: _t->setCurrentWidget((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->updatePublisher((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 3: _t->bookDataCheck(); break;
        case 4: _t->error((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        case 5: _t->buttonBack(); break;
        case 6: _t->editButtonClicked(); break;
        case 7: _t->okButtonClicked(); break;
        case 8: _t->publisherLoggedIn((*reinterpret_cast< std::add_pointer_t<Publisher>>(_a[1]))); break;
        case 9: _t->showInfoBtnClicked(); break;
        case 10: _t->handleToolBar((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PublisherWidget::*)(string , string , string , int )>(_a, &PublisherWidget::addBookData, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PublisherWidget::*)(int )>(_a, &PublisherWidget::setCurrentWidget, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PublisherWidget::*)(string , string , string , string , int )>(_a, &PublisherWidget::updatePublisher, 2))
            return;
    }
}

const QMetaObject *PublisherWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PublisherWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PublisherWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PublisherWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void PublisherWidget::addBookData(string _t1, string _t2, string _t3, int _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 1
void PublisherWidget::setCurrentWidget(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void PublisherWidget::updatePublisher(string _t1, string _t2, string _t3, string _t4, int _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3, _t4, _t5);
}
QT_WARNING_POP
