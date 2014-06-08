#include "hframestyle.h"
#include "hglobal.h"

IMPLEMENT_OBJECT_STATIC_CREATE(HFrameStyle)
HFrameStyle::HFrameStyle(QObject *parent) :
    HWidgetStyle(parent),
    mWindow(NULL),
    mHandler(NULL)
{
    mObjType = USEOBJTYPE(HFrameStyle);
}

HFrameStyle::HFrameStyle(const HObjectInfo& objinfo, QObject *parent) :
    HWidgetStyle(objinfo,parent),
    mWindow(NULL),
    mHandler(NULL)
{
    //qDebug("HFrameStyle styleid=%s",objinfo.mStyleId.data());
    mObjType = USEOBJTYPE(HFrameStyle);
}

HFrameStyle::~HFrameStyle()
{
}

void HFrameStyle::setWindow(QWidget* window)
{
    mWindow = window;
}

QWidget* HFrameStyle::window() const
{
    return mWindow;
}

void HFrameStyle::setFrameStyleHandler(IHFrameStyleHandler* handler)
{
    mHandler = handler;
}

void HFrameStyle::onSetWindowAttribute()
{
    HGlobal::setQWidgetAttribute(mWindow,mWinAttribute);
}

void HFrameStyle::copyTo(HBaseStyle* obj)
{
    HFrameStyle* style = static_cast<HFrameStyle*>(obj);
    if (!style) return ;

    HWidgetStyle::copyTo(obj);
}

HBaseStyle* HFrameStyle::clone()
{
    HFrameStyle* style = new HFrameStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}

void  HFrameStyle::init()
{
    onSetWindowAttribute();
}

void HFrameStyle::resizeEvent(QResizeEvent *event)
{
    if (mHandler)
        mHandler->resizeEvent(this,event);
}

bool  HFrameStyle::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    //Windows	eventType = "windows_generic_MSG"	message = MSG *	 result = LRESULT
    if (mHandler)
        return mHandler->nativeEvent(this,eventType,message,result);
    return false;
}
