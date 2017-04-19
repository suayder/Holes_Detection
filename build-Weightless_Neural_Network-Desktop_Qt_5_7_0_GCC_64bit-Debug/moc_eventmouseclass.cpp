/****************************************************************************
** Meta object code from reading C++ file 'eventmouseclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Weightless_Neural_Network/eventmouseclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eventmouseclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EventMouseClass_t {
    QByteArrayData data[5];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EventMouseClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EventMouseClass_t qt_meta_stringdata_EventMouseClass = {
    {
QT_MOC_LITERAL(0, 0, 15), // "EventMouseClass"
QT_MOC_LITERAL(1, 16, 13), // "Mouse_Pressed"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "Mouse_Move"
QT_MOC_LITERAL(4, 42, 14) // "Mouse_Released"

    },
    "EventMouseClass\0Mouse_Pressed\0\0"
    "Mouse_Move\0Mouse_Released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EventMouseClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EventMouseClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EventMouseClass *_t = static_cast<EventMouseClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Mouse_Pressed(); break;
        case 1: _t->Mouse_Move(); break;
        case 2: _t->Mouse_Released(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EventMouseClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EventMouseClass::Mouse_Pressed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (EventMouseClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EventMouseClass::Mouse_Move)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (EventMouseClass::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EventMouseClass::Mouse_Released)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EventMouseClass::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_EventMouseClass.data,
      qt_meta_data_EventMouseClass,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EventMouseClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EventMouseClass::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EventMouseClass.stringdata0))
        return static_cast<void*>(const_cast< EventMouseClass*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int EventMouseClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void EventMouseClass::Mouse_Pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void EventMouseClass::Mouse_Move()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void EventMouseClass::Mouse_Released()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
