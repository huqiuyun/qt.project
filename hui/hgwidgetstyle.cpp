#include "hgwidgetstyle.h"
#include "hglobal.h"
#include <QGraphicsWidget>

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
    //qDebug("HGWidgetStyle styleid=%s",objinfo.mStyleId.data());
    mObjType = USEOBJTYPE(HGWidgetStyle);
}

void HGWidgetStyle::setWidget(QGraphicsWidget* widget)
{
    mWidget = widget;

    widget->setWindowFrameMargins(mFrameMargins.left(),mFrameMargins.top(),mFrameMargins.right(),mFrameMargins.bottom());
    widget->setContentsMargins(mContentsMargins.left(),mContentsMargins.top(),mContentsMargins.right(),mContentsMargins.bottom());
}

QMargins HGWidgetStyle::windowFrameMargins() const
{
    return mFrameMargins;
}

void HGWidgetStyle::setWindowFrameMargins(const QMargins& m)
{
    //qDebug("HGWidgetStyle::setWindowFrameMargins(%d,%d,%d,%d)",m.left(),m.top(),m.right(),m.bottom());
    mFrameMargins = m;
}

QMargins HGWidgetStyle::contentsMargins() const
{
    return mContentsMargins;
}

void HGWidgetStyle::setContentsMargins(const QMargins& m)
{
    mContentsMargins = m;
}

void HGWidgetStyle::init()
{
    onSetWindowAttribute();
}

void HGWidgetStyle::onSetWindowAttribute()
{
    HGlobal::setGWidgetAttribute(mWidget,mWinAttribute);
}


void HGWidgetStyle::copyTo(HBaseStyle* obj)
{
    HGWidgetStyle* style = static_cast<HGWidgetStyle*>(obj);
    if (!style) return ;

    style->setContentsMargins(mContentsMargins);
    style->setWindowFrameMargins(mFrameMargins);

    HBaseStyle::copyTo(obj);
}

HBaseStyle* HGWidgetStyle::clone()
{
    HGWidgetStyle* style = new HGWidgetStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}
