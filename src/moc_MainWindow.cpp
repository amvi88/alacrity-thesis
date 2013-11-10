/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.hxx'
**
** Created: Sun Oct 20 19:09:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.hxx"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.hxx' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   11,   11,   11, 0x08,
      57,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     138,  133,   11,   11, 0x08,
     172,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     229,  133,   11,   11, 0x08,
     279,  133,   11,   11, 0x08,
     327,  133,   11,   11, 0x08,
     372,   11,   11,   11, 0x08,
     405,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0timeLimitReached()\0"
    "on_actionLoad_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionExit_triggered()\0"
    "on_pushButton_clicked()\0arg1\0"
    "on_spinBoxFrame_valueChanged(int)\0"
    "on_toolButtonStart_clicked()\0"
    "on_toolButtonStop_clicked()\0"
    "on_comboBoxAlgorithm_currentIndexChanged(QString)\0"
    "on_comboBoxGesture_currentIndexChanged(QString)\0"
    "on_comboBoxHand_currentIndexChanged(QString)\0"
    "endFrameTrackingDuetoTimeLimit()\0"
    "displayPlaybackData()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->timeLimitReached(); break;
        case 1: _t->on_actionLoad_triggered(); break;
        case 2: _t->on_actionSave_triggered(); break;
        case 3: _t->on_actionExit_triggered(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_spinBoxFrame_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_toolButtonStart_clicked(); break;
        case 7: _t->on_toolButtonStop_clicked(); break;
        case 8: _t->on_comboBoxAlgorithm_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_comboBoxGesture_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_comboBoxHand_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->endFrameTrackingDuetoTimeLimit(); break;
        case 12: _t->displayPlaybackData(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::timeLimitReached()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
