/****************************************************************************
** Meta object code from reading C++ file 'Mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[29];
    char stringdata0[427];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "on_btnWinMin_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "SltMainPageChanged"
QT_MOC_LITERAL(4, 52, 3), // "dex"
QT_MOC_LITERAL(5, 56, 22), // "SltTrayIconMenuClicked"
QT_MOC_LITERAL(6, 79, 8), // "QAction*"
QT_MOC_LITERAL(7, 88, 6), // "action"
QT_MOC_LITERAL(8, 95, 17), // "SltTrayIcoClicked"
QT_MOC_LITERAL(9, 113, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(10, 147, 6), // "reason"
QT_MOC_LITERAL(11, 154, 10), // "SltQuitApp"
QT_MOC_LITERAL(12, 165, 22), // "on_btnWinClose_clicked"
QT_MOC_LITERAL(13, 188, 11), // "SltTcpReply"
QT_MOC_LITERAL(14, 200, 4), // "type"
QT_MOC_LITERAL(15, 205, 7), // "dataVal"
QT_MOC_LITERAL(16, 213, 12), // "SltTcpStatus"
QT_MOC_LITERAL(17, 226, 5), // "state"
QT_MOC_LITERAL(18, 232, 17), // "SltFriendsClicked"
QT_MOC_LITERAL(19, 250, 7), // "QQCell*"
QT_MOC_LITERAL(20, 258, 6), // "qqcell"
QT_MOC_LITERAL(21, 265, 16), // "SltGroupsClicked"
QT_MOC_LITERAL(22, 282, 26), // "onAddFriendMenuDidSelected"
QT_MOC_LITERAL(23, 309, 25), // "onGroupPopMenuDidSelected"
QT_MOC_LITERAL(24, 335, 14), // "SltSendMessage"
QT_MOC_LITERAL(25, 350, 4), // "json"
QT_MOC_LITERAL(26, 355, 24), // "SltFriendChatWindowClose"
QT_MOC_LITERAL(27, 380, 19), // "PraseAddFriendReply"
QT_MOC_LITERAL(28, 400, 26) // "PraseAddFriendRequistReply"

    },
    "MainWindow\0on_btnWinMin_clicked\0\0"
    "SltMainPageChanged\0dex\0SltTrayIconMenuClicked\0"
    "QAction*\0action\0SltTrayIcoClicked\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0SltQuitApp\0on_btnWinClose_clicked\0"
    "SltTcpReply\0type\0dataVal\0SltTcpStatus\0"
    "state\0SltFriendsClicked\0QQCell*\0qqcell\0"
    "SltGroupsClicked\0onAddFriendMenuDidSelected\0"
    "onGroupPopMenuDidSelected\0SltSendMessage\0"
    "json\0SltFriendChatWindowClose\0"
    "PraseAddFriendReply\0PraseAddFriendRequistReply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    1,   95,    2, 0x08 /* Private */,
       5,    1,   98,    2, 0x08 /* Private */,
       8,    1,  101,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    2,  106,    2, 0x08 /* Private */,
      16,    1,  111,    2, 0x08 /* Private */,
      18,    1,  114,    2, 0x08 /* Private */,
      21,    1,  117,    2, 0x08 /* Private */,
      22,    1,  120,    2, 0x08 /* Private */,
      23,    1,  123,    2, 0x08 /* Private */,
      24,    2,  126,    2, 0x08 /* Private */,
      26,    0,  131,    2, 0x08 /* Private */,
      27,    1,  132,    2, 0x08 /* Private */,
      28,    1,  135,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::QJsonValue,   14,   15,
    QMetaType::Void, QMetaType::UChar,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::UChar, QMetaType::QJsonValue,   14,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonValue,   15,
    QMetaType::Void, QMetaType::QJsonValue,   15,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnWinMin_clicked(); break;
        case 1: _t->SltMainPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SltTrayIconMenuClicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->SltTrayIcoClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 4: _t->SltQuitApp(); break;
        case 5: _t->on_btnWinClose_clicked(); break;
        case 6: _t->SltTcpReply((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< const QJsonValue(*)>(_a[2]))); break;
        case 7: _t->SltTcpStatus((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 8: _t->SltFriendsClicked((*reinterpret_cast< QQCell*(*)>(_a[1]))); break;
        case 9: _t->SltGroupsClicked((*reinterpret_cast< QQCell*(*)>(_a[1]))); break;
        case 10: _t->onAddFriendMenuDidSelected((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 11: _t->onGroupPopMenuDidSelected((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 12: _t->SltSendMessage((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< const QJsonValue(*)>(_a[2]))); break;
        case 13: _t->SltFriendChatWindowClose(); break;
        case 14: _t->PraseAddFriendReply((*reinterpret_cast< const QJsonValue(*)>(_a[1]))); break;
        case 15: _t->PraseAddFriendRequistReply((*reinterpret_cast< const QJsonValue(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &CustomMoveWidget::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return CustomMoveWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomMoveWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
