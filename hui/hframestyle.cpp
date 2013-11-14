#include "hframestyle.h"
#include "HGView.h"
#include "hcssstyle.h"

IMPLEMENT_OBJECT_STATIC_CREATE(HFrameStyle)
HFrameStyle::HFrameStyle(QObject *parent) :
    QObject(parent),
    mStyleId("framestyleId"),
    mView(NULL)
{
}

HFrameStyle::HFrameStyle(const HObjectInfo& objinfo, QObject *parent) :
    QObject(parent),
    mStyleId(objinfo.mStyleId),
    mView(NULL)
{
    if (objinfo.mObjName.size()) setObjectName(objinfo.mObjName);
}

HFrameStyle::~HFrameStyle()
{

}

void HFrameStyle::setView(HGView* view)
{
    mView = view;
}

void HFrameStyle::setStyleId(const QLatin1String& id)
{
    mStyleId = id;
}

QLatin1String HFrameStyle::styleId() const
{
    return mStyleId;
}

HCssFrame* HFrameStyle::css() const
{
    return mView->css();
}

qreal HFrameStyle::opacity() const
{
    return 0.0;
}

void  HFrameStyle::init()
{
    mView->setWindowFlags(css()->windowFlags());

    if (css()->hasStyleSheet())
    {
        mView->setStyleSheet(css()->styleSheet());
    }
    mView->setAttribute(Qt::WA_TranslucentBackground, true);
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

bool  HFrameStyle::isAnimationEnabled() const
{
    return false;
}

bool  HFrameStyle::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    //Windows	eventType = "windows_generic_MSG"	message = MSG *	 result = LRESULT

    Q_UNUSED(eventType);
    Q_UNUSED(message);
    Q_UNUSED(result);
    return false;
}
