#include "hframestyle.h"
#include <QWidget>

IMPLEMENT_OBJECT_STATIC_CREATE(HFrameStyle)
HFrameStyle::HFrameStyle(QObject *parent) :
    HBaseStyle(parent),
    mWindow(NULL)
{
    mWinFlags = Qt::Window;
}

HFrameStyle::HFrameStyle(const HObjectInfo& objinfo, QObject *parent) :
    HBaseStyle(objinfo,parent),
    mWindow(NULL)
{
    mWinFlags = Qt::Window;
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

bool HFrameStyle::hasStyleSheet() const
{
    return (mStyleSheet.size() > 1);
}

void HFrameStyle::setStyleSheet(const QString& sheet)
{
    mStyleSheet = sheet;
}

QString HFrameStyle::styleSheet() const
{
    return mStyleSheet;
}

bool HFrameStyle::hasBackgroundStyle() const
{
    return (mBackgroundStyle.mClsName.size() > 1 && mBackgroundStyle.mStyleId.size()>1);
}
void HFrameStyle::setBackgroundStyle(const HClassInfo& cls)
{
    mBackgroundStyle = cls;
}

HClassInfo HFrameStyle::backgroundStyle() const
{
    return mBackgroundStyle;
}

bool HFrameStyle::hasLayoutStyle() const
{
    return (mLayoutStyle.mClsName.size() > 1 && mLayoutStyle.mStyleId.size()>1);
}
void HFrameStyle::setLayoutStyle(const HClassInfo& cls)
{
    mLayoutStyle = cls;
}

HClassInfo HFrameStyle::layoutStyle() const
{
    return mLayoutStyle;
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
    style->setStyleSheet(styleSheet());
    HBaseStyle::copyTo(obj);
}

HBaseStyle* HFrameStyle::clone()
{
    HFrameStyle* style = new HFrameStyle(mObjinfo,parent());
    copyTo(style);

    return style;
}

void  HFrameStyle::init()
{
    mWindow->setWindowFlags(windowFlags());

    if (hasStyleSheet())
    {
        mWindow->setStyleSheet(styleSheet());
    }
    mWindow->setAttribute(Qt::WA_TranslucentBackground, true);
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
