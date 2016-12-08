/****************************************************************************
** Meta object code from reading C++ file 'fieldwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LifeGame/fieldwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fieldwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FieldWidget_t {
    QByteArrayData data[9];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FieldWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FieldWidget_t qt_meta_stringdata_FieldWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FieldWidget"
QT_MOC_LITERAL(1, 12, 8), // "stepOnce"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "stepN"
QT_MOC_LITERAL(4, 28, 1), // "N"
QT_MOC_LITERAL(5, 30, 6), // "zoomIn"
QT_MOC_LITERAL(6, 37, 7), // "zoomOut"
QT_MOC_LITERAL(7, 45, 10), // "clearField"
QT_MOC_LITERAL(8, 56, 14) // "randomizeField"

    },
    "FieldWidget\0stepOnce\0\0stepN\0N\0zoomIn\0"
    "zoomOut\0clearField\0randomizeField"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FieldWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FieldWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FieldWidget *_t = static_cast<FieldWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stepOnce(); break;
        case 1: _t->stepN((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zoomIn(); break;
        case 3: _t->zoomOut(); break;
        case 4: _t->clearField(); break;
        case 5: _t->randomizeField(); break;
        default: ;
        }
    }
}

const QMetaObject FieldWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FieldWidget.data,
      qt_meta_data_FieldWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FieldWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FieldWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FieldWidget.stringdata0))
        return static_cast<void*>(const_cast< FieldWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FieldWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
