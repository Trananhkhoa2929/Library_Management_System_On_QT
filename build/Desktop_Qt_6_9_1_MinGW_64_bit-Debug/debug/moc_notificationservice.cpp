/****************************************************************************
** Meta object code from reading C++ file 'notificationservice.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Services/notificationservice.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notificationservice.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN19NotificationServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto NotificationService::qt_create_metaobjectdata<qt_meta_tag_ZN19NotificationServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NotificationService",
        "notificationSent",
        "",
        "recipient",
        "NotificationType",
        "type",
        "success",
        "notificationFailed",
        "error",
        "serviceStatusChanged",
        "enabled",
        "onScheduleTimer"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'notificationSent'
        QtMocHelpers::SignalData<void(const QString &, NotificationType, bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { 0x80000000 | 4, 5 }, { QMetaType::Bool, 6 },
        }}),
        // Signal 'notificationFailed'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'serviceStatusChanged'
        QtMocHelpers::SignalData<void(bool)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'onScheduleTimer'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NotificationService, qt_meta_tag_ZN19NotificationServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NotificationService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NotificationServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NotificationServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19NotificationServiceE_t>.metaTypes,
    nullptr
} };

void NotificationService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NotificationService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->notificationSent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<NotificationType>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 1: _t->notificationFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->serviceStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->onScheduleTimer(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NotificationService::*)(const QString & , NotificationType , bool )>(_a, &NotificationService::notificationSent, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NotificationService::*)(const QString & , const QString & )>(_a, &NotificationService::notificationFailed, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NotificationService::*)(bool )>(_a, &NotificationService::serviceStatusChanged, 2))
            return;
    }
}

const QMetaObject *NotificationService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotificationService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NotificationServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NotificationService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NotificationService::notificationSent(const QString & _t1, NotificationType _t2, bool _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}

// SIGNAL 1
void NotificationService::notificationFailed(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void NotificationService::serviceStatusChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
