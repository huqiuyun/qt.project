#include "hgscenestyle.h"
#include "hgscene.h"
#include "hgwidget.h"
#include <QPointer>
#include <QGraphicsView>

class HGSceneStylePrivate
{
public:
    HGSceneStylePrivate() :
        mView(NULL),
        mScene(NULL),
        mMWidget(NULL)
    {
        mSizePolicy = QSizePolicy::Fixed;
        mAlignment = Qt::AlignCenter;
    }

    QGraphicsView *mView;
    HGScene *mScene;
    QPointer<HGWidget> mMWidget;
    Qt::Alignment mAlignment;
    QBrush mForegroundBrush;
    QBrush mBackgroundBrush;
    QSizePolicy::Policy mSizePolicy;
};

//HGSceneStyle
IMPLEMENT_OBJECT_STATIC_CREATE(HGSceneStyle)

HGSceneStyle::HGSceneStyle(QObject *parent) :
    HBaseStyle(parent),
    d_ptr(new HGSceneStylePrivate())
{
}

HGSceneStyle::HGSceneStyle(const HObjectInfo& objinfo,QObject* parent) :
    HBaseStyle(objinfo,parent),
    d_ptr(new HGSceneStylePrivate())
{
    mObjType = USEOBJTYPE(HGSceneStyle);
}

HGSceneStyle::~HGSceneStyle()
{
    hDelete(d_ptr);
}

void HGSceneStyle::setGView(QGraphicsView* view)
{
    Q_D(HGSceneStyle);
    if (!d->mScene)
        d->mScene = new HGScene(this);

    d->mView = view;
    d->mView->setScene(d->mScene);

    //todo
    d->mView->setAlignment(d->mAlignment);

    if (hasBackgroundBrush()) {
        d->mScene->setBackgroundBrush(d->mBackgroundBrush);
    }

    if (hasForegroundBrush()) {
        d->mScene->setForegroundBrush(d->mForegroundBrush);
    }
}

/** set alignment in scene */
Qt::Alignment HGSceneStyle::alignment() const
{
    return d_func()->mAlignment;
}

void HGSceneStyle::setAlignment(Qt::Alignment align)
{
    d_func()->mAlignment = align;
}

QSizePolicy::Policy HGSceneStyle::sizePolicy() const
{
    return d_func()->mSizePolicy;
}

void HGSceneStyle::setSizePolicy(QSizePolicy::Policy policy)
{
    d_func()->mSizePolicy = policy;
}

bool HGSceneStyle::hasForegroundBrush() const
{
    return (d_func()->mForegroundBrush.style() != Qt::NoBrush);
}

QBrush HGSceneStyle::foregroundBrush() const
{
    return d_func()->mForegroundBrush;
}

void HGSceneStyle::setForegroundBrush(const QBrush& brush)
{
    d_func()->mForegroundBrush = brush;
}

// scene
bool HGSceneStyle::hasBackgroundBrush() const
{
    return (d_func()->mBackgroundBrush.style() != Qt::NoBrush);
}

QBrush HGSceneStyle::backgroundBrush() const
{
    return d_func()->mBackgroundBrush;
}

void HGSceneStyle::setBackgroundBrush(const QBrush& brush)
{
    d_func()->mBackgroundBrush = brush;
}

void HGSceneStyle::copyTo(HBaseStyle* obj)
{
    Q_D(HGSceneStyle);
    HGSceneStyle* style = static_cast<HGSceneStyle*>(obj);
    if (!style) return ;

    style->setAlignment(d->mAlignment);
    style->setBackgroundBrush(d->mBackgroundBrush);
    style->setForegroundBrush(d->mForegroundBrush);
    style->setSizePolicy(d->mSizePolicy);
    HBaseStyle::copyTo(obj);
}

bool HGSceneStyle::hasScene() const
{
    return d_func()->mScene != NULL;
}

HGScene* HGSceneStyle::scene() const
{
    return d_func()->mScene;
}

void HGSceneStyle::reSize(const QRectF& rect)
{
    Q_D(HGSceneStyle);
    if (!d->mView)
        return ;

    if (sizePolicy() == QSizePolicy::Fixed) {
        d->mView->setSceneRect(rect);
        if (d->mMWidget)
            d->mMWidget->setGeometry(rect);
    }
    //other items adjust rect
}

void HGSceneStyle::doConstruct()
{
}

HBaseStyle* HGSceneStyle::clone()
{
    HGSceneStyle* style = new HGSceneStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}

bool HGSceneStyle::addGWidget(HGWidget* widget,bool main)
{
    Q_UNUSED(main);
    Q_D(HGSceneStyle);
    if (hasScene()) {
        if (main)
            d->mMWidget = widget;
        d->mScene->addItem(widget);
        return true;
    }
    return false;
}

void HGSceneStyle::removeGWidget(HGWidget* widget)
{
    Q_D(HGSceneStyle);
    if (hasScene()) {
        d->mScene->removeItem(widget);
    }
}

bool HGSceneStyle::addItem(QGraphicsItem* item)
{
    Q_D(HGSceneStyle);
    if (hasScene()) {
        d->mScene->addItem(item);
        return true;
    }
    return false;
}

void HGSceneStyle::removeItem(QGraphicsItem* item)
{
    Q_D(HGSceneStyle);
    if (hasScene()) {
        d->mScene->removeItem(item);
    }
}


