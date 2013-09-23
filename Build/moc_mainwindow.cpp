/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata[438];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 20),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 21),
QT_MOC_LITERAL(4, 55, 22),
QT_MOC_LITERAL(5, 78, 17),
QT_MOC_LITERAL(6, 96, 24),
QT_MOC_LITERAL(7, 121, 24),
QT_MOC_LITERAL(8, 146, 22),
QT_MOC_LITERAL(9, 169, 21),
QT_MOC_LITERAL(10, 191, 25),
QT_MOC_LITERAL(11, 217, 25),
QT_MOC_LITERAL(12, 243, 23),
QT_MOC_LITERAL(13, 267, 25),
QT_MOC_LITERAL(14, 293, 20),
QT_MOC_LITERAL(15, 314, 28),
QT_MOC_LITERAL(16, 343, 22),
QT_MOC_LITERAL(17, 366, 22),
QT_MOC_LITERAL(18, 389, 22),
QT_MOC_LITERAL(19, 412, 24)
    },
    "MainWindow\0on_NewFile_triggered\0\0"
    "on_SaveFile_triggered\0on_CloseFile_triggered\0"
    "on_Exit_triggered\0on_createField_triggered\0"
    "on_modifyField_triggered\0"
    "on_listField_triggered\0on_OpenFile_triggered\0"
    "on_insertRecord_triggered\0"
    "on_searchRecord_triggered\0"
    "on_listRecord_triggered\0"
    "on_deleteRecord_triggered\0"
    "on_reindex_triggered\0on_doSimpleIndexes_triggered\0"
    "on_PrintFile_triggered\0on_exportXML_triggered\0"
    "on_importXML_triggered\0on_crossTables_triggered\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08,
       3,    0,  105,    2, 0x08,
       4,    0,  106,    2, 0x08,
       5,    0,  107,    2, 0x08,
       6,    0,  108,    2, 0x08,
       7,    0,  109,    2, 0x08,
       8,    0,  110,    2, 0x08,
       9,    0,  111,    2, 0x08,
      10,    0,  112,    2, 0x08,
      11,    0,  113,    2, 0x08,
      12,    0,  114,    2, 0x08,
      13,    0,  115,    2, 0x08,
      14,    0,  116,    2, 0x08,
      15,    0,  117,    2, 0x08,
      16,    0,  118,    2, 0x08,
      17,    0,  119,    2, 0x08,
      18,    0,  120,    2, 0x08,
      19,    0,  121,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_NewFile_triggered(); break;
        case 1: _t->on_SaveFile_triggered(); break;
        case 2: _t->on_CloseFile_triggered(); break;
        case 3: _t->on_Exit_triggered(); break;
        case 4: _t->on_createField_triggered(); break;
        case 5: _t->on_modifyField_triggered(); break;
        case 6: _t->on_listField_triggered(); break;
        case 7: _t->on_OpenFile_triggered(); break;
        case 8: _t->on_insertRecord_triggered(); break;
        case 9: _t->on_searchRecord_triggered(); break;
        case 10: _t->on_listRecord_triggered(); break;
        case 11: _t->on_deleteRecord_triggered(); break;
        case 12: _t->on_reindex_triggered(); break;
        case 13: _t->on_doSimpleIndexes_triggered(); break;
        case 14: _t->on_PrintFile_triggered(); break;
        case 15: _t->on_exportXML_triggered(); break;
        case 16: _t->on_importXML_triggered(); break;
        case 17: _t->on_crossTables_triggered(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
