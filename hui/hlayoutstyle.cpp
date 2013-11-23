#include "hlayoutstyle.h"
#include <QGraphicsView>

//HLayoutStyle

HLayoutStyle::HLayoutStyle(QObject* parent) :
    HBaseStyle(parent)
{
    mLayoutType = HEnums::kNone;
    mSpacing = 0;
    mAlignment = Qt::AlignCenter;
    mObjType = USEOBJTYPE(HLayoutStyle);
}

HLayoutStyle::HLayoutStyle(const HObjectInfo& objinfo,QObject* parent) :
    HBaseStyle(objinfo,parent)
{
    mLayoutType = HEnums::kNone;
    mSpacing = 0;
    mAlignment = Qt::AlignCenter;
    mObjType = USEOBJTYPE(HLayoutStyle);
}

// next layout functions
HEnums::HLayoutType HLayoutStyle::layoutType() const
{
    return mLayoutType;
}

void HLayoutStyle::setLayoutType(HEnums::HLayoutType type)
{
    mLayoutType = type;
}

/** set margins for all child item in layout */
void HLayoutStyle::setMargins(const QMargins& m)
{
    mMargins = m;
}

QMargins HLayoutStyle::margins() const
{
   return mMargins;
}

/** set alignment in parent layout*/
Qt::Alignment HLayoutStyle::alignment() const
{
    return mAlignment;
}

void HLayoutStyle::setAlignment(Qt::Alignment align)
{
    mAlignment = align;
}

HAnchor HLayoutStyle::anchor() const
{
    return mAnchor;
}

void HLayoutStyle::setAnchor(const HAnchor& a)
{
    mAnchor = a;
}

/** set per child item space in owner layout */
void HLayoutStyle::setSpacing(int s)
{
    mSpacing = s;
}

int HLayoutStyle::spacing() const
{
    return mSpacing;
}

void HLayoutStyle::copyTo(HBaseStyle* obj)
{
    HLayoutStyle* style = static_cast<HLayoutStyle*>(obj);
    if (!style) return ;

    style->setLayoutType(layoutType());
    style->setMargins(margins());
    style->setAlignment(alignment());
    style->setAnchor(anchor());
    style->setSpacing(spacing());
    HBaseStyle::copyTo(obj);
}

void HLayoutStyle::doConstruct()
{

}

