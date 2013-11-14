/****************************************************************************
** Meta object code from reading C++ file 'hgstackedwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hui/hgstackedwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hgstackedwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HGStackedWidget_t {
    QByteArrayData data[23];
    char stringdata[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_HGStackedWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_HGStackedWidget_t qt_meta_stringdata_HGStackedWidget = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 23),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 25),
QT_MOC_LITERAL(4, 67, 8),
QT_MOC_LITERAL(5, 76, 8),
QT_MOC_LITERAL(6, 85, 19),
QT_MOC_LITERAL(7, 105, 11),
QT_MOC_LITERAL(8, 117, 26),
QT_MOC_LITERAL(9, 144, 5),
QT_MOC_LITERAL(10, 150, 9),
QT_MOC_LITERAL(11, 160, 15),
QT_MOC_LITERAL(12, 176, 5),
QT_MOC_LITERAL(13, 182, 18),
QT_MOC_LITERAL(14, 201, 15),
QT_MOC_LITERAL(15, 217, 6),
QT_MOC_LITERAL(16, 224, 10),
QT_MOC_LITERAL(17, 235, 10),
QT_MOC_LITERAL(18, 246, 10),
QT_MOC_LITERAL(19, 257, 16),
QT_MOC_LITERAL(20, 274, 19),
QT_MOC_LITERAL(21, 294, 9),
QT_MOC_LITERAL(22, 304, 10)
    },
    "HGStackedWidget\0onAnimationStateChanged\0"
    "\0QAbstractAnimation::State\0newState\0"
    "oldState\0onAnimationFinished\0resizeEvent\0"
    "QGraphicsSceneResizeEvent*\0event\0"
    "construct\0setCurrentIndex\0index\0"
    "setCurrentHGWidget\0const HGWidget*\0"
    "widget\0effectType\0EffectType\0NullEffect\0"
    "SlideInOutEffect\0ChildWidgetSizeMode\0"
    "fixedMode\0adjustMode\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HGStackedWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       1,   60, // properties
       2,   63, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x09,
       6,    0,   49,    2, 0x09,
       7,    1,   50,    2, 0x09,
      10,    0,   53,    2, 0x09,

 // methods: name, argc, parameters, tag, flags
      11,    1,   54,    2, 0x02,
      13,    1,   57,    2, 0x02,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 14,   15,

 // properties: name, type, flags
      16, 0x80000000 | 17, 0x0009510b,

 // enums: name, flags, count, data
      17, 0x0,    2,   71,
      20, 0x0,    2,   75,

 // enum data: key, value
      18, uint(HGStackedWidget::NullEffect),
      19, uint(HGStackedWidget::SlideInOutEffect),
      21, uint(HGStackedWidget::fixedMode),
      22, uint(HGStackedWidget::adjustMode),

       0        // eod
};

void HGStackedWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HGStackedWidget *_t = static_cast<HGStackedWidget *>(_o);
        switch (_id) {
        case 0: _t->onAnimationStateChanged((*reinterpret_cast< QAbstractAnimation::State(*)>(_a[1])),(*reinterpret_cast< QAbstractAnimation::State(*)>(_a[2]))); break;
        case 1: _t->onAnimationFinished(); break;
        case 2: _t->resizeEvent((*reinterpret_cast< QGraphicsSceneResizeEvent*(*)>(_a[1]))); break;
        case 3: _t->construct(); break;
        case 4: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setCurrentHGWidget((*reinterpret_cast< const HGWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HGStackedWidget::staticMetaObject = {
    { &HGWidget::staticMetaObject, qt_meta_stringdata_HGStackedWidget.data,
      qt_meta_data_HGStackedWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *HGStackedWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HGStackedWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HGStackedWidget.stringdata))
        return static_cast<void*>(const_cast< HGStackedWidget*>(this));
    return HGWidget::qt_metacast(_clname);
}

int HGStackedWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = HGWidget::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< EffectType*>(_v) = effectType(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setEffectType(*reinterpret_cast< EffectType*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
