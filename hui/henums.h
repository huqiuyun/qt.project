#ifndef HENUMS_H
#define HENUMS_H

#include "hconfig.h"

class H_API HEnums
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

};

#endif // HENUMS_H
