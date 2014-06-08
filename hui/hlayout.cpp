#include "hlayout.h"
#include <QGraphicsView>

//HLayout
HLayout::HLayout(QObject* parent) :
    QObject(parent)
{
    mLayoutType = HEnums::kNone;
    mSpacing = 0;
    mAlignment = 0;
}

// next layout functions
HEnums::HLayoutType HLayout::layoutType() const
{
    return mLayoutType;
}

void HLayout::setLayoutType(HEnums::HLayoutType type)
{
    mLayoutType = type;
}

/** set margins for all child item in layout */
void HLayout::setMargins(const QMargins& m)
{
    mMargins = m;
}

QMargins HLayout::margins() const
{
   return mMargins;
}

/** set alignment in parent layout*/
Qt::Alignment HLayout::alignment() const
{
    return mAlignment;
}

void HLayout::setAlignment(Qt::Alignment align)
{
    mAlignment = align;
}

/** set per child item space in owner layout */
void HLayout::setSpacing(int s)
{
    mSpacing = s;
}

int HLayout::spacing() const
{
    return mSpacing;
}
