#ifndef HQCREATOR_H
#define HQCREATOR_H

#include "hbase.h"
#include "hfactory_i.h"
#include "hcssstyle.h"
#include "hframestyle.h"
#include "hgview.h"
#include "hgwidget.h"
#include "hbackgrounditem.h"
#include "hgstackedwidget.h"

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
#include <QLabel>
#include <QLineEdit>
#include <QTabBar>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTableView>
#include <QSplitter>
#include <QSlider>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>

const HRegisterObject s_objs[] =
{
    // css object
    {"HCssWidget"           , (HCreateObjectInstanceCB)&HCssWidget::create},
    {"HCssBackground"       , (HCreateObjectInstanceCB)&HCssBackground::create},
    {"HCssFrame"            , (HCreateObjectInstanceCB)&HCssFrame::create},
    {"HCssObject"           , (HCreateObjectInstanceCB)&HCssObject::create},

    //
    {"HBackgroundItem"      , (HCreateObjectInstanceCB)&HBackgroundItem::create},
    {"HFrameStyle"          , (HCreateObjectInstanceCB)&HFrameStyle::create},
    {NULL,NULL}
};

class HQCreator
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

    //graphicsitem
    DECLARE_GITEM_STATIC_CREATE(QGraphicsEllipseItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsLineItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsPathItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsPixmapItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsPolygonItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsRectItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsSimpleTextItem);
    DECLARE_GITEM_STATIC_CREATE(QGraphicsTextItem);
};

#define REG_GITEM_EX(CLSSTR,CLSNAME)   \
    REG_GITEM(CLSSTR,CLSNAME,HQCreator)

// QGraphicsItem
const HRegisterGItem s_gitems[] =
{
    // css object
    REG_GITEM("HGWidget"                  , HGWidget, HGWidget),
    REG_GITEM("HGStackedWidget"           , HGStackedWidget, HGStackedWidget),
    //
    REG_GITEM_EX("QGraphicsEllipseItem"   , QGraphicsEllipseItem),
    REG_GITEM_EX("QGraphicsLineItem"      , QGraphicsLineItem),
    REG_GITEM_EX("QGraphicsPathItem"      , QGraphicsPathItem),
    REG_GITEM_EX("QGraphicsPixmapItem"    , QGraphicsPixmapItem),
    REG_GITEM_EX("QGraphicsPolygonItem"   , QGraphicsPolygonItem),
    REG_GITEM_EX("QGraphicsRectItem"      , QGraphicsRectItem),
    REG_GITEM_EX("QGraphicsSimpleTextItem", QGraphicsSimpleTextItem),
    REG_GITEM_EX("QGraphicsTextItem"      , QGraphicsTextItem),
    {NULL,NULL}
};

#define REG_QWIDGET_EX(CLSSTR,CLSNAME)       \
    REG_QWIDGET(CLSSTR,CLSNAME,HQCreator)

const HRegisterQWidget s_qwidgets[] =
{
    // css object
    REG_QWIDGET("HGView"             , HGView, HGView),
    REG_QWIDGET_EX("QWidget"         , QWidget),
    REG_QWIDGET_EX("QPushButton"     , QPushButton),
    REG_QWIDGET_EX("QCheckBox"       , QCheckBox),
    REG_QWIDGET_EX("QRadioButton"    , QRadioButton),
    REG_QWIDGET_EX("QComboBox"       , QComboBox),
    REG_QWIDGET_EX("QTreeWidget"     , QTreeWidget),
    REG_QWIDGET_EX("QTreeView"       , QTreeView),
    REG_QWIDGET_EX("QListWidget"     , QListWidget),
    REG_QWIDGET_EX("QListView"       , QListView),
    REG_QWIDGET_EX("QTextBrowser"    , QTextBrowser),
    REG_QWIDGET_EX("QLabel"          , QLabel),
    REG_QWIDGET_EX("QLineEdit"       , QLineEdit),
    REG_QWIDGET_EX("QTabBar"         , QTabBar),
    REG_QWIDGET_EX("QStackedWidget"  , QStackedWidget),
    REG_QWIDGET_EX("QTableWidget"    , QTableWidget),
    REG_QWIDGET_EX("QTableView"      , QTableView),
    REG_QWIDGET_EX("QSplitter"       , QSplitter),
    REG_QWIDGET_EX("QSlider"         , QSlider),
    {NULL,NULL}
};

#endif // HQCREATOR_H
