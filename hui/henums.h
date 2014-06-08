#ifndef HENUMS_H
#define HENUMS_H

#include "hconfig.h"

#define OBJTYPE(TYPE)    kHObjT_##TYPE
#define USEOBJTYPE(TYPE) HEnums::kHObjT_##TYPE

class HEnums
{
    Q_GADGET
    Q_ENUMS(HLayoutType)
    Q_ENUMS(HWidgetState)
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
        OBJTYPE(HLayoutConfig),
        OBJTYPE(QObject),
        OBJTYPE(HStyle),
        OBJTYPE(HImageStyle),
        OBJTYPE(HFrameStyle),
        OBJTYPE(HGWidgetStyle),
        OBJTYPE(HFontStyle),
        OBJTYPE(HColorStyle),
        OBJTYPE(HGroup),
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
        OBJTYPE(QDockWidget),

        OBJTYPE(HQWidget),
        OBJTYPE(HGView),
        OBJTYPE(HQUseDefine) = 1500,

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
        OBJTYPE(HGButton),
        OBJTYPE(HGLable),
        OBJTYPE(HGComboBox),
        OBJTYPE(HGTree),
        OBJTYPE(HGListBox),
        OBJTYPE(HGCaption),
        OBJTYPE(HGSplitter),
        OBJTYPE(HGScrollArea),
        OBJTYPE(HGScrollBar),
        OBJTYPE(HGAnimation),
        OBJTYPE(HGItemView),

        OBJTYPE(HGUseDefine) = 4500,

        kOTUsed = 6000
    };

    enum HChangeType
    {
        kChgUnk      = 0,
        kChgMargins  = 1 << 0,
        kChgColorizePolicy = 1 << 1,
        kChgData = 1 << 2,
        kChgComposeMode = 1 << 3, //0x10
        kChgImage = 1 << 4,
        kChgAlignment = 1 << 5,
        kChgColor = 1 << 6,
        kChgWidth = 1 << 7, // 0x100
        kChgHeight = 1 << 8,
        kChgFixWidth = 1 << 9,
        kChgFixHeight = 1 << 10,
        kChgLayout = 1 << 11, // 0x1000
        kChgSpacing = 1 << 12,
        kChgAnchor = 1 << 13,
        kChgSize = 1 << 14,
        kChgDragFlag = 1 << 15,
        kChgBrush = 1<< 16,
        kCssEnd
    };

    enum HWidgetState
    {
        kStateNormal        = 0x00000000,
        kStateOver          = 0x00000001,
        kStatePressed       = 0x00000002,
        kStateFoucs         = 0x00000004,
        kStateDisable       = 0x00000008,
        kStateChecked       = 0x00000010
    };
    static bool testState(int state,int flag)
    {
        return (state & flag) != 0;
    }
}; //end class

#endif // HENUMS_H
