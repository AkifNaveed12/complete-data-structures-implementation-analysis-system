/****************************************************************************
** Meta object code from reading C++ file 'GlobalGuiNotifier.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/gui/GlobalGuiNotifier.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GlobalGuiNotifier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
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
struct qt_meta_tag_ZN17GlobalGuiNotifierE_t {};
} // unnamed namespace

template <> constexpr inline auto GlobalGuiNotifier::qt_create_metaobjectdata<qt_meta_tag_ZN17GlobalGuiNotifierE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GlobalGuiNotifier",
        "stepLogged",
        "",
        "stepNum",
        "message",
        "headerLogged",
        "module",
        "op",
        "resultLogged",
        "errorLogged",
        "stateChanged",
        "arrayStateChanged",
        "const int*",
        "arr",
        "size",
        "activeIndex"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'stepLogged'
        QtMocHelpers::SignalData<void(int, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'headerLogged'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 }, { QMetaType::QString, 7 },
        }}),
        // Signal 'resultLogged'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Signal 'errorLogged'
        QtMocHelpers::SignalData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Signal 'stateChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'arrayStateChanged'
        QtMocHelpers::SignalData<void(const int *, int, int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 }, { QMetaType::Int, 14 }, { QMetaType::Int, 15 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<GlobalGuiNotifier, qt_meta_tag_ZN17GlobalGuiNotifierE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject GlobalGuiNotifier::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17GlobalGuiNotifierE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17GlobalGuiNotifierE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17GlobalGuiNotifierE_t>.metaTypes,
    nullptr
} };

void GlobalGuiNotifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GlobalGuiNotifier *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->stepLogged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->headerLogged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->resultLogged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->errorLogged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->stateChanged(); break;
        case 5: _t->arrayStateChanged((*reinterpret_cast<std::add_pointer_t<const int*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GlobalGuiNotifier::*)(int , const QString & )>(_a, &GlobalGuiNotifier::stepLogged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GlobalGuiNotifier::*)(const QString & , const QString & )>(_a, &GlobalGuiNotifier::headerLogged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GlobalGuiNotifier::*)(const QString & )>(_a, &GlobalGuiNotifier::resultLogged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (GlobalGuiNotifier::*)(const QString & )>(_a, &GlobalGuiNotifier::errorLogged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (GlobalGuiNotifier::*)()>(_a, &GlobalGuiNotifier::stateChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (GlobalGuiNotifier::*)(const int * , int , int )>(_a, &GlobalGuiNotifier::arrayStateChanged, 5))
            return;
    }
}

const QMetaObject *GlobalGuiNotifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GlobalGuiNotifier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17GlobalGuiNotifierE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GlobalGuiNotifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void GlobalGuiNotifier::stepLogged(int _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void GlobalGuiNotifier::headerLogged(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void GlobalGuiNotifier::resultLogged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void GlobalGuiNotifier::errorLogged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void GlobalGuiNotifier::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GlobalGuiNotifier::arrayStateChanged(const int * _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
