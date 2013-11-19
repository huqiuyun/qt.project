#include "hgwidgetstyle.h"
#include "hgwidget.h"

//HGWidgetStyle
IMPLEMENT_OBJECT_STATIC_CREATE(HGWidgetStyle)

HGWidgetStyle::HGWidgetStyle(QObject* parent) :
    HBaseStyle(parent)
{
}

HGWidgetStyle::HGWidgetStyle(const HObjectInfo& objinfo,QObject* parent) :
    HBaseStyle(objinfo,parent)
{
}

void HGWidgetStyle::setWidget(HGWidget* widget)
{
    mWidget = widget;
    //todo
}

bool HGWidgetStyle::hasStyleSheet() const
{
    return (mStyleSheet.size() > 1);
}

void HGWidgetStyle::setStyleSheet(const QString& sheet)
{
    mStyleSheet = sheet;
}

QString HGWidgetStyle::styleSheet() const
{
    return mStyleSheet;
}

bool HGWidgetStyle::hasBackgroundStyle() const
{
    return (mBackgroundStyle.mClsName.size() > 1 && mBackgroundStyle.mStyleId.size()>1);
}
void HGWidgetStyle::setBackgroundStyle(const HClassInfo& cls)
{
    mBackgroundStyle = cls;
}

HClassInfo HGWidgetStyle::backgroundStyle() const
{
    return mBackgroundStyle;
}

bool HGWidgetStyle::hasLayoutStyle() const
{
    return (mLayoutStyle.mClsName.size() > 1 && mLayoutStyle.mStyleId.size()>1);
}
void HGWidgetStyle::setLayoutStyle(const HClassInfo& cls)
{
    mLayoutStyle = cls;
}

HClassInfo HGWidgetStyle::layoutStyle() const
{
    return mLayoutStyle;
}

void HGWidgetStyle::copyTo(HBaseStyle* obj)
{
    HGWidgetStyle* style = static_cast<HGWidgetStyle*>(obj);
    if (!style) return ;

    style->setStyleSheet(styleSheet());
    HBaseStyle::copyTo(obj);
}

HBaseStyle* HGWidgetStyle::clone()
{
    HGWidgetStyle* style = new HGWidgetStyle(mObjinfo,parent());
    copyTo(style);

    return style;
}
