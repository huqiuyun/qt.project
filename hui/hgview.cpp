#include "hgview.h"
#include "hgwidget.h"
#include "hframestyle.h"
#include "hbackgroundStyle.h"
#include "hqlayoutstyle.h"
#include "hglayoutstyle.h"
#include "hgscenestyle.h"
#include "hqwidget.h"
#include "hcore.h"
#include "hstyle.h"
#include "hfactory.h"
#include "private/hgview_p.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

HGViewPrivate::HGViewPrivate() :
    q_ptr(NULL)
{
}

HGViewPrivate::~HGViewPrivate()
{
}

void HGViewPrivate::init()
{
    static int s_index = 0;
    QString name = "NoGView" + QString::number(s_index++);
    q_ptr->setObjectName(name);

    installStyle(HSTYLE);
}

bool HGViewPrivate::installStyle(const HStyle* style)
{
    HFrameStyle* framestyle = hStyleSharedCast<HFrameStyle>(style->itemAt(q_ptr->styleId()));
    if (framestyle)
    {
        mFrameStyle = hStyleShared<HFrameStyle>(framestyle->clone());
        initStyle(style);
        return true;
    }
    return false;
}

void HGViewPrivate::initStyle(const HStyle* style)
{
    HFrameStyle* framestyle = mFrameStyle.data();
    if (!framestyle)
        return;
    framestyle->setWindow(q_ptr);

    if (framestyle->hasBackgroundStyle()) {
        HCreateParam param;
        HClassInfo cls = framestyle->backgroundStyle();
        HBackgroundStyle* back = static_cast<HBackgroundStyle*>(HFACTORY->createObject(cls,q_ptr,param));
        mBackgroundStyle = QSharedPointer<HBackgroundStyle>(back);
        mBackgroundStyle->backup(style);
    }

    if (framestyle->hasLayoutStyle()) {
        HCreateParam param;
        HClassInfo cls = framestyle->layoutStyle();
        HQLayoutStyle* layout = static_cast<HQLayoutStyle*>(HFACTORY->createObject(cls,q_ptr,param));
        mLayoutStyle = QSharedPointer<HQLayoutStyle>(layout);
        mLayoutStyle->backup(style);
        mLayoutStyle->setWindow(q_ptr);
    }

    if (framestyle->hasSceneStyle()) {
        HCreateParam param;
        HClassInfo cls = framestyle->sceneStyle();
        HGSceneStyle* scene = static_cast<HGSceneStyle*>(HFACTORY->createObject(cls,q_ptr,param));
        mSceneStyle = QSharedPointer<HGSceneStyle>(scene);
        mSceneStyle->backup(style);
        mSceneStyle->setGView(q_ptr);
    }
}

IMPLEMENT_GVIEW_STATIC_CREATE(HGView,USEOBJTYPE(HGView))
HGView::HGView(QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new HGViewPrivate())
{
    mObjType = USEOBJTYPE(HGView);
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGView::HGView(const HObjectInfo& objinfo, QWidget *parent) :
    QGraphicsView(parent),
    HObject(objinfo.mStyleId),
    d_ptr(new HGViewPrivate())
{
    mObjType = USEOBJTYPE(HGView);
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}

HGView::~HGView()
{
    delete d_ptr;
}

void HGView::doConstruct()
{
    Q_D(HGView);
    if (d->mFrameStyle)
       d->mFrameStyle->init();

    construct();
}

void HGView::installStyle(const HStyle *style)
{
    Q_D(HGView);
    if (d->installStyle(style))
        d->mFrameStyle->init();
}

void HGView::setFixedSize(const QSize &s)
{
     QGraphicsView::setFixedSize(s);
}

void HGView::setFixedHeight(int h)
{
     QGraphicsView::setFixedHeight(h);
}

void HGView::setFixedWidth(int w)
{
    QGraphicsView::setFixedWidth(w);
}

void HGView::resizeEx(const QSize &s)
{
    QGraphicsView::resize(s.width(),s.height());
}

bool HGView::hasFrameStyle() const
{
    return d_func()->mFrameStyle != NULL;
}

void HGView::setFrameStyle(QSharedPointer<HFrameStyle> style)
{
    Q_D(HGView);

   QSharedPointer<HFrameStyle> oldStyle = frameStyle();
    if (oldStyle == style)
        return ;

    d->mFrameStyle = style;

    d->initStyle(HSTYLE);
}

QSharedPointer<HFrameStyle> HGView::frameStyle() const
{
    return d_func()->mFrameStyle;
}

bool HGView::hasSceneStyle() const
{
    return d_func()->mSceneStyle != NULL;
}

void HGView::setSceneStyle(QSharedPointer<HGSceneStyle> style)
{
    Q_D(HGView);
    d->mSceneStyle = style;
}

QSharedPointer<HGSceneStyle> HGView::sceneStyle() const
{
    return d_func()->mSceneStyle;
}

bool HGView::hasBackgroundStyle() const
{
    return d_func()->mBackgroundStyle != NULL;
}

void HGView::setBackgroundStyle(QSharedPointer<HBackgroundStyle> style)
{
    Q_D(HGView);
    d->mBackgroundStyle = style;
}

QSharedPointer<HBackgroundStyle> HGView::backgroundStyle() const
{
    return d_func()->mBackgroundStyle;
}

bool HGView::hasLayoutStyle() const
{
    return d_func()->mLayoutStyle != NULL;
}

void HGView::setLayoutStyle(QSharedPointer<HQLayoutStyle> style)
{
    Q_D(HGView);
    d->mLayoutStyle = style;
}

QSharedPointer<HQLayoutStyle> HGView::layoutStyle() const
{
    return d_func()->mLayoutStyle;
}

HEnums::HLayoutType HGView::layoutType() const
{
    Q_D(const HGView);
    return d->mLayoutStyle?d->mLayoutStyle->layoutType():HEnums::kNone;
}

void HGView::resizeEvent(QResizeEvent *event)
{
    Q_D(HGView);
    if (d->mFrameStyle) {
        d->mFrameStyle->resizeEvent(event);
    }

    if (d->mSceneStyle)
        d->mSceneStyle->reSize(QRect(QPoint(0, 0), event->size()));

    if (d->mLayoutStyle)
        d->mLayoutStyle->resizeEvent(event->size());

    emit resized();
}

bool HGView::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    return d_func()->mFrameStyle->nativeEvent(eventType,message,result);
}

void HGView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_D(HGView);
    if (d->mBackgroundStyle)
        d->mBackgroundStyle->draw(painter,rect.toRect(),0);
}

/** add widget to owner layout */
int HGView::addWidget(QWidget* widget)
{
    Q_D(HGView);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->addWidget(widget);
    return -1;
}

int HGView::insertWidget(QWidget* widget ,const HLayoutConf& conf)
{
    Q_D(HGView);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->insertWidget(widget,conf);
    return -1;
}

bool HGView::removeWidget(QWidget* widget)
{
    Q_D(HGView);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->removeWidget(widget);
    return false;
}

bool HGView::addChildWidget(QWidget* widget ,const HLayoutConf& conf)
{
    Q_D(HGView);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->addChildWidget(widget,conf);

    return false;
}

void HGView::removeChildWidget(QWidget* widget)
{
    Q_D(HGView);
    if (d->mLayoutStyle)
        d->mLayoutStyle->removeChildWidget(widget);
}

/** the object is alignment in parent layout */
Qt::Alignment HGView::alignment() const
{
    return Qt::AlignCenter;
}

void HGView::setAlignment(Qt::Alignment align)
{
    HGWidget* widget = parentGWidget();
    if (widget) {
        QObject* p = NULL;
        QGraphicsProxyWidget* proxy = graphicsProxyWidget();
        if (!proxy || !(p = proxy->parent()))
            return;
        if (p->property("isHGWidget").toBool())
            static_cast<HGWidget*>(p)->layoutStyle()->setAlignment(proxy,align);
    }
    else {
        QObject* p = parent();
        if (p->property("isHQWidget").toBool()) {
            static_cast<HQWidget*>(p)->layoutStyle()->setAlignment(this,align);
        }
        else if(p->property("isHGView").toBool()) {
            static_cast<HGView*>(p)->layoutStyle()->setAlignment(this,align);
        }
    }
}

HGWidget* HGView::parentGWidget() const
{
    QObject* p = parent();
    if (p) return NULL;

    QGraphicsProxyWidget* proxy = graphicsProxyWidget();
    if (!proxy || !proxy->parent())
        return NULL;
    p = proxy->parent();
    return (p->property("isHGWidget").toBool()) ? static_cast<HGWidget*>(p) : NULL;
}
