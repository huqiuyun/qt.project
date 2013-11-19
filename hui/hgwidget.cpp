#include "hgwidget.h"
#include "hbase.h"
#include "Hbackgroundstyle.h"
#include "hglayoutstyle.h"
#include "hgwidgetstyle.h"
#include "hstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsGridLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QWidget>
#include "private/hgwidget_p.h"

HGWidgetPrivate::HGWidgetPrivate(const char* styleid) :
    q_ptr(NULL),
    mStyleId(styleid)
{
}

HGWidgetPrivate::~HGWidgetPrivate()
{
}

void HGWidgetPrivate::init()
{
    static int s_index = 0;
    QString name = "NoNameWidget" + QString::number(s_index++);
    q_ptr->setObjectName(name);

    // find
    HGWidgetStyle* style = static_cast<HGWidgetStyle*>(HSTYLE->itemAt(mStyleId.data()).data());
    if (style)
    {
        mGWidgetStyle = QSharedPointer<HGWidgetStyle>(static_cast<HGWidgetStyle*>(style->clone()));
        initStyle(style);
    }
 }

void HGWidgetPrivate::initStyle(HGWidgetStyle* style)
{
    if (!style)
    {
        return;
    }
    style->setWidget(q_ptr);

    long hr = 0;
    if (style->hasBackgroundStyle())
    {
        HClassInfo cls = style->backgroundStyle();
        HBackgroundStyle* back = static_cast<HBackgroundStyle*>(HFACTORY->createObject(cls,q_ptr,HCreateParameter(),&hr));
        mBackgroundStyle = QSharedPointer<HBackgroundStyle>(back);
    }

    if (style->hasLayoutStyle())
    {
        HClassInfo cls = style->backgroundStyle();
        HGLayoutStyle* layout = static_cast<HGLayoutStyle*>(HFACTORY->createObject(cls,q_ptr,HCreateParameter(),&hr));
        mLayoutStyle = QSharedPointer<HGLayoutStyle>(layout);
        mLayoutStyle->setWidget(q_ptr);
    }
}

IMPLEMENT_GITEM_STATIC_CREATE(HGWidget,HGWidget)
HGWidget::HGWidget(QGraphicsItem* parent) :
    QGraphicsWidget(parent),
    d_ptr(new HGWidgetPrivate("widgetId"))
{
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGWidget::HGWidget(const HObjectInfo& objinfo,QGraphicsItem* parent):
    QGraphicsWidget(parent),
    d_ptr(new HGWidgetPrivate(objinfo.mStyleId.data()))
{
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}

HGWidget::HGWidget(HGWidgetPrivate &dd, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    d_ptr(&dd)
{
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGWidget::HGWidget(HGWidgetPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent) :
    QGraphicsWidget(parent),
    d_ptr(&dd)
{
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}

HGWidget::~HGWidget()
{
    delete d_ptr;
}

int HGWidget::height() const
{
    return static_cast<int>(size().height());
}

void HGWidget::setHeight(int h)
{
    QSizeF s = size();
    s.setHeight(h);

    resize(s);
}

int HGWidget::width() const
{
    // Rounds value to the nearest integer.
    return qRound((size().width()));
}

void HGWidget::setWidth(int w)
{
    QSizeF s = size();
    s.setWidth(w);

    resize(s);
}

QSizeF HGWidget::fixSize() const
{
    return size();
}

void HGWidget::setFixSize(const QSizeF &s)
{
    setMaximumSize(s);
    setMinimumSize(s);
    setPreferredSize(s);
}

int HGWidget::fixHeight() const
{
    return size().height();
}

void HGWidget::setFixHeight(int h)
{
    setMaximumHeight(h);
    setMinimumHeight(h);
    setPreferredHeight(h);
}

int HGWidget::fixWidth() const
{
    return size().width();
}

void HGWidget::setFixWidth(int w)
{
    setMaximumWidth(w);
    setMinimumWidth(w);
    setPreferredWidth(w);
}

void HGWidget::setGWidgetStyle(QSharedPointer<HGWidgetStyle> style)
{
    d_func()->mGWidgetStyle = style;

    d_ptr->initStyle(style.data());
}

QSharedPointer<HGWidgetStyle> HGWidget::gwidgetStyle() const
{
    return d_func()->mGWidgetStyle;
}

void HGWidget::setBackgroundStyle(QSharedPointer<HBackgroundStyle> style)
{
    d_func()->mBackgroundStyle = style;
}

QSharedPointer<HBackgroundStyle> HGWidget::backgroundStyle() const
{
    return d_func()->mBackgroundStyle;
}

void HGWidget::setLayoutStyle(QSharedPointer<HGLayoutStyle> style)
{
    d_func()->mLayoutStyle = style;
}

QSharedPointer<HGLayoutStyle> HGWidget::layoutStyle() const
{
    return d_func()->mLayoutStyle;
}

HEnums::HLayoutType HGWidget::layoutType() const
{
    Q_D(const HGWidget);
    return d->mLayoutStyle?d->mLayoutStyle->layoutType():HEnums::kNone;
}

void HGWidget::doConstruct()
{
    construct();
}

void HGWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_D(HGWidget);

    if (d->mBackgroundStyle)
    {
        d->mBackgroundStyle->draw(painter,rect().toRect());
    }
    QGraphicsWidget::paint(painter,option,widget);
}
