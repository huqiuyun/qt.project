#include "hgscenestyle.h"
#include "hgscene.h"
#include "hgwidget.h"
#include <QPointer>
#include <QGraphicsView>
#include <QList>

class HGSceneStylePrivate
{
public:
    HGSceneStylePrivate() :
        mView(NULL),
        mScene(NULL)
    {
        mSizePolicy = QSizePolicy::Fixed;
        mAlignment = Qt::AlignCenter;
    }

    QGraphicsView *mView;
    HGScene *mScene;
    HChildWidgetList<HGWidget> mChilds;
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
    }

    //other items adjust rect
    QSize s(rect.width(),rect.height());
    for (int i = 0; i < d->mChilds.count();i++) {

        const HChildWidget<HGWidget>* iter = &d->mChilds.at(i);

        QRectF rc(QPoint(0,0),s);

        if (iter->margins.left()<0)
            rc.setLeft( s.width() + iter->margins.left());
        if (iter->margins.left()>0)
            rc.setLeft(iter->margins.left());

        if (iter->margins.right()<0)
            rc.setRight(s.width() + iter->margins.right());
        else if(iter->margins.right()>0)
            rc.setRight(iter->margins.right());

        if (iter->margins.top()<0)
            rc.setTop( s.height() + iter->margins.top());
        else if (iter->margins.top()>0)
            rc.setTop(iter->margins.top());

        if (iter->margins.bottom()<0)
            rc.setBottom(s.height() + iter->margins.bottom());
        else if(iter->margins.bottom()>0)
            rc.setBottom(iter->margins.bottom());

        iter->widget->setGeometry(rc);
    }
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

bool HGSceneStyle::addGWidget(HGWidget* widget,const HLayoutConf& conf)
{
    Q_UNUSED(conf);
    Q_D(HGSceneStyle);
    if (hasScene()) {
        d->mScene->addItem(widget);

        if (-1 == d->mChilds.at(widget))
            d->mChilds.add(widget,conf.toMargins());

        return true;
    }
    return false;
}

void HGSceneStyle::removeGWidget(HGWidget* widget)
{
    Q_D(HGSceneStyle);
    if (hasScene()) {
        d->mScene->removeItem(widget);
        d->mChilds.remove(widget);
    }
}

bool HGSceneStyle::addItem(QGraphicsItem* item,const HLayoutConf& conf)
{
    Q_UNUSED(conf);
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


