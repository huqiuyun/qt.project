#include "hgwidgetstyle.h"
#include "hgwidget.h"

//HGWidgetStyle
IMPLEMENT_OBJECT_STATIC_CREATE(HGWidgetStyle)

HGWidgetStyle::HGWidgetStyle(QObject* parent) :
    HWidgetStyle(parent),
    mWidget(NULL)
{
    mObjType = USEOBJTYPE(HGWidgetStyle);
}

HGWidgetStyle::HGWidgetStyle(const HObjectInfo& objinfo,QObject* parent) :
    HWidgetStyle(objinfo,parent),
    mWidget(NULL)
{
    mObjType = USEOBJTYPE(HGWidgetStyle);
}

void HGWidgetStyle::setWidget(HGWidget* widget)
{
    mWidget = widget;
    //todo
}

HBaseStyle* HGWidgetStyle::clone()
{
    HGWidgetStyle* style = new HGWidgetStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}
