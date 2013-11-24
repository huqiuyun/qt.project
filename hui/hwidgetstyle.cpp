#include "hwidgetstyle.h"

//HWidgetStyle
IMPLEMENT_OBJECT_STATIC_CREATE(HWidgetStyle)

HWidgetStyle::HWidgetStyle(QObject* parent) :
    HBaseStyle(parent)
{
    mObjType = USEOBJTYPE(HWidgetStyle);
}

HWidgetStyle::HWidgetStyle(const HObjectInfo& objinfo,QObject* parent) :
    HBaseStyle(objinfo,parent)
{
    mObjType = USEOBJTYPE(HWidgetStyle);
}

bool HWidgetStyle::hasBackgroundStyle() const
{
    return (mBackgroundStyle.mClsName.size() > 1 && mBackgroundStyle.mStyleId.size()>1);
}

void HWidgetStyle::setBackgroundStyle(const HClassInfo& cls)
{
    mBackgroundStyle = cls;
}

HClassInfo HWidgetStyle::backgroundStyle() const
{
    return mBackgroundStyle;
}

bool HWidgetStyle::hasLayoutStyle() const
{
    return (mLayoutStyle.mClsName.size() > 1 && mLayoutStyle.mStyleId.size()>1);
}

void HWidgetStyle::setLayoutStyle(const HClassInfo& cls)
{
    mLayoutStyle = cls;
}

HClassInfo HWidgetStyle::layoutStyle() const
{
    return mLayoutStyle;
}

void HWidgetStyle::copyTo(HBaseStyle* obj)
{
    HWidgetStyle* style = static_cast<HWidgetStyle*>(obj);
    if (!style) return ;

    style->setBackgroundStyle(mBackgroundStyle);
    style->setLayoutStyle(mLayoutStyle);
    HBaseStyle::copyTo(obj);
}

HBaseStyle* HWidgetStyle::clone()
{
    HWidgetStyle* style = new HWidgetStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}
