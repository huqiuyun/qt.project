#ifndef HuiCreator_H
#define HuiCreator_H

#include "hbase.h"
#include "hfactory_i.h"
#include "hstyle.h"
#include "hgview.h"
#include "hgwidget.h"

#include "hgscenestyle.h"
#include "hqlayoutstyle.h"
#include "hgwidgetstyle.h"
#include "hglayoutstyle.h"
#include "hframestyle.h"
#include "hbackgroundstyle.h"
#include "hfontstyle.h"
#include "hgstackedwidget.h"
#include "hqwidget.h"
#include "hgproxywidget.h"
#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QTreeWidget>
#include <QTreeView>
#include <QListWidget>
#include <QListView>
#include <QTextBrowser>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QTabBar>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTableView>
#include <QSplitter>
#include <QSlider>
#include <QDialog>
#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QMargins>
#include <QDockWidget>

Q_DECLARE_METATYPE(QMargins)

#define REG_OBJECT_EX(CLSNAME)   \
    REG_OBJECT(CLSNAME,CLSNAME)

const HRegisterObject s_objs[] =
{
    // style object
    REG_OBJECT_EX(HBackgroundStyle),
    REG_OBJECT_EX(HFrameStyle),
    REG_OBJECT_EX(HGSceneStyle),
    REG_OBJECT_EX(HGWidgetStyle),
    REG_OBJECT_EX(HGLayoutStyle),
    REG_OBJECT_EX(HQLayoutStyle),
    REG_OBJECT_EX(HFontStyle),
    {NULL,NULL}
};

#define DECLARE_HCONVERT_QSTRING(TYPE)  \
    DECLARE_STATIC_CONVERT_FUNC(QString,QVariant,QString_##TYPE)

#define IMPLEMENT_HCONVERT_QSTRING(TYPE) \
    IMPLEMENT_STATIC_CONVERT_FUNC(HuiCreator,QString,QVariant,QString_##TYPE)

#define DECLARE_HCONVERT_QVARIANT(TYPE)  \
    DECLARE_STATIC_CONVERT_FUNC(QVariant,QString,QVariant_##TYPE)

#define IMPLEMENT_HCONVERT_QVARIANT(TYPE) \
    IMPLEMENT_STATIC_CONVERT_FUNC(HuiCreator,QVariant,QString,QVariant_##TYPE)

class HuiCreator
{
public:
    DECLARE_QWIDGET_STATIC_CREATE(QWidget);
    DECLARE_QWIDGET_STATIC_CREATE(QPushButton);
    DECLARE_QWIDGET_STATIC_CREATE(QCheckBox);
    DECLARE_QWIDGET_STATIC_CREATE(QRadioButton);
    DECLARE_QWIDGET_STATIC_CREATE(QComboBox);

    DECLARE_QWIDGET_STATIC_CREATE(QTreeWidget);
    DECLARE_QWIDGET_STATIC_CREATE(QTreeView);
    DECLARE_QWIDGET_STATIC_CREATE(QListWidget);
    DECLARE_QWIDGET_STATIC_CREATE(QListView);
    DECLARE_QWIDGET_STATIC_CREATE(QTextBrowser);
    DECLARE_QWIDGET_STATIC_CREATE(QLabel);
    DECLARE_QWIDGET_STATIC_CREATE(QLineEdit);
    DECLARE_QWIDGET_STATIC_CREATE(QTabBar);
    DECLARE_QWIDGET_STATIC_CREATE(QStackedWidget);
    DECLARE_QWIDGET_STATIC_CREATE(QTableWidget);
    DECLARE_QWIDGET_STATIC_CREATE(QTableView);
    DECLARE_QWIDGET_STATIC_CREATE(QSplitter);
    DECLARE_QWIDGET_STATIC_CREATE(QSlider);
    DECLARE_QWIDGET_STATIC_CREATE(QDialog);
    DECLARE_QWIDGET_STATIC_CREATE(QTextEdit);
    DECLARE_QWIDGET_STATIC_CREATE(QDockWidget);
    //graphicsitem
    DECLARE_GITEM_STATIC_CREATE(QGraphicsEllipseItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsLineItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsPathItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsPixmapItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsPolygonItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsRectItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsSimpleTextItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsTextItem);

    //convert function
    DECLARE_HCONVERT_QSTRING(QString);
    DECLARE_HCONVERT_QVARIANT(QString);

    DECLARE_HCONVERT_QSTRING(QMargins);
    DECLARE_HCONVERT_QVARIANT(QMargins);

    DECLARE_HCONVERT_QSTRING(QColor);
    DECLARE_HCONVERT_QVARIANT(QColor);

    DECLARE_HCONVERT_QSTRING(QRectF);
    DECLARE_HCONVERT_QVARIANT(QRectF);

    DECLARE_HCONVERT_QSTRING(QRect);
    DECLARE_HCONVERT_QVARIANT(QRect);

    DECLARE_HCONVERT_QSTRING(QSizeF);
    DECLARE_HCONVERT_QVARIANT(QSizeF);

    DECLARE_HCONVERT_QSTRING(QSize);
    DECLARE_HCONVERT_QVARIANT(QSize);

    DECLARE_HCONVERT_QSTRING(QPointF);
    DECLARE_HCONVERT_QVARIANT(QPointF);

    DECLARE_HCONVERT_QSTRING(QPoint);
    DECLARE_HCONVERT_QVARIANT(QPoint);

    DECLARE_HCONVERT_QSTRING(HAnchor);
    DECLARE_HCONVERT_QVARIANT(HAnchor);

    DECLARE_HCONVERT_QSTRING(QBrush);
    DECLARE_HCONVERT_QVARIANT(QBrush);

    DECLARE_HCONVERT_QSTRING(QFont);
    DECLARE_HCONVERT_QVARIANT(QFont);

    DECLARE_HCONVERT_QSTRING(QIcon);
    DECLARE_HCONVERT_QVARIANT(QIcon);

    DECLARE_HCONVERT_QSTRING(qreal);
    DECLARE_HCONVERT_QVARIANT(qreal);
};

#define REG_CONVERT_EX(TYPE)   \
    REG_CONVERT(qRegisterMetaType<TYPE>(#TYPE),TYPE,HuiCreator)

const HRegisterConvert s_converts[] =
{
    REG_CONVERT(0,QString,HuiCreator), // default handler
    REG_CONVERT_EX(QString),
    REG_CONVERT_EX(QMargins),
    REG_CONVERT_EX(QColor),
    REG_CONVERT_EX(QRectF),
    REG_CONVERT_EX(QRect),
    REG_CONVERT_EX(QSizeF),
    REG_CONVERT_EX(QSize),
    REG_CONVERT_EX(QPointF),
    REG_CONVERT_EX(QPoint),
    REG_CONVERT_EX(QBrush),
    REG_CONVERT_EX(QFont),
    REG_CONVERT_EX(QIcon),
    REG_CONVERT_EX(HAnchor),
    REG_CONVERT_EX(qreal),
    {-1,NULL,NULL}
};

#define REG_GITEM_EX(CLSNAME)   \
    REG_GITEM(CLSNAME,HuiCreator)

// QGraphicsItem
const HRegisterGItem s_gitems[] =
{
    REG_GITEM_EX(QGraphicsEllipseItem),
    REG_GITEM_EX(QGraphicsLineItem),
    REG_GITEM_EX(QGraphicsPathItem),
    REG_GITEM_EX(QGraphicsPixmapItem),
    REG_GITEM_EX(QGraphicsPolygonItem),
    REG_GITEM_EX(QGraphicsRectItem),
    REG_GITEM_EX(QGraphicsSimpleTextItem),
    REG_GITEM_EX(QGraphicsTextItem),
    {NULL,NULL}
};

const HRegisterGWidget s_gwidgets[] =
{
    REG_GWIDGET(HGWidget, HGWidget),
    REG_GWIDGET(HGStackedWidget, HGStackedWidget),
    REG_GWIDGET(HGProxyWidget, HGProxyWidget),
    {NULL,NULL}
};

#define REG_QWIDGET_EX(CLSNAME)       \
    REG_QWIDGET(CLSNAME,HuiCreator)

const HRegisterQWidget s_qwidgets[] =
{
    REG_QWIDGET(HGView, HGView),
    REG_QWIDGET(HQWidget, HQWidget),
    REG_QWIDGET_EX(QWidget),
    REG_QWIDGET_EX(QPushButton),
    REG_QWIDGET_EX(QCheckBox),
    REG_QWIDGET_EX(QRadioButton),
    REG_QWIDGET_EX(QComboBox),
    REG_QWIDGET_EX(QTreeWidget),
    REG_QWIDGET_EX(QTreeView),
    REG_QWIDGET_EX(QListWidget),
    REG_QWIDGET_EX(QListView),
    REG_QWIDGET_EX(QTextBrowser),
    REG_QWIDGET_EX(QTextEdit),
    REG_QWIDGET_EX(QLabel),
    REG_QWIDGET_EX(QLineEdit),
    REG_QWIDGET_EX(QTabBar),
    REG_QWIDGET_EX(QStackedWidget),
    REG_QWIDGET_EX(QTableWidget),
    REG_QWIDGET_EX(QTableView),
    REG_QWIDGET_EX(QSplitter),
    REG_QWIDGET_EX(QSlider),
    REG_QWIDGET_EX(QDialog),
    REG_QWIDGET_EX(QDockWidget),
    {NULL,NULL}
};

#endif // HuiCreator_H
