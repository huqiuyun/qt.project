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

const HRegisterGWidget s_gwidgets[] =
{
    // css object
    {"HGWidget"             , (HCreateGWidgetInstanceCB)&HGWidget::create},
    {"HGStackedWidget"      , (HCreateGWidgetInstanceCB)&HGStackedWidget::create},
    {NULL,NULL}
};

class HQCreator
{
public:
    HQCreator();

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
    REG_QWIDGET_EX("QTableWidget"    , QTableWidget),
    REG_QWIDGET_EX("QTableView"      , QTableView),
    REG_QWIDGET_EX("QStackedWidget"  , QStackedWidget),
    {NULL,NULL}
};

#endif // HQCREATOR_H
