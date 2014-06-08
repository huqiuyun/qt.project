#include "hwidgetstyle.h"

//HWidgetStyle
HWidgetStyle::HWidgetStyle(QObject* parent) :
    HBaseStyle(parent)
{
}

HWidgetStyle::HWidgetStyle(const HObjectInfo& objinfo,QObject* parent) :
    HBaseStyle(objinfo,parent)
{
}

QString HWidgetStyle::windowAttribute() const
{
    return mWinAttribute;
}

void HWidgetStyle::setWindowAttribute(const QString& a)
{
    mWinAttribute = a;
    onSetWindowAttribute();
}

void HWidgetStyle::copyTo(HBaseStyle* obj)
{
    HWidgetStyle* style = static_cast<HWidgetStyle*>(obj);
    if (!style) return ;

    style->setWindowAttribute(mWinAttribute);
    HBaseStyle::copyTo(obj);
}

HBaseStyle* HWidgetStyle::clone()
{
    HWidgetStyle* style = new HWidgetStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}
