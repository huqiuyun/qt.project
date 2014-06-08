#include "hgsceneitem.h"
#include "hgscene.h"
#include "hgwidget.h"
#include "hlayoutconfig.h"
#include <QPointer>
#include <QGraphicsView>
#include <QList>

class HGSceneItemPrivate
{
public:
    HGSceneItemPrivate() :
        mView(NULL),
        mScene(NULL)
    {
        mSizePolicy = QSizePolicy::Fixed;
        mAlignment = Qt::AlignCenter;
    }

    QGraphicsView *mView;
    HGScene *mScene;
    HItemWidgets<HGWidget> mChilds;
    Qt::Alignment mAlignment;
    QBrush mForegroundBrush;
    QBrush mBackgroundBrush;
    QSizePolicy::Policy mSizePolicy;
};

//HGSceneItem
HGSceneItem::HGSceneItem(QObject *parent) :
    QObject(parent),
    d_ptr(new HGSceneItemPrivate())
{
}

HGSceneItem::~HGSceneItem()
{
    hDelete(d_ptr);
}

void HGSceneItem::setGView(QGraphicsView* view)
{
    Q_D(HGSceneItem);
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
Qt::Alignment HGSceneItem::alignment() const
{
    return d_func()->mAlignment;
}

void HGSceneItem::setAlignment(Qt::Alignment align)
{
    d_func()->mAlignment = align;
}

QSizePolicy::Policy HGSceneItem::sizePolicy() const
{
    return d_func()->mSizePolicy;
}

void HGSceneItem::setSizePolicy(QSizePolicy::Policy policy)
{
    d_func()->mSizePolicy = policy;
}

bool HGSceneItem::hasForegroundBrush() const
{
    return (d_func()->mForegroundBrush.style() != Qt::NoBrush);
}

QBrush HGSceneItem::foregroundBrush() const
{
    return d_func()->mForegroundBrush;
}

void HGSceneItem::setForegroundBrush(const QBrush& brush)
{
    d_func()->mForegroundBrush = brush;
}

// scene
bool HGSceneItem::hasBackgroundBrush() const
{
    return (d_func()->mBackgroundBrush.style() != Qt::NoBrush);
}

QBrush HGSceneItem::backgroundBrush() const
{
    return d_func()->mBackgroundBrush;
}

void HGSceneItem::setBackgroundBrush(const QBrush& brush)
{
    d_func()->mBackgroundBrush = brush;
}

bool HGSceneItem::hasScene() const
{
    return d_func()->mScene != NULL;
}

HGScene* HGSceneItem::scene() const
{
    return d_func()->mScene;
}

void HGSceneItem::reSize(const QRectF& rect)
{
    Q_D(HGSceneItem);
    if (!d->mView)
        return ;

    if (sizePolicy() == QSizePolicy::Fixed) {
        d->mView->setSceneRect(rect);
    }

    //other items adjust rect
    QSize s(rect.width(),rect.height());
    for (int i = 0; i < d->mChilds.count();i++) {

        const HItemWidget<HGWidget>* iter = &d->mChilds.at(i);

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

bool HGSceneItem::addGWidget(HGWidget* widget,const HLayoutConfig& conf)
{
    Q_UNUSED(conf);
    Q_D(HGSceneItem);
    if (hasScene()) {
        d->mScene->addItem(widget);

        if (-1 == d->mChilds.at(widget))
            d->mChilds.add(widget,conf.margins());

        return true;
    }
    return false;
}

void HGSceneItem::removeGWidget(HGWidget* widget)
{
    Q_D(HGSceneItem);
    if (hasScene()) {
        d->mScene->removeItem(widget);
        d->mChilds.remove(widget);
    }
}

bool HGSceneItem::addItem(QGraphicsItem* item,const HLayoutConfig& conf)
{
    Q_UNUSED(conf);
    Q_D(HGSceneItem);
    if (hasScene()) {
        d->mScene->addItem(item);
        return true;
    }
    return false;
}

void HGSceneItem::removeItem(QGraphicsItem* item)
{
    Q_D(HGSceneItem);
    if (hasScene()) {
        d->mScene->removeItem(item);
    }
}

HGWidget* HGSceneItem::widgetAt(int index)
{
    Q_D(HGSceneItem);

    return d->mChilds.widgetAt(index);
}

HGWidget* HGSceneItem::widgetOf(const QString& name)
{
    Q_D(HGSceneItem);

    return d->mChilds.widgetOf(name);
}

