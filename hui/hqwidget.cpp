#include "hqwidget.h"
#include "hstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "hgview.h"
#include "hgwidget.h"
#include "hframestyle.h"
#include "hbackgroundstyle.h"
#include "hqlayoutstyle.h"
#include "hglayoutstyle.h"
#include "private/hqwidget_p.h"
#include <QGraphicsProxyWidget>

HQWidgetPrivate::HQWidgetPrivate() :
    q_ptr(NULL)
{
}

HQWidgetPrivate::~HQWidgetPrivate()
{
}

void HQWidgetPrivate::init()
{
    static int s_index = 0;
    QString name = "NoQWidget" + QString::number(s_index++);
    q_ptr->setObjectName(name);

    installStyle(HSTYLE);
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

    if (framestyle->hasLayoutStyle()) {
        HCreateParam param;
        HClassInfo cls = framestyle->layoutStyle();
        HQLayoutStyle* layout = static_cast<HQLayoutStyle*>(HFACTORY->createObject(cls,q_ptr,param));
        mLayoutStyle = QSharedPointer<HQLayoutStyle>(layout);
        mLayoutStyle->backup(style);
        mLayoutStyle->setWindow(q_ptr);
    }
    if (framestyle->hasBackgroundStyle()) {
        HCreateParam param;
        HClassInfo cls = framestyle->backgroundStyle();
        HBackgroundStyle* back = static_cast<HBackgroundStyle*>(HFACTORY->createObject(cls,q_ptr,param));
        mBackgroundStyle = QSharedPointer<HBackgroundStyle>(back);
        mBackgroundStyle->backup(style);
    }
}

IMPLEMENT_QWIDGET_STATIC_CREATE(HQWidget,HQWidget,USEOBJTYPE(HQWidget))
HQWidget::HQWidget(QWidget* parent) :
    QWidget(parent),
    d_ptr(new HQWidgetPrivate())
{
    mObjType = USEOBJTYPE(HQWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
}

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

HQWidget::HQWidget(HQWidgetPrivate &dd, QWidget *parent) :
    QWidget(parent),
    d_ptr(&dd)
{
    mObjType = USEOBJTYPE(HQWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
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

void HQWidget::setFrameStyle(QSharedPointer<HFrameStyle> style)
{
    d_func()->mFrameStyle = style;

    d_ptr->initStyle(HSTYLE);
}

QSharedPointer<HFrameStyle> HQWidget::frameStyle() const
{
    return d_func()->mFrameStyle;
}

void HQWidget::setLayoutStyle(QSharedPointer<HQLayoutStyle> style)
{
    d_func()->mLayoutStyle = style;
}

QSharedPointer<HQLayoutStyle> HQWidget::layoutStyle() const
{
    return d_func()->mLayoutStyle;
}

HEnums::HLayoutType HQWidget::layoutType() const
{
    Q_D(const HQWidget);
    return d->mLayoutStyle?d->mLayoutStyle->layoutType():HEnums::kNone;
}


/** add widget to owner layout */
int HQWidget::addWidget(QWidget* widget)
{
    Q_D(HQWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->addWidget(widget);
    return -1;
}

int HQWidget::insertWidget(QWidget* widget ,const HLayoutConf& conf)
{
    Q_D(HQWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->insertWidget(widget,conf);
    return -1;
}

bool HQWidget::removeWidget(QWidget* widget)
{
    Q_D(HQWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->removeWidget(widget);
    return false;
}

bool HQWidget::addChildWidget(QWidget* widget ,const HLayoutConf& conf)
{
    Q_D(HQWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->addChildWidget(widget,conf);
    return false;
}

void HQWidget::removeChildWidget(QWidget* widget)
{
    Q_D(HQWidget);
    if (d->mLayoutStyle)
        d->mLayoutStyle->removeChildWidget(widget);
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


void HQWidget::setWindowAttribute(QWidget* window,const QString& attribute)
{
    if (!window) return;
    QStringList list = attribute.split("|");
    for(int i=0; i< list.size();i++) {
        QString attr = list.at(i);
        QStringList item = attr.split(":");
        if (item.size()>=2)
        {
            int val = item.at(0).toInt();
            if (val>=0 && val < Qt::WA_AttributeCount)
                window->setAttribute((Qt::WidgetAttribute)val,(item.at(1)==QLatin1String("true")));
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

void HQWidget::doConstruct()
{
    Q_D(HQWidget);
    if (d->mFrameStyle)
       d->mFrameStyle->init();

    construct();
}

void HQWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(HQWidget);
    if (d->mFrameStyle) {
        d->mFrameStyle->resizeEvent(event);
    }
    if (d->mLayoutStyle)
        d->mLayoutStyle->resizeEvent(event->size());

    emit resized();
}

void HQWidget::paintEvent(QPaintEvent*)
{
    Q_D(HQWidget);
    if (d->mBackgroundStyle) {
        QPainter painter(this);
        d->mBackgroundStyle->draw(&painter,rect(),HEnums::kStateDefaultTile);
    }
}

bool HQWidget::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    return d_func()->mFrameStyle->nativeEvent(eventType,message,result);
}



