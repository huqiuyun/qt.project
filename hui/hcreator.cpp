#include "hcreator.h"

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QWidget>(objinfo,new QWidget(parent,(Qt::WindowFlags)param.mVar0.toUInt()));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QPushButton,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QPushButton>(objinfo,new QPushButton(param.mVar0.toString(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QCheckBox,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QCheckBox>(objinfo,new QCheckBox(param.mVar0.toString(),parent));
}


IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QRadioButton,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QRadioButton>(objinfo,new QRadioButton(param.mVar0.toString(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QComboBox,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QComboBox>(objinfo,new QComboBox(parent));
}

//
IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTreeWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTreeWidget>(objinfo,new QTreeWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTreeView,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTreeView>(objinfo,new QTreeView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QListWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QListWidget>(objinfo,new QListWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QListView,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QListView>(objinfo,new QListView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTextBrowser,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTextBrowser>(objinfo,new QTextBrowser(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QLabel,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QLabel>(objinfo,new QLabel(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QLineEdit,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QLineEdit>(objinfo,new QLineEdit(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTabBar,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTabBar>(objinfo,new QTabBar(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QStackedWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QStackedWidget>(objinfo,new QStackedWidget(parent));
}


IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTableWidget,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTableWidget>(objinfo,new QTableWidget(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QTableView,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QTableView>(objinfo,new QTableView(parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QSplitter,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QSplitter>(objinfo,new QSplitter((Qt::Orientation)param.mVar0.toUInt(),parent));
}

IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(QSlider,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return hSetObjectT<QSlider>(objinfo,new QSlider((Qt::Orientation)param.mVar0.toUInt(),parent));
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsEllipseItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsEllipseItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsLineItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsLineItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsPathItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsPathItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsPixmapItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsPixmapItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsPolygonItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsPolygonItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsRectItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsRectItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsSimpleTextItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsSimpleTextItem(parent);
}

IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(QGraphicsTextItem,HQCreator)
{
    Q_UNUSED(objinfo);
    Q_UNUSED(parent);
    Q_UNUSED(param);
    Q_UNUSED(hr);
    return new QGraphicsTextItem(parent);
}

/// convert function

IMPLEMENT_HCONVERT_QSTRING(QString)
{
    *hr = 0;
    return val.value<QString>();
}

IMPLEMENT_HCONVERT_QVARIANT(QString)
{
    *hr = 0;
    return QVariant(val);
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
    QStringList s = val.split(",");
    if (s.size() >= 4)
    {
        *hr = 0;
        QMargins ret(s.at(0).toFloat(), s.at(1).toFloat(), s.at(2).toFloat(), s.at(3).toFloat());
        return qVariantFromValue(ret);
    }
    else
    {
        return qVariantFromValue(QMargins());
    }
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
    QColor ret;
    QStringList s = val.split(",");
    if (s.size() >= 3)
    {
        *hr = 0;
        int red = s[0].toInt();
        int green = s[1].toInt();
        int blue = s[2].toInt();
        int alpha = 255;
        if (s.size() >= 4)
        {
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
    QRectF ret;
    QStringList s = val.split(",");
    if (s.size() >= 4)
    {
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
    return convertQVariant_QRectF(val,hr).toRect();
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
    QSizeF ret;
    QStringList s = val.split(",");
    if (s.size() >= 2)
    {
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
    return convertQVariant_QSizeF(val,hr).toSize();
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
    QStringList s = val.split(",");
    QPointF ret;
    if (s.size() >= 2)
    {
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
    return convertQVariant_QPointF(val,hr).toPoint();
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
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QVariant();
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
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QVariant();
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
    Q_UNUSED(val);
    Q_UNUSED(hr);
    return QVariant();
}

