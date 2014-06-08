#include "hqwidget.h"
#include "hstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "hgview.h"
#include "hgwidget.h"
#include "hframestyle.h"
#include "himagestyle.h"
#include "hqlayout.h"
#include "hglayout.h"
#include "hfontstyle.h"
#include "private/hqwidget_p.h"
#include <QGraphicsProxyWidget>

HQWidgetPrivate::HQWidgetPrivate() :
    q_ptr(NULL),
    mLayout(NULL)
{
}

HQWidgetPrivate::~HQWidgetPrivate()
{
    hDelete(mLayout);
}

void HQWidgetPrivate::init()
{
    QString name = "hui.qwidget." + QString::number(HObject::objectIndex());
    q_ptr->setObjectName(name);

    if (installStyle(HSTYLE))
        mFrameStyle->init();
}

bool HQWidgetPrivate::installStyle(const HStyle* style)
{
    // find
    HFrameStyle* framestyle = hStyleSharedCast<HFrameStyle>(style->itemAt(q_ptr->styleId()));
    if (framestyle) {
        mFrameStyle = hStyleShared<HFrameStyle>(framestyle->clone());
        initStyle(style);
        return true;
    }
    return false;
 }

void HQWidgetPrivate::initStyle(const HStyle* style)
{
    HFrameStyle* framestyle = mFrameStyle.data();
    if (!framestyle) {
        return;
    }
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

void HQWidgetPrivate::initFontStyle(const HStyle* style,const char* styleid)
{
    HFontStyle* fontstyle = hStyleSharedCast<HFontStyle>(style->itemAt(styleid));
    if (fontstyle)
        q_ptr->setFont(fontstyle->font());
    else if(style != HSTYLE) {
        //qDebug("initFontStyle:Not find font style=%s,then to do find from system style",styleid);
        initFontStyle(HSTYLE,styleid);
    }
    else
       qDebug("initFontStyle:Not find font style=%s in system style",styleid);
}

IMPLEMENT_QWIDGET_STATIC_CREATE(HQWidget,HQWidget,USEOBJTYPE(HQWidget))
HQWidget::HQWidget(const HObjectInfo& objinfo,QWidget* parent):
    QWidget(parent),
    HObject(objinfo.mStyleId),
    d_ptr(new HQWidgetPrivate())
{
    mObjType = USEOBJTYPE(HQWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}

HQWidget::HQWidget(HQWidgetPrivate& dd,const HObjectInfo& objinfo,QWidget* parent) :
    QWidget(parent),
    HObject(objinfo.mStyleId),
    d_ptr(&dd)
{
    mObjType = USEOBJTYPE(HQWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}

HQWidget::~HQWidget()
{
    delete d_ptr;
}

void HQWidget::installStyle(const HStyle* style)
{
    Q_D(HQWidget);
    if (d->installStyle(style))
        d->mFrameStyle->init();
}

void HQWidget::initFontStyle(const char* styleid,const HStyle* style)
{
    Q_D(HQWidget);
    d->initFontStyle(style?style:HSTYLE,styleid);
}

void HQWidget::setFrameStyle(QSharedPointer<HFrameStyle> style)
{
    d_func()->mFrameStyle = style;

    d_ptr->initStyle(HSTYLE);
}

QSharedPointer<HFrameStyle> HQWidget::frameStyle() const
{
    return d_func()->mFrameStyle;
}

void HQWidget::setLayout(HQLayout* l)
{
    HQLayout* o = d_func()->mLayout;
    d_func()->mLayout = l;
    if (l)
        l->setWindow(this);
    hDelete(o);
}

HQLayout* HQWidget::layout() const
{
    return d_func()->mLayout;
}

HEnums::HLayoutType HQWidget::layoutType() const
{
    Q_D(const HQWidget);
    return d->mLayout?d->mLayout->layoutType():HEnums::kNone;
}

void HQWidget::setBackgroundStyle(QSharedPointer<HImageStyle> style)
{
    Q_D(HQWidget);
    d->mBkgStyle = style;
}

QSharedPointer<HImageStyle> HQWidget::backgroundStyle() const
{
    return d_func()->mBkgStyle;
}

void HQWidget::setIndexOfBkgmage(int index)
{
    Q_D(HQWidget);
    if (d->mBkgStyle)
        d->mBkgStyle->setIndex(index);
}

int HQWidget::indexOfBkgImage() const
{
    Q_D(const HQWidget);
    return (d->mBkgStyle)?d->mBkgStyle->index():0;
}

QRect HQWidget::rectOfBackgroundImage() const
{
    return rect();
}

/** add widget to owner layout */
int HQWidget::addWidget(QWidget* widget)
{
    Q_D(HQWidget);
    if (d->mLayout)
        return d->mLayout->addWidget(widget);
    return -1;
}

int HQWidget::insertWidget(QWidget* widget ,const HLayoutConfig& conf)
{
    Q_D(HQWidget);
    if (d->mLayout)
        return d->mLayout->insertWidget(widget,conf);
    return -1;
}

bool HQWidget::removeWidget(QWidget* widget)
{
    Q_D(HQWidget);
    if (d->mLayout)
        return d->mLayout->removeWidget(widget);
    return false;
}

bool HQWidget::addChildWidget(QWidget* widget ,const HLayoutConfig& conf)
{
    Q_D(HQWidget);
    if (d->mLayout)
        return d->mLayout->addChildWidget(widget,conf);
    return false;
}

void HQWidget::removeChildWidget(QWidget* widget)
{
    Q_D(HQWidget);
    if (d->mLayout)
        d->mLayout->removeChildWidget(widget);
}

void HQWidget::setFixedSize(const QSize &s)
{
    QWidget::setFixedSize(s);
}

void HQWidget::setFixedWidth(int w)
{
    QWidget::setFixedWidth(w);
}

void HQWidget::setFixedHeight(int h)
{
    QWidget::setFixedHeight(h);
}

void HQWidget::resizeEx(const QSize &s)
{
    QWidget::resize(s.width(),s.height());
}

/** the object is alignment in parent layout */
Qt::Alignment HQWidget::alignment() const
{
    return Qt::AlignCenter;
}

void HQWidget::setAlignment(Qt::Alignment align)
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

HGWidget* HQWidget::parentGWidget() const
{
    QObject* p = parent();
    if (p) return NULL;

    QGraphicsProxyWidget* proxy = graphicsProxyWidget();
    if (!proxy || !proxy->parent())
        return NULL;
    p = proxy->parent();
    return (p->property("isHGWidget").toBool()) ? static_cast<HGWidget*>(p) : NULL;
}

void HQWidget::construct()
{

}

void HQWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(HQWidget);
    if (d->mFrameStyle) {
        d->mFrameStyle->resizeEvent(event);
    }
    if (d->mLayout)
        d->mLayout->resizeEvent(event->size());

    emit resized();
}

void HQWidget::paintEvent(QPaintEvent*)
{
    Q_D(HQWidget);
    if (d->mBkgStyle) {
        QPainter painter(this);
        d->mBkgStyle->draw(&painter,rectOfBackgroundImage());
    }
}

bool HQWidget::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    Q_D(HQWidget);
    if (d->mFrameStyle)
        return d->mFrameStyle->nativeEvent(eventType,message,result);
    return false;
}



