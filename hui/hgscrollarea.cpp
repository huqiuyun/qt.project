#include "hgscrollarea.h"
#include "hgscrollbar.h"
#include "hstyle.h"
#include "private/hgscrollarea_p.h"
#include <QGraphicsSceneResizeEvent>

HGScrollAreaPrivate::HGScrollAreaPrivate()
    : HGWidgetPrivate()
    , mViewport(0)
    , mHorizontalScrollBar(0)
    , mVerticalScrollBar(0)
    , mPrevHorizontalValue(0.0)
    , mPrevVerticalValue(0.0)
{
}

void HGScrollAreaPrivate::onInitStyle(const HStyle * style)
{
    Q_UNUSED(style);
    Q_Q(HGScrollArea);

    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    q->setContentsMargins(0, 0, 0, 0);

    mHorizontalScrollBar = new HGScrollBar(Qt::Horizontal,HObjectInfo("hui.ghscrollbar",""), q);
    mHorizontalScrollBar->hide();
    mHorizontalScrollBarPolicy = Qt::ScrollBarAsNeeded;
    mHorizontalScrollBar->setZValue(q->zValue()+1); // Raise scroll bar to top
    mHorizontalScrollBar->setVisible(false);

    QObject::connect(mHorizontalScrollBar, SIGNAL(sliderPositionChange(int)),
                     q, SLOT(horizontalScroll(int)));
    QObject::connect(mHorizontalScrollBar, SIGNAL(sliderPressed()),
                     q, SLOT(horizontalScrollStart()));
    QObject::connect(mHorizontalScrollBar, SIGNAL(scrollVisible(bool)),
                     q, SLOT(horizontalScrollVisible(bool)));

    mVerticalScrollBar = new HGScrollBar(Qt::Vertical,HObjectInfo("hui.gvscrollbar",""), q);
    mVerticalScrollBar->hide();
    mVerticalScrollBarPolicy = Qt::ScrollBarAsNeeded;
    mVerticalScrollBar->setZValue(q->zValue()+1); // Raise scroll bar to top
    mVerticalScrollBar->setVisible(false);

    QObject::connect(mVerticalScrollBar, SIGNAL(sliderPositionChange(int)),
                     q, SLOT(verticalScroll(int)));
    QObject::connect(mVerticalScrollBar, SIGNAL(sliderPressed()),
                     q, SLOT(verticalScrollStart()));
    QObject::connect(mVerticalScrollBar, SIGNAL(scrollVisible(bool)),
                     q, SLOT(verticalScrollVisible(bool)));

    HGWidget *viewport = new HGWidget(HObjectInfo("hui.gwidget",""));
    q->setViewport(viewport);
}

IMPLEMENT_GITEM_STATIC_CREATE(HGScrollArea,HGScrollArea)
HGScrollArea::HGScrollArea(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGScrollAreaPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGScrollArea);
}

HGScrollArea::HGScrollArea(HGScrollAreaPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent)
    :HGWidget(dd,objinfo,parent)
{
    mObjType = USEOBJTYPE(HGScrollArea);
}

HGScrollArea::~HGScrollArea()
{
}

HGScrollBar *HGScrollArea::verticalScrollBar() const
{
    Q_D(const HGScrollArea);
    return d->mVerticalScrollBar;
}

HGScrollBar *HGScrollArea::horizontalScrollBar() const
{
    Q_D(const HGScrollArea);
    return d->mHorizontalScrollBar;
}

void HGScrollArea::setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy)
{
    Q_D(HGScrollArea);
    d->mHorizontalScrollBarPolicy = policy;
}

void HGScrollArea::setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy)
{
    Q_D(HGScrollArea);
    d->mVerticalScrollBarPolicy = policy;
}

Qt::ScrollBarPolicy HGScrollArea::verticalScrollBarPolicy() const
{
    Q_D(const HGScrollArea);
    return d->mVerticalScrollBarPolicy;
}

Qt::ScrollBarPolicy HGScrollArea::horizontalScrollBarPolicy() const
{
    Q_D(const HGScrollArea);
    return d->mHorizontalScrollBarPolicy;
}

QGraphicsWidget *HGScrollArea::viewport() const
{
    Q_D(const HGScrollArea);
    return d->mViewport;
}

void HGScrollArea::setViewport(QGraphicsWidget *viewport)
{
    Q_D(HGScrollArea);
    if (d->mViewport) {
        d->mViewport->setParentItem(0);
        QList<QGraphicsItem*> children = d->mViewport->childItems();
        foreach (QGraphicsItem *child, children)
            child->setParentItem(0);
        delete d->mViewport;
    }

    d->mViewport = viewport;

    if (viewport) {
        d->mViewport->setParentItem(this);
        d->mViewport->setContentsMargins(0, 0, 0, 0);
        adjustScrollBars();
    }
    emit viewportChanged(viewport);
}

bool HGScrollArea::event(QEvent *e)
{
    Q_D(HGScrollArea);
    if (e->type() == QEvent::ApplicationLayoutDirectionChange
            || e->type() == QEvent::LayoutDirectionChange) {
    }
    else if (e->type() == QEvent::GraphicsSceneResize) {
        QGraphicsSceneResizeEvent *event =
                static_cast<QGraphicsSceneResizeEvent*>(e);

        adjustScrollBars();

        QSizeF newSize = event->newSize();
        QRectF hrect = d->mHorizontalScrollBar->boundingRect();
        QRectF vrect = d->mVerticalScrollBar->boundingRect();

        QSizeF vpSize(newSize);

        if (d->mHorizontalScrollBar->isVisible())
            vpSize.setHeight(newSize.height() - hrect.height());

        if (d->mVerticalScrollBar->isVisible())
            vpSize.setWidth(newSize.width() - vrect.width());
        d->mViewport->resize(vpSize);
    }
    return HGWidget::event(e);
}

void HGScrollArea::scrollContentsBy(qreal dx, qreal dy)
{
    Q_UNUSED(dx)
    Q_UNUSED(dy)
    prepareGeometryChange();
}

void HGScrollArea::verticalScrollStart()
{
    Q_D(HGScrollArea);
    d->mPrevVerticalValue = d->mVerticalScrollBar->scrollPos();
}

void HGScrollArea::verticalScroll(int value)
{
    Q_D(HGScrollArea);
    qreal dy = value - d->mPrevVerticalValue;
    if (!qFuzzyCompare(dy,qreal(0.0))) {
        scrollContentsBy(0.0, dy);
        d->mPrevVerticalValue = value;
    }
}

void HGScrollArea::verticalScrollVisible(bool)
{
    adjustScrollBars();
}

void HGScrollArea::horizontalScrollStart()
{
    Q_D(HGScrollArea);
    d->mPrevHorizontalValue = d->mHorizontalScrollBar->scrollPos();
}

void HGScrollArea::horizontalScroll(int value)
{
    Q_D(HGScrollArea);
    qreal dx = value - d->mPrevHorizontalValue;
    if (!qFuzzyCompare(dx,qreal(0.0))) {
        scrollContentsBy(dx, 0.0);
        d->mPrevHorizontalValue = value;
    }
}

void HGScrollArea::horizontalScrollVisible(bool)
{
    adjustScrollBars();
}

void HGScrollArea::adjustScrollBars()
{
    Q_D(HGScrollArea);

    QRectF sbgeom;
    bool h_visible = true;
    bool v_visible = true;

    if (d->mHorizontalScrollBarPolicy == Qt::ScrollBarAlwaysOff) {
        h_visible = false;
    }
    else {
        h_visible = d->mHorizontalScrollBar->isScrollVisible();
    }

    if (d->mVerticalScrollBarPolicy == Qt::ScrollBarAlwaysOff) {
        v_visible = false;
    }
    else {
        v_visible = d->mVerticalScrollBar->isScrollVisible();
    }
    //qDebug("scroll area(h=%d,v=%d)",h_visible,v_visible);

    sbgeom = boundingRect();
    if (!h_visible) {
        d->mHorizontalScrollBar->hide();
        sbgeom.setLeft(sbgeom.right());
        sbgeom.setTop(sbgeom.bottom());
        d->mHorizontalScrollBar->setGeometry(sbgeom);
    }
    else {
        int width = 0;
        if (v_visible) {
            width = d->mVerticalScrollBar->boundingRect().width();
            d->mHorizontalScrollBar->show();
        }
        else{
            d->mHorizontalScrollBar->hide();
        }
        sbgeom.setTop(sbgeom.bottom() - d->mHorizontalScrollBar->boundingRect().height());
        sbgeom.setRight(sbgeom.right() - width);
        d->mHorizontalScrollBar->setGeometry(sbgeom);

        //qDebug("hscrollbar:%d,%d",sbgeom.width(),sbgeom.height());
    }

    sbgeom = boundingRect();
    if (!v_visible) {
        d->mVerticalScrollBar->hide();
        sbgeom.setLeft(sbgeom.right());
        sbgeom.setTop(sbgeom.bottom());
        d->mVerticalScrollBar->setGeometry(sbgeom);
    } else {
        int height = 0;
        if (h_visible) {
            height = d->mHorizontalScrollBar->boundingRect().height();
            d->mVerticalScrollBar->show();
        }
        else {
            d->mVerticalScrollBar->hide();
        }
        sbgeom.setLeft(sbgeom.right() - d->mVerticalScrollBar->boundingRect().width());
        sbgeom.setBottom(sbgeom.bottom() - height);
        d->mVerticalScrollBar->setGeometry(sbgeom);

        //qDebug("vscrollbar:%d,%d",sbgeom.width(),sbgeom.height());
    }
}
