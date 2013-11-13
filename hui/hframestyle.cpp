#include "hframestyle.h"
#include "HGView.h"

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

qreal HFrameStyle::opacity() const
{
    return 0.0;
}

void  HFrameStyle::init()
{
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

#if defined(WIN32)
#include "hframestyle_win32.cpp"
#endif //WIN32
