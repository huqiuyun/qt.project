#include "hgview.h"
#include "hgwidget.h"
#include "hframestyle.h"
#include "HbackgroundStyle.h"
#include "hqlayoutstyle.h"
#include "hgscenestyle.h"
#include "hcore.h"
#include "hstyle.h"
#include "hfactory.h"
#include "private/hgview_p.h"
#include <QGraphicsScene>

HGViewPrivate::HGViewPrivate(const char* styleid) :
    q_ptr(NULL),
    mStyleId(styleid)
{
}

HGViewPrivate::~HGViewPrivate()
{

}

void HGViewPrivate::init()
{
    //保证每个frame必定有名字
    static int s_index = 0;
    QString name = "NoNameFrame" + QString::number(s_index++);
    q_ptr->setObjectName(name);

    HFrameStyle* style = static_cast<HFrameStyle*>(HSTYLE->itemAt(mStyleId.data()).data());
    if (style)
    {
        mFrameStyle = QSharedPointer<HFrameStyle>(static_cast<HFrameStyle*>(style->clone()));

        initStyle(style);
    }
}

void HGViewPrivate::initStyle(HFrameStyle* style)
{
    if (!style)
    {
        return;
    }
    style->setWindow(q_ptr);

    long hr = 0;
    if (style->hasBackgroundStyle())
    {
        HClassInfo cls = style->backgroundStyle();
        HBackgroundStyle* back = static_cast<HBackgroundStyle*>(HFACTORY->createObject(cls,q_ptr,HCreateParameter(),&hr));
        mBackgroundStyle = QSharedPointer<HBackgroundStyle>(back);
    }

    if (style->hasLayoutStyle())
    {
        HClassInfo cls = style->layoutStyle();
        HQLayoutStyle* layout = static_cast<HQLayoutStyle*>(HFACTORY->createObject(cls,q_ptr,HCreateParameter(),&hr));
        mLayoutStyle = QSharedPointer<HQLayoutStyle>(layout);
        mLayoutStyle->setWindow(q_ptr);
    }

    if (style->hasSceneStyle())
    {
        HClassInfo cls = style->sceneStyle();
        HGSceneStyle* scene = static_cast<HGSceneStyle*>(HFACTORY->createObject(cls,q_ptr,HCreateParameter(),&hr));
        mSceneStyle = QSharedPointer<HGSceneStyle>(scene);
        mSceneStyle->setGView(q_ptr);
    }
}

IMPLEMENT_GVIEW_STATIC_CREATE(HGView)
HGView::HGView(QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new HGViewPrivate(""))
{
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGView::HGView(const HObjectInfo& objinfo, QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new HGViewPrivate(objinfo.mStyleId.data()))
{
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
    {
       d->mFrameStyle->init();
    }
    construct();
}

void HGView::setFrameStyle(QSharedPointer<HFrameStyle> style)
{
    Q_D(HGView);

   QSharedPointer<HFrameStyle> oldStyle = frameStyle();
    if (oldStyle == style)
        return ;

    d->mFrameStyle = style;

    d->initStyle(style.data());
}

QSharedPointer<HFrameStyle> HGView::frameStyle() const
{
    return d_func()->mFrameStyle;
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

void HGView::setBackgroundStyle(QSharedPointer<HBackgroundStyle> style)
{
    Q_D(HGView);
    d->mBackgroundStyle = style;
}

QSharedPointer<HBackgroundStyle> HGView::backgroundStyle() const
{
    return d_func()->mBackgroundStyle;
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
    if (d->mFrameStyle)
    {
    d->mFrameStyle->resizeEvent(event);
}
    QRect rect(QPoint(0, 0), event->size());
    if (d->mSceneStyle)
    {
        d->mSceneStyle->reSize(rect);
    }
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
    {
        d->mBackgroundStyle->draw(painter,rect.toRect());
    }
    else
    {
        QGraphicsView::drawBackground(painter,rect);
    }
}

