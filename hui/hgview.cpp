#include "hgview.h"
#include "hgwidget.h"
#include "hframestyle.h"
#include "himagestyle.h"
#include "hfontstyle.h"
#include "hgsceneitem.h"
#include "hqwidget.h"
#include "hglayout.h"
#include "hqlayout.h"
#include "hcore.h"
#include "hstyle.h"
#include "hfactory.h"
#include "hlayoutconfig.h"
#include "private/hgview_p.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

HGViewPrivate::HGViewPrivate() :
    q_ptr(NULL),
    mLayout(NULL)
{
}

HGViewPrivate::~HGViewPrivate()
{
    hDelete(mLayout);
}

void HGViewPrivate::init()
{
    QString name = "hui.gview." + QString::number(HObject::objectIndex());
    q_ptr->setObjectName(name);

    if (installStyle(HSTYLE))
        mFrameStyle->init();
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

    HClassInfo backgroundcls = framestyle->childAt(QLatin1String("backgroundStyle"));
    if (backgroundcls.isValid()) {
        HCreateParam param;
        HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(backgroundcls,q_ptr,param));
        mBkgStyle = QSharedPointer<HImageStyle>(back);
        mBkgStyle->backup(style);
    }

    // font
    HClassInfo fontcls = framestyle->childAt(QLatin1String("fontStyle"));
    if (fontcls.isValid()) {
        initFontStyle(style,fontcls.mStyleId.data());
    }
    onInitStyle(style);
}

void HGViewPrivate::initFontStyle(const HStyle* style,const char* styleid)
{
    HFontStyle* fontstyle = hStyleSharedCast<HFontStyle>(style->itemAt(styleid));
    if (fontstyle)
        q_ptr->setFont(fontstyle->font());
    else if(style != HSTYLE) {
        initFontStyle(HSTYLE,styleid);
    }
    else
        qDebug("initFontStyle:Not find font style=%s in system style",styleid);
}

IMPLEMENT_GVIEW_STATIC_CREATE(HGView,USEOBJTYPE(HGView))
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

void HGView::construct()
{
}

void HGView::installStyle(const HStyle *style)
{
    Q_D(HGView);
    if (d->installStyle(style))
        d->mFrameStyle->init();
}

void HGView::initFontStyle(const char* styleid,const HStyle* style)
{
    Q_D(HGView);
    d->initFontStyle(style?style:HSTYLE,styleid);
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

void HGView::setSceneItem(QSharedPointer<HGSceneItem> style)
{
    Q_D(HGView);
    d->mSceneStyle = style;
    if (style)
        style->setGView(this);
}

QSharedPointer<HGSceneItem> HGView::sceneItem() const
{
    return d_func()->mSceneStyle;
}

void HGView::setBackgroundStyle(QSharedPointer<HImageStyle> style)
{
    Q_D(HGView);
    d->mBkgStyle = style;
}

QSharedPointer<HImageStyle> HGView::backgroundStyle() const
{
    return d_func()->mBkgStyle;
}

void HGView::setLayout(HQLayout* l)
{
    Q_D(HGView);
    HQLayout* o = d->mLayout;
    d->mLayout = l;
    if (l)
        l->setWindow(this);
    hDelete(o);
}

HQLayout* HGView::layout() const
{
    return d_func()->mLayout;
}

HEnums::HLayoutType HGView::layoutType() const
{
    Q_D(const HGView);
    return d->mLayout?d->mLayout->layoutType():HEnums::kNone;
}

void HGView::setIndexOfBkgmage(int index)
{
    Q_D(HGView);
    if (d->mBkgStyle)
        d->mBkgStyle->setIndex(index);
}

int HGView::indexOfBkgImage() const
{
    Q_D(const HGView);
    return (d->mBkgStyle)?d->mBkgStyle->index():0;
}

QRect HGView::rectOfBackgroundImage() const
{
    return rect();
}

void HGView::resizeEvent(QResizeEvent *event)
{
    Q_D(HGView);
    if (d->mFrameStyle) {
        d->mFrameStyle->resizeEvent(event);
    }

    if (d->mSceneStyle)
        d->mSceneStyle->reSize(QRect(QPoint(0, 0), event->size()));

    if (d->mLayout)
        d->mLayout->resizeEvent(event->size());

    emit resized();
}

bool HGView::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    Q_D(HGView);
    if (d->mFrameStyle)
        return d->mFrameStyle->nativeEvent(eventType,message,result);
    return false;
}

void HGView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    Q_D(HGView);
    if (d->mBkgStyle)
        d->mBkgStyle->draw(painter,rectOfBackgroundImage());
}

/** add widget to owner layout */
int HGView::addWidget(QWidget* widget)
{
    Q_D(HGView);
    if (d->mLayout)
        return d->mLayout->addWidget(widget);
    return -1;
}

int HGView::insertWidget(QWidget* widget ,const HLayoutConfig& conf)
{
    Q_D(HGView);
    if (d->mLayout)
        return d->mLayout->insertWidget(widget,conf);
    return -1;
}

bool HGView::removeWidget(QWidget* widget)
{
    Q_D(HGView);
    if (d->mLayout)
        return d->mLayout->removeWidget(widget);
    return false;
}

bool HGView::addChildWidget(QWidget* widget ,const HLayoutConfig& conf)
{
    Q_D(HGView);
    if (d->mLayout)
        return d->mLayout->addChildWidget(widget,conf);

    return false;
}

void HGView::removeChildWidget(QWidget* widget)
{
    Q_D(HGView);
    if (d->mLayout)
        d->mLayout->removeChildWidget(widget);
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
            static_cast<HGWidget*>(p)->layout()->setAlignment(proxy,align);
    }
    else {
        QObject* p = parent();
        if (p->property("isHQWidget").toBool()) {
            static_cast<HQWidget*>(p)->layout()->setAlignment(this,align);
        }
        else if(p->property("isHGView").toBool()) {
            static_cast<HGView*>(p)->layout()->setAlignment(this,align);
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

HGWidget* HGView::rootWidget() const
{
    return widgetAt(0);
}

HGWidget* HGView::widgetAt(int index) const
{
    Q_D(const HGView);
    return d->mSceneStyle?d->mSceneStyle->widgetAt(index):NULL;
}

HGWidget* HGView::widgetOf(const QString& name) const
{
    Q_D(const HGView);
    return d->mSceneStyle?d->mSceneStyle->widgetOf(name):NULL;
}
