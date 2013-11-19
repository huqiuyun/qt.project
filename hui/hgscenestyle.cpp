#include "hgscenestyle.h"
#include <QGraphicsView>
#include <QGraphicsScene>

//HGSceneStyle
IMPLEMENT_OBJECT_STATIC_CREATE(HGSceneStyle)

HGSceneStyle::HGSceneStyle(QObject *parent) :
    HBaseStyle(parent),
    mView(NULL),
    mScene(NULL)
{
    mSizePolicy= QSizePolicy::Ignored;
    mAlignment = Qt::AlignCenter;
}

HGSceneStyle::HGSceneStyle(const HObjectInfo& objinfo,QObject* parent) :
    HBaseStyle(objinfo,parent),
    mView(NULL),
    mScene(NULL)
{
    mSizePolicy= QSizePolicy::Ignored;
    mAlignment = Qt::AlignCenter;
}

HGSceneStyle::~HGSceneStyle()
{

}

void HGSceneStyle::setGView(QGraphicsView* view)
{
    mView = view;
    mScene = new QGraphicsScene(this);
    mView->setScene(mScene);

    //todo
    mView->setAlignment(alignment());

    if (hasBackgroundBrush())
    {
        mScene->setBackgroundBrush(backgroundBrush());
    }

    if (hasForegroundBrush())
    {
        mScene->setForegroundBrush(foregroundBrush());
    }
}

/** set alignment in scene */
Qt::Alignment HGSceneStyle::alignment() const
{
    return mAlignment;
}

void HGSceneStyle::setAlignment(Qt::Alignment align)
{
    mAlignment = align;
}

QSizePolicy::Policy HGSceneStyle::sizePolicy() const
{
    return mSizePolicy;
}

void HGSceneStyle::setSizePolicy(QSizePolicy::Policy policy)
{
    mSizePolicy = policy;
}

bool HGSceneStyle::hasForegroundBrush() const
{
    return (mForegroundBrush.style() != Qt::NoBrush);
}

QBrush HGSceneStyle::foregroundBrush() const
{
    return mForegroundBrush;
}

void HGSceneStyle::setForegroundBrush(const QBrush& brush)
{
    mForegroundBrush = brush;
}

// scene
bool HGSceneStyle::hasBackgroundBrush() const
{
    return (mBackgroundBrush.style() != Qt::NoBrush);
}

QBrush HGSceneStyle::backgroundBrush() const
{
    return mBackgroundBrush;
}

void HGSceneStyle::setBackgroundBrush(const QBrush& brush)
{
    mBackgroundBrush = brush;
}

void HGSceneStyle::copyTo(HBaseStyle* obj)
{
    HGSceneStyle* style = static_cast<HGSceneStyle*>(obj);
    if (!style) return ;

    style->setAlignment(alignment());
    style->setBackgroundBrush(backgroundBrush());
    style->setForegroundBrush(foregroundBrush());
    style->setSizePolicy(sizePolicy());
    HBaseStyle::copyTo(obj);
}

void HGSceneStyle::reSize(const QRectF& rect)
{
    if (!mView) return ;
    if (sizePolicy() == QSizePolicy::Fixed)
    {
        mView->setSceneRect(rect);
    }
}

void HGSceneStyle::doConstruct()
{

}

HBaseStyle* HGSceneStyle::clone()
{
    HGSceneStyle* style = new HGSceneStyle(mObjinfo,parent());
    copyTo(style);

    return style;
}

