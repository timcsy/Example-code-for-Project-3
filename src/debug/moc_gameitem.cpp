/****************************************************************************
** Meta object code from reading C++ file 'gameitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gameitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameItem_t {
    QByteArrayData data[7];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameItem_t qt_meta_stringdata_GameItem = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GameItem"
QT_MOC_LITERAL(1, 9, 14), // "nextItemSignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "dieSignal"
QT_MOC_LITERAL(4, 35, 11), // "scoreSignal"
QT_MOC_LITERAL(5, 47, 5), // "score"
QT_MOC_LITERAL(6, 53, 5) // "paint"

    },
    "GameItem\0nextItemSignal\0\0dieSignal\0"
    "scoreSignal\0score\0paint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void GameItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameItem *_t = static_cast<GameItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextItemSignal(); break;
        case 1: _t->dieSignal(); break;
        case 2: _t->scoreSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->paint(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GameItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameItem::nextItemSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (GameItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameItem::dieSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (GameItem::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameItem::scoreSignal)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject GameItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GameItem.data,
      qt_meta_data_GameItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GameItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GameItem.stringdata0))
        return static_cast<void*>(const_cast< GameItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int GameItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GameItem::nextItemSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void GameItem::dieSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void GameItem::scoreSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
