#ifndef HCONFIG_H
#define HCONFIG_H

#include "hctypes.h"
#include "herror.h"

#if defined(WIN32)

#ifdef QT_DLL
    #include <QtGlobal>
    #define H_DECL_EXPORT Q_DECL_EXPORT
    #define H_DECL_IMPORT Q_DECL_IMPORT
#else
    #define H_DECL_EXPORT __declspec(dllexport)
    #define H_DECL_IMPORT __declspec(dllimport)
#endif

#else // other platform
    #define H_DECL_EXPORT
    #define H_DECL_IMPORT
#endif

#  ifdef BUILD_HFW
#    define H_API H_DECL_EXPORT
#  else
#    define H_API H_DECL_IMPORT
#  endif // BUILD_H_DUIFW

#define hDelete(h)  if (h) { delete (h); (h)= NULL;}
#define hDelete2(h) if (h) { delete[] (h); (h)= NULL;}
#define hfree(v)    if (v) { ::free((void*)v); v = NULL; }

#define H_D(cls) cls##Private* d = d_ptr

namespace qy {
enum HColorizeFlag
{
    kFollowParent = 0,
    kUnColorableFlag,
    kColorableFlag
};

enum HDragFlag
{
    kDragWindow = 1,
    kNotDragWindow = 2,
    kDragWithParentFlag = 3
};

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
    kCssEnd,
};

} // namespace qy

#endif // HCONFIG_H
