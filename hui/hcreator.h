#ifndef HUICREATOR_H
#define HUICREATOR_H

#include "hbase.h"
#include "hfactory_i.h"
#include "hstyle.h"
#include "hgview.h"
#include "hgwidget.h"

#include "hgwidgetstyle.h"
#include "hframestyle.h"
#include "himagestyle.h"
#include "hfontstyle.h"
#include "hcolorstyle.h"

#include "hgstackedwidget.h"
#include "hqwidget.h"
#include "hgbutton.h"
#include "hgroup.h"
#include "hglable.h"
#include "hgcombobox.h"
#include "hgtree.h"
#include "hgsplitter.h"
#include "hglistbox.h"
#include "hganimation.h"
#include "hgcaption.h"
#include "hgscrollarea.h"

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
    REG_OBJECT_EX(HImageStyle),
    REG_OBJECT_EX(HFrameStyle),
    REG_OBJECT_EX(HGWidgetStyle),
    REG_OBJECT_EX(HFontStyle),
    REG_OBJECT_EX(HColorStyle),
    REG_OBJECT_EX(HGroup),
    {NULL,NULL}
};

#define DECLARE_HCONVERT_QSTRING(TYPE)  \
    DECLARE_STATIC_CONVERT_FUNC(QString,QVariant,QString_##TYPE)

#define IMPLEMENT_HCONVERT_QSTRING(TYPE) \
    IMPLEMENT_STATIC_CONVERT_FUNC(HuiCreator,QString,QVariant,QString_##TYPE)

#define DECLARE_HCONVERT(TYPE)  \
    DECLARE_STATIC_CONVERT_FUNC(TYPE,QString,_##TYPE)

#define DECLARE_HCONVERT_QVARIANT(TYPE)  \
    DECLARE_STATIC_CONVERT_FUNC(QVariant,QString,QVariant_##TYPE)

#define IMPLEMENT_HCONVERT_QVARIANT(TYPE) \
    IMPLEMENT_STATIC_CONVERT_FUNC(HuiCreator,QVariant,QString,QVariant_##TYPE)

#define IMPLEMENT_HCONVERT(TYPE) \
    IMPLEMENT_STATIC_CONVERT_FUNC(HuiCreator,TYPE,QString,_##TYPE)


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
    DECLARE_HCONVERT(QString);

    DECLARE_HCONVERT_QSTRING(QMargins);
    DECLARE_HCONVERT_QVARIANT(QMargins);
    DECLARE_HCONVERT(QMargins);

    DECLARE_HCONVERT_QSTRING(QColor);
    DECLARE_HCONVERT_QVARIANT(QColor);
    DECLARE_HCONVERT(QColor);

    DECLARE_HCONVERT_QSTRING(QRectF);
    DECLARE_HCONVERT_QVARIANT(QRectF);
    DECLARE_HCONVERT(QRectF);

    DECLARE_HCONVERT_QSTRING(QRect);
    DECLARE_HCONVERT_QVARIANT(QRect);
    DECLARE_HCONVERT(QRect);

    DECLARE_HCONVERT_QSTRING(QSizeF);
    DECLARE_HCONVERT_QVARIANT(QSizeF);
    DECLARE_HCONVERT(QSizeF);

    DECLARE_HCONVERT_QSTRING(QSize);
    DECLARE_HCONVERT_QVARIANT(QSize);
    DECLARE_HCONVERT(QSize);

    DECLARE_HCONVERT_QSTRING(QPointF);
    DECLARE_HCONVERT_QVARIANT(QPointF);
    DECLARE_HCONVERT(QPointF);

    DECLARE_HCONVERT_QSTRING(QPoint);
    DECLARE_HCONVERT_QVARIANT(QPoint);
    DECLARE_HCONVERT(QPoint);

    DECLARE_HCONVERT_QSTRING(HAnchor);
    DECLARE_HCONVERT_QVARIANT(HAnchor);
    DECLARE_HCONVERT(HAnchor);

    DECLARE_HCONVERT_QSTRING(QBrush);
    DECLARE_HCONVERT_QVARIANT(QBrush);
    DECLARE_HCONVERT(QBrush);

    DECLARE_HCONVERT_QSTRING(QFont);
    DECLARE_HCONVERT_QVARIANT(QFont);
    DECLARE_HCONVERT(QFont);

    DECLARE_HCONVERT_QSTRING(QIcon);
    DECLARE_HCONVERT_QVARIANT(QIcon);
    DECLARE_HCONVERT(QIcon);

    DECLARE_HCONVERT_QSTRING(bool);
    DECLARE_HCONVERT_QVARIANT(bool);
    DECLARE_HCONVERT(bool);

    DECLARE_HCONVERT_QSTRING(int);
    DECLARE_HCONVERT_QVARIANT(int);
    DECLARE_HCONVERT(int);

    DECLARE_HCONVERT_QSTRING(int64);
    DECLARE_HCONVERT_QVARIANT(int64);
    DECLARE_HCONVERT(int64);

    DECLARE_HCONVERT_QSTRING(qreal);
    DECLARE_HCONVERT_QVARIANT(qreal);
    DECLARE_HCONVERT(qreal);
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
    REG_CONVERT_EX(bool),
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
    REG_GWIDGET(HGButton, HGButton),
    REG_GWIDGET(HGLable, HGLable),
    REG_GWIDGET(HGComboBox, HGComboBox),
    REG_GWIDGET(HGTree, HGTree),
    REG_GWIDGET(HGSplitter, HGSplitter),
    REG_GWIDGET(HGAnimation, HGAnimation),
    REG_GWIDGET(HGListBox, HGListBox),
    REG_GWIDGET(HGCaption,HGCaption),
    REG_GWIDGET(HGScrollArea,HGScrollArea),
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

#endif // HUICREATOR_H
