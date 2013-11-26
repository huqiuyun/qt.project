#ifndef HENUMS_H
#define HENUMS_H

#include "hconfig.h"

#define OBJTYPE(TYPE)    kHObjT_##TYPE
#define USEOBJTYPE(TYPE) HEnums::kHObjT_##TYPE

class HEnums
{
    Q_GADGET
    Q_ENUMS(HLayoutType)
public:

    enum HLayoutType
    {
        kNone = 0,
        kVBox = 1, //top to bottom, QGraphicsLinearLayout,QVBoxLayout
        kHBox = 2, //left to right, QGraphicsLinearLayout,QHBoxLayout
        kGrid = 3,
        kAnchor = 4,
        kStacked = 5, // for QWidget QStackedLayout
        kVBoxTopBottom = 6, // for QWidget, QBoxLayout,directon = top to bottom
        kVBoxBottomTop = 7, // for QWidget, QBoxLayout,directon = top to bottom
        kHBoxLeftRight = 8, // for QWidget, QBoxLayout,directon = top to bottom
        kHBoxRightLeft = 9, // for QWidget, QBoxLayout,directon = top to bottom
        kForm // for QWidget, QFormLayout
    };


    enum HObjectType
    {
        OBJTYPE(Unk) = 0,
        OBJTYPE(QObject),
        OBJTYPE(HStyle),
        OBJTYPE(HGSceneStyle),
        OBJTYPE(HBackgroundStyle),
        OBJTYPE(HFrameStyle),
        OBJTYPE(HWidgetStyle),
        OBJTYPE(HGWidgetStyle),
        OBJTYPE(HLayoutStyle),
        OBJTYPE(HGLayoutStyle),
        OBJTYPE(HQLayoutStyle),
        OBJTYPE(HFontStyle),
        OBJTYPE(HGScene),
        //
        OBJTYPE(QWidget) = 500,
        OBJTYPE(QPushButton) = 501,
        OBJTYPE(QCheckBox) = 502,
        OBJTYPE(QRadioButton) = 503,
        OBJTYPE(QComboBox) = 504,
        OBJTYPE(QTreeWidget) = 505,
        OBJTYPE(QTreeView) = 506,
        OBJTYPE(QListWidget) = 507,
        OBJTYPE(QListView) = 508,
        OBJTYPE(QTextBrowser) = 509,
        OBJTYPE(QLabel) = 510,
        OBJTYPE(QLineEdit) = 511,
        OBJTYPE(QTabBar) = 512,
        OBJTYPE(QStackedWidget) = 513,
        OBJTYPE(QTableWidget) = 514,
        OBJTYPE(QTableView) = 515,
        OBJTYPE(QSplitter) = 516,
        OBJTYPE(QSlider) = 517,
        OBJTYPE(QDialog),
        OBJTYPE(QTextEdit),

        OBJTYPE(HQWidget),
        OBJTYPE(HGView),
        OBJTYPE(QUseDefine) = 1500,

        //graphicsitem for scene
        OBJTYPE(QGraphicsItem) = 2500,
        OBJTYPE(QGraphicsEllipseItem),
        OBJTYPE(QGraphicsLineItem),
        OBJTYPE(QGraphicsPathItem),
        OBJTYPE(QGraphicsPixmapItem),
        OBJTYPE(QGraphicsPolygonItem),
        OBJTYPE(QGraphicsRectItem),
        OBJTYPE(QGraphicsSimpleTextItem),
        OBJTYPE(QGraphicsTextItem),

        // grahicslayoutitem for layout (QGraphicsWidget ,QGraphicsProxyWidget, HGWidget)
        OBJTYPE(QGLayoutItem) = 3500,
        OBJTYPE(QGraphicsWidget),
        OBJTYPE(QGraphicsProxyWidget),
        OBJTYPE(HGProxyWidget),
        OBJTYPE(HGWidget),
        OBJTYPE(HGStackedWidget),

        OBJTYPE(HGLayoutItemUseDefine) = 4500,

        kOTUsed = 6000
    };

    enum HCssKey
    {
        kCssUnk      = 0,
        kCssMargins  = 1 << 0,
        kCssColorizePolicy = 1 << 1,
        kCssData = 1 << 2,
        kCssComposeMode = 1 << 3, //0x10
        kCssImagePath = 1 << 4,
        kCssAlignment = 1 << 5,
        kCssColor = 1 << 6,
        kCssWidth = 1 << 7, // 0x100
        kCssHeight = 1 << 8,
        kCssFixWidth = 1 << 9,
        kCssFixHeight = 1 << 10,
        kCssLayout = 1 << 11, // 0x1000
        kCssSpacing = 1 << 12,
        kCssAnchor = 1 << 13,
        kCssSize = 1 << 14,
        kCssDragFlag = 1 << 15,
        kCssEnd
    };
}; //end class

#endif // HENUMS_H
