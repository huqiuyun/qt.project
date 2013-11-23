#include "hqwidget.h"
#include "hstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "hframestyle.h"
#include "Hbackgroundstyle.h"
#include "hqlayoutstyle.h"
#include "private/hqwidget_p.h"

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

int HQWidget::insertWidget(QWidget* widget ,const HLayoutIndex& layIndex)
{
    Q_D(HQWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->insertWidget(widget,layIndex);
    return -1;
}

bool HQWidget::removeWidget(QWidget* widget)
{
    Q_D(HQWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->removeWidget(widget);
    return false;
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

void HQWidget::doConstruct()
{
    Q_D(HQWidget);
    if (d->mFrameStyle) {
       d->mFrameStyle->init();
    }
    construct();
}


void HQWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(HQWidget);
    if (d->mFrameStyle) {
        d->mFrameStyle->resizeEvent(event);
    }
    emit resized();
}

bool HQWidget::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
    return d_func()->mFrameStyle->nativeEvent(eventType,message,result);
}


