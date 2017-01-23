/****************************************************************************
** Meta object code from reading C++ file 'menu_widget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "menu_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menu_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Menu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      16,    5,    5,    5, 0x05,
      27,    5,    5,    5, 0x05,
      38,    5,    5,    5, 0x05,
      66,   51,    5,    5, 0x05,
      82,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      96,    5,    5,    5, 0x08,
     111,    5,    5,    5, 0x08,
     132,    5,    5,    5, 0x08,
     144,    5,    5,    5, 0x08,
     157,    5,    5,    5, 0x08,
     169,    5,    5,    5, 0x08,
     180,    5,    5,    5, 0x08,
     194,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Menu[] = {
    "Menu\0\0RunGame()\0StopGame()\0MakeStep()\0"
    "ClearFeild()\0length_,width_\0Resize(int,int)\0"
    "WriteToFile()\0setLabelStop()\0"
    "setLabelInProgress()\0throwStep()\0"
    "throwClear()\0throwStop()\0throwRun()\0"
    "throwResize()\0throwWrite()\0"
};

void Menu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Menu *_t = static_cast<Menu *>(_o);
        switch (_id) {
        case 0: _t->RunGame(); break;
        case 1: _t->StopGame(); break;
        case 2: _t->MakeStep(); break;
        case 3: _t->ClearFeild(); break;
        case 4: _t->Resize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->WriteToFile(); break;
        case 6: _t->setLabelStop(); break;
        case 7: _t->setLabelInProgress(); break;
        case 8: _t->throwStep(); break;
        case 9: _t->throwClear(); break;
        case 10: _t->throwStop(); break;
        case 11: _t->throwRun(); break;
        case 12: _t->throwResize(); break;
        case 13: _t->throwWrite(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Menu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Menu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Menu,
      qt_meta_data_Menu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Menu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Menu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Menu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Menu))
        return static_cast<void*>(const_cast< Menu*>(this));
    return QWidget::qt_metacast(_clname);
}

int Menu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Menu::RunGame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Menu::StopGame()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Menu::MakeStep()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Menu::ClearFeild()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Menu::Resize(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Menu::WriteToFile()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
