/****************************************************************************
** Meta object code from reading C++ file 'autypermain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../autypermain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autypermain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AutyperMain_t {
    QByteArrayData data[17];
    char stringdata0[367];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutyperMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutyperMain_t qt_meta_stringdata_AutyperMain = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AutyperMain"
QT_MOC_LITERAL(1, 12, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 17), // "handle_voice2text"
QT_MOC_LITERAL(4, 55, 20), // "Voice2Text::CResult*"
QT_MOC_LITERAL(5, 76, 3), // "res"
QT_MOC_LITERAL(6, 80, 18), // "handleAbortRequest"
QT_MOC_LITERAL(7, 99, 22), // "on_actionNew_triggered"
QT_MOC_LITERAL(8, 122, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(9, 146, 31), // "on_actionChange_Model_triggered"
QT_MOC_LITERAL(10, 178, 31), // "on_actionAppend_Voice_triggered"
QT_MOC_LITERAL(11, 210, 23), // "on_actionHelp_triggered"
QT_MOC_LITERAL(12, 234, 23), // "on_actionInfo_triggered"
QT_MOC_LITERAL(13, 258, 36), // "on_actionCheck_for_Upgrade_tr..."
QT_MOC_LITERAL(14, 295, 23), // "on_actionCopy_triggered"
QT_MOC_LITERAL(15, 319, 24), // "on_actionPaste_triggered"
QT_MOC_LITERAL(16, 344, 22) // "on_actionCut_triggered"

    },
    "AutyperMain\0on_actionOpen_triggered\0"
    "\0handle_voice2text\0Voice2Text::CResult*\0"
    "res\0handleAbortRequest\0on_actionNew_triggered\0"
    "on_actionSave_triggered\0"
    "on_actionChange_Model_triggered\0"
    "on_actionAppend_Voice_triggered\0"
    "on_actionHelp_triggered\0on_actionInfo_triggered\0"
    "on_actionCheck_for_Upgrade_triggered\0"
    "on_actionCopy_triggered\0"
    "on_actionPaste_triggered\0"
    "on_actionCut_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutyperMain[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    1,   80,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
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

void AutyperMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AutyperMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionOpen_triggered(); break;
        case 1: _t->handle_voice2text((*reinterpret_cast< Voice2Text::CResult*(*)>(_a[1]))); break;
        case 2: _t->handleAbortRequest(); break;
        case 3: _t->on_actionNew_triggered(); break;
        case 4: _t->on_actionSave_triggered(); break;
        case 5: _t->on_actionChange_Model_triggered(); break;
        case 6: _t->on_actionAppend_Voice_triggered(); break;
        case 7: _t->on_actionHelp_triggered(); break;
        case 8: _t->on_actionInfo_triggered(); break;
        case 9: _t->on_actionCheck_for_Upgrade_triggered(); break;
        case 10: _t->on_actionCopy_triggered(); break;
        case 11: _t->on_actionPaste_triggered(); break;
        case 12: _t->on_actionCut_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AutyperMain::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_AutyperMain.data,
    qt_meta_data_AutyperMain,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AutyperMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutyperMain::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AutyperMain.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int AutyperMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
