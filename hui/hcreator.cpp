#include "hcreator.h"
#include "hresourcemgr.h"
#include "hcore.h"

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QWidget,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() = USEOBJTYPE(QWidget);
    return hSetObjectT<QWidget>(objinfo,new QWidget(parent,(Qt::WindowFlags)param.mVar0.toUInt()));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QPushButton,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QPushButton);
    return hSetObjectT<QPushButton>(objinfo,new QPushButton(param.mVar0.toString(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QCheckBox,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QCheckBox);
    return hSetObjectT<QCheckBox>(objinfo,new QCheckBox(param.mVar0.toString(),parent));
}


IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QRadioButton,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QRadioButton);
    return hSetObjectT<QRadioButton>(objinfo,new QRadioButton(param.mVar0.toString(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QComboBox,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QComboBox);
    return hSetObjectT<QComboBox>(objinfo,new QComboBox(parent));
}

//
IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTreeWidget,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QTreeWidget);
    return hSetObjectT<QTreeWidget>(objinfo,new QTreeWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTreeView,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QTreeView);
    return hSetObjectT<QTreeView>(objinfo,new QTreeView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QListWidget,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QListWidget);
    return hSetObjectT<QListWidget>(objinfo,new QListWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QListView,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QListView);
    return hSetObjectT<QListView>(objinfo,new QListView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTextBrowser,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QTextBrowser);
    return hSetObjectT<QTextBrowser>(objinfo,new QTextBrowser(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QLabel,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QLabel);
    return hSetObjectT<QLabel>(objinfo,new QLabel(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QLineEdit,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QLineEdit);
    return hSetObjectT<QLineEdit>(objinfo,new QLineEdit(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTabBar,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QTabBar);
    return hSetObjectT<QTabBar>(objinfo,new QTabBar(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QStackedWidget,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QStackedWidget);
    return hSetObjectT<QStackedWidget>(objinfo,new QStackedWidget(parent));
}


IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTableWidget,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QTableWidget);
    return hSetObjectT<QTableWidget>(objinfo,new QTableWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTableView,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QTableView);
    return hSetObjectT<QTableView>(objinfo,new QTableView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QSplitter,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QSplitter);
    return hSetObjectT<QSplitter>(objinfo,new QSplitter((Qt::Orientation)param.mVar0.toUInt(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QSlider,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QSlider);
    return hSetObjectT<QSlider>(objinfo,new QSlider((Qt::Orientation)param.mVar0.toUInt(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QDialog,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QDialog);
    return hSetObjectT<QDialog>(objinfo,new QDialog(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTextEdit,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QTextEdit);
    return hSetObjectT<QTextEdit>(objinfo,new QTextEdit(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QDockWidget,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QDockWidget);
    return hSetObjectT<QDockWidget>(objinfo,new QDockWidget(parent));
}

// create based qgraphicsitem
IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsEllipseItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsEllipseItem);
    return new QGraphicsEllipseItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsLineItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsLineItem);
    return new QGraphicsLineItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsPathItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsPathItem);
    return new QGraphicsPathItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsPixmapItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsPixmapItem);
    return new QGraphicsPixmapItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsPolygonItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsPolygonItem);
    return new QGraphicsPolygonItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsRectItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsRectItem);
    return new QGraphicsRectItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsSimpleTextItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsSimpleTextItem);
    return new QGraphicsSimpleTextItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsTextItem,HuiCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);

    param.error()= qy::kHOk;
    param.type() =USEOBJTYPE(QGraphicsTextItem);
    return new QGraphicsTextItem(parent);
}

/// convert function
#define CALL_QVARIANT(TYPE,val,hr) convertQVariant_##TYPE(val,hr)
#define CALL_QSTRING(TYPE,val,hr)  convertQString_##TYPE(val,hr)
#define CALL_CONVERT(TYPE,val,hr) convert_##TYPE(val,hr)

IMPLEMENT_HCONVERT_QSTRING(QString)
{
    *hr = 0;
    return val.value<QString>();
}

IMPLEMENT_HCONVERT_QVARIANT(QString)
{
    return qVariantFromValue(convert_QString(val,hr));
}

IMPLEMENT_HCONVERT(QString)
{
    *hr = 0;
    return val;
}

//QMargins
IMPLEMENT_HCONVERT_QSTRING(QMargins)
{
    *hr = 0;
    QMargins ret = val.value<QMargins>();
    return QString("%1,%2,%3,%4").arg(ret.left()).arg(ret.top()).arg(ret.right()).arg(ret.bottom());
}

IMPLEMENT_HCONVERT_QVARIANT(QMargins)
{
    return qVariantFromValue(convert_QMargins(val,hr));
}

IMPLEMENT_HCONVERT(QMargins)
{
    QStringList s = val.split(",");
    if (s.size() >= 4) {
        *hr = 0;
        QMargins ret(s.at(0).toFloat(), s.at(1).toFloat(), s.at(2).toFloat(), s.at(3).toFloat());
        return ret;
    }
    return QMargins();
}

//QColor
IMPLEMENT_HCONVERT_QSTRING(QColor)
{
    *hr = 0;
    QColor ret = val.value<QColor>();
    return QString("%1,%2,%3,%4").arg(ret.red()).arg(ret.green()).arg(ret.blue()).arg(ret.alpha());
}

IMPLEMENT_HCONVERT_QVARIANT(QColor)
{
    return qVariantFromValue(convert_QColor(val,hr));
}

IMPLEMENT_HCONVERT(QColor)
{
    QColor ret;
    QStringList s = val.split(",");
    if (s.size() >= 3) {
        *hr = 0;
        int red = s[0].toInt();
        int green = s[1].toInt();
        int blue = s[2].toInt();
        int alpha = 255;
        if (s.size() >= 4) {
            alpha = s[3].toInt();
        }
        ret.setRgb(red, green, blue, alpha);
    }
    return ret;
}

//QRectF
IMPLEMENT_HCONVERT_QSTRING(QRectF)
{
    *hr = 0;
    QRectF ret = val.value<QRectF>();
    return QString("%1,%2,%3,%4").arg(ret.x()).arg(ret.y()).arg(ret.width()).arg(ret.height());
}

IMPLEMENT_HCONVERT_QVARIANT(QRectF)
{
     return qVariantFromValue(convert_QRectF(val,hr));
}

IMPLEMENT_HCONVERT(QRectF)
{
    QRectF ret;
    QStringList s = val.split(",");
    if (s.size() >= 4) {
        *hr = 0;
        ret.setX(s.at(0).toFloat());
        ret.setY(s.at(1).toFloat());
        ret.setWidth(s.at(2).toFloat());
        ret.setHeight(s.at(3).toFloat());
    }
    return ret;
}

IMPLEMENT_HCONVERT_QSTRING(QRect)
{
    *hr = 0;
    QRect ret = val.value<QRect>();
    return QString("%1,%2,%3,%4").arg(ret.x()).arg(ret.y()).arg(ret.width()).arg(ret.height());
}

IMPLEMENT_HCONVERT_QVARIANT(QRect)
{
    return qVariantFromValue(convert_QRect(val,hr));
}

IMPLEMENT_HCONVERT(QRect)
{
    return CALL_CONVERT(QRectF,val,hr).toRect();
}

// QSizeF
IMPLEMENT_HCONVERT_QSTRING(QSizeF)
{
    *hr = 0;
    QSizeF ret = val.value<QSizeF>();
    return QString("%1,%2").arg(ret.width()).arg(ret.height());
}

IMPLEMENT_HCONVERT_QVARIANT(QSizeF)
{
    return qVariantFromValue(convert_QSizeF(val,hr));
}

IMPLEMENT_HCONVERT(QSizeF)
{
    QSizeF ret;
    QStringList s = val.split(",");
    if (s.size() >= 2) {
        *hr = 0;
        ret.setWidth(s.at(0).toFloat());
        ret.setHeight(s.at(1).toFloat());
    }
    return ret;
}

IMPLEMENT_HCONVERT_QSTRING(QSize)
{
    *hr = 0;
    QSize ret = val.value<QSize>();
    return QString("%1,%2").arg(ret.width()).arg(ret.height());
}

IMPLEMENT_HCONVERT_QVARIANT(QSize)
{
    return qVariantFromValue(convert_QSize(val,hr));
}

IMPLEMENT_HCONVERT(QSize)
{
    return CALL_CONVERT(QSizeF,val,hr).toSize();
}

// QPointF
IMPLEMENT_HCONVERT_QSTRING(QPointF)
{
    *hr = 0;
    QPointF ret = val.value<QPointF>();
    return QString("%1,%2").arg(ret.x()).arg(ret.y());
}

IMPLEMENT_HCONVERT_QVARIANT(QPointF)
{
    return qVariantFromValue(convert_QPointF(val,hr));
}

IMPLEMENT_HCONVERT(QPointF)
{
    QStringList s = val.split(",");
    QPointF ret;
    if (s.size() >= 2)  {
        *hr = 0;
        ret.setX(s.at(0).toFloat());
        ret.setY(s.at(1).toFloat());
    }
    return ret;
}

IMPLEMENT_HCONVERT_QSTRING(QPoint)
{
    *hr = 0;
    QPoint ret = val.value<QPoint>();
    return QString("%1,%2").arg(ret.x()).arg(ret.y());
}

IMPLEMENT_HCONVERT_QVARIANT(QPoint)
{
    return qVariantFromValue(convert_QPoint(val,hr));
}

IMPLEMENT_HCONVERT(QPoint)
{
    return CALL_CONVERT(QPointF,val,hr).toPoint();
}

//HAnchor
IMPLEMENT_HCONVERT_QSTRING(HAnchor)
{
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QString();
}

IMPLEMENT_HCONVERT_QVARIANT(HAnchor)
{
    return qVariantFromValue(convert_HAnchor(val,hr));
}

IMPLEMENT_HCONVERT(HAnchor)
{
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return HAnchor();
}

//QBrush
IMPLEMENT_HCONVERT_QSTRING(QBrush)
{
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QString();
}

IMPLEMENT_HCONVERT_QVARIANT(QBrush)
{
    return qVariantFromValue(convert_QBrush(val,hr));
}

IMPLEMENT_HCONVERT(QBrush)
{
    QStringList s = val.split("|");
    if (s.size() >= 2) {
        QString type = s.at(0);
        if (type.startsWith("color")) {
            return QBrush(CALL_CONVERT(QColor,s.at(1),hr));
        }
        else if(type.startsWith("image")) {
            *hr = 0;
            return QBrush(HRESMGR->loadPixmap(s.at(1)));
        }
    }
    return QBrush();
}

//QFont
IMPLEMENT_HCONVERT_QSTRING(QFont)
{
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QString();
}

IMPLEMENT_HCONVERT_QVARIANT(QFont)
{
    return qVariantFromValue(convert_QFont(val,hr));
}

IMPLEMENT_HCONVERT(QFont)
{
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QFont();
}

IMPLEMENT_HCONVERT_QSTRING(QIcon)
{
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QString();
}

IMPLEMENT_HCONVERT_QVARIANT(QIcon)
{
    return qVariantFromValue(convert_QIcon(val,hr));
}

IMPLEMENT_HCONVERT(QIcon)
{
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QIcon();
}

IMPLEMENT_HCONVERT_QSTRING(qreal)
{
    *hr = 0;
    return QString("%1").arg(val.toFloat());
}

IMPLEMENT_HCONVERT_QVARIANT(qreal)
{
    return qVariantFromValue(convert_qreal(val,hr));
}

IMPLEMENT_HCONVERT(qreal)
{
    *hr = 0;
    return val.toFloat();
}

IMPLEMENT_HCONVERT_QSTRING(int)
{
    *hr = 0;
    return QString("%1").arg(val.toInt());
}

IMPLEMENT_HCONVERT_QVARIANT(int)
{
    return convert_int(val,hr);
}

IMPLEMENT_HCONVERT(int)
{
    *hr = 0;
    return val.toInt();
}


IMPLEMENT_HCONVERT_QSTRING(int64)
{
    *hr = 0;
    return QString("%1").arg(val.toLongLong());
}

IMPLEMENT_HCONVERT_QVARIANT(int64)
{
    return convert_int64(val,hr);
}

IMPLEMENT_HCONVERT(int64)
{
    *hr = 0;
    return val.toLongLong();
}

IMPLEMENT_HCONVERT_QSTRING(bool)
{
    *hr = 0;
    return val.toBool()?QString("true"):QString("false");
}

IMPLEMENT_HCONVERT_QVARIANT(bool)
{
    return QVariant(convert_bool(val,hr));
}

IMPLEMENT_HCONVERT(bool)
{
    *hr = 0;
    return val==QLatin1String("true");
}
