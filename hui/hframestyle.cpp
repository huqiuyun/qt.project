#include "hframestyle.h"
#include <QWidget>

IMPLEMENT_OBJECT_STATIC_CREATE(HFrameStyle)
HFrameStyle::HFrameStyle(QObject *parent) :
    HWidgetStyle(parent),
    mWindow(NULL)
{
    mWinFlags = Qt::Window;
    mObjType = USEOBJTYPE(HFrameStyle);
}

HFrameStyle::HFrameStyle(const HObjectInfo& objinfo, QObject *parent) :
    HWidgetStyle(objinfo,parent),
    mWindow(NULL)
{
    mWinFlags = Qt::Window;
    mObjType = USEOBJTYPE(HFrameStyle);
}

HFrameStyle::~HFrameStyle()
{
}

void HFrameStyle::setWindow(QWidget* window)
{
    mWindow = window;
}

void HFrameStyle::setWindowFlags(Qt::WindowFlags flags)
{
    mWinFlags = flags;
}

Qt::WindowFlags HFrameStyle::windowFlags() const
{
    return mWinFlags;
}

bool HFrameStyle::hasSceneStyle() const
{
    return (mSceneStyle.mClsName.size() > 1 && mSceneStyle.mStyleId.size()>1);
}

void HFrameStyle::setSceneStyle(const HClassInfo& cls)
{
    mSceneStyle = cls;
}

HClassInfo HFrameStyle::sceneStyle() const
{
    return mSceneStyle;
}

void HFrameStyle::copyTo(HBaseStyle* obj)
{
    HFrameStyle* style = static_cast<HFrameStyle*>(obj);
    if (!style) return ;

    style->setWindowFlags(windowFlags());
    style->setSceneStyle(sceneStyle());
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
    mWindow->setWindowFlags(windowFlags());

    if (hasStyleSheet()) {
        mWindow->setStyleSheet(styleSheet());
    }
}

void  HFrameStyle::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}

QRect HFrameStyle::calcClientRect(const QRect &frameRect) const
{
    Q_UNUSED(frameRect);

    return frameRect;
}

bool  HFrameStyle::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    //Windows	eventType = "windows_generic_MSG"	message = MSG *	 result = LRESULT

    Q_UNUSED(eventType);
    Q_UNUSED(message);
    Q_UNUSED(result);
    return false;
}
