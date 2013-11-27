#include "hgwidget.h"
#include "hbase.h"
#include "Hbackgroundstyle.h"
#include "hglayoutstyle.h"
#include "hgwidgetstyle.h"
#include "hstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "hgproxywidget.h"
#include "private/hgwidget_p.h"

#include <QGraphicsLayoutItem>
#include <QGraphicsProxyWidget>
#include <QWidget>

HGWidgetPrivate::HGWidgetPrivate() :
    q_ptr(NULL)
{
}

HGWidgetPrivate::~HGWidgetPrivate()
{
}

void HGWidgetPrivate::init()
{
    static int s_index = 0;
    QString name = "NoGWidget" + QString::number(s_index++);
    q_ptr->setObjectName(name);
    installStyle(HSTYLE);
}

bool HGWidgetPrivate::installStyle(const HStyle* style)
{
    // find
    HGWidgetStyle* widgetstyle = hStyleSharedCast<HGWidgetStyle>(style->itemAt(q_ptr->styleId()));
    if (widgetstyle) {
        mWidgetStyle = hStyleShared<HGWidgetStyle>(widgetstyle->clone());
        initStyle(style);
        return true;
    }
    return false;
 }

void HGWidgetPrivate::initStyle(const HStyle* style)
{
    HGWidgetStyle* widgetstyle = mWidgetStyle.data();
    if (!widgetstyle) {
        return;
    }
    widgetstyle->setWidget(q_ptr);

    if (widgetstyle->hasBackgroundStyle()) {
        HCreateParam param;
        HClassInfo cls = widgetstyle->backgroundStyle();
        HBackgroundStyle* back = static_cast<HBackgroundStyle*>(HFACTORY->createObject(cls,q_ptr,param));
        mBackgroundStyle = QSharedPointer<HBackgroundStyle>(back);
        mBackgroundStyle->backup(style);
    }

    if (widgetstyle->hasLayoutStyle()) {
        HCreateParam param;
        HClassInfo cls = widgetstyle->layoutStyle();
        HGLayoutStyle* layout = static_cast<HGLayoutStyle*>(HFACTORY->createObject(cls,q_ptr,param));
        mLayoutStyle = QSharedPointer<HGLayoutStyle>(layout);
        mLayoutStyle->backup(style);
        mLayoutStyle->setWidget(q_ptr);
    }
}

IMPLEMENT_GITEM_STATIC_CREATE(HGWidget,HGWidget)
HGWidget::HGWidget(QGraphicsItem* parent) :
    QGraphicsWidget(parent),
    d_ptr(new HGWidgetPrivate())
{
    mObjType = USEOBJTYPE(HGWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();

}

HGWidget::HGWidget(const HObjectInfo& objinfo,QGraphicsItem* parent):
    QGraphicsWidget(parent),
    HObject(objinfo.mStyleId),
    d_ptr(new HGWidgetPrivate())
{
    mObjType = USEOBJTYPE(HGWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}

HGWidget::HGWidget(HGWidgetPrivate &dd, QGraphicsItem *parent) :
    QGraphicsWidget(parent),
    d_ptr(&dd)
{
    mObjType = USEOBJTYPE(HGWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGWidget::HGWidget(HGWidgetPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent) :
    QGraphicsWidget(parent),
    HObject(objinfo.mStyleId),
    d_ptr(&dd)
{
    mObjType = USEOBJTYPE(HGWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}

HGWidget::~HGWidget()
{
    delete d_ptr;
}

void HGWidget::installStyle(const HStyle *style)
{
    Q_D(HGWidget);
    d->installStyle(style);
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

QSizeF HGWidget::fixedSize() const
{
    return size();
}

void HGWidget::setFixedSize(const QSizeF &s)
{
    setMaximumSize(s);
    setMinimumSize(s);
    setPreferredSize(s);
}

int HGWidget::fixedHeight() const
{
    return size().height();
}

void HGWidget::setFixedHeight(int h)
{
    setMaximumHeight(h);
    setMinimumHeight(h);
    setPreferredHeight(h);
}

int HGWidget::fixedWidth() const
{
    return size().width();
}

void HGWidget::setFixedWidth(int w)
{
    setMaximumWidth(w);
    setMinimumWidth(w);
    setPreferredWidth(w);
}

void HGWidget::setImagePath(const QString& path)
{
    Q_D(HGWidget);
    if (d->mBackgroundStyle)
        d->mBackgroundStyle->setImagePath(path);
}

void HGWidget::setColor(const QColor& rgb)
{
    Q_D(HGWidget);
    if (d->mBackgroundStyle)
        d->mBackgroundStyle->setColor(rgb);
}

void HGWidget::setBackgroundBrush(const QBrush& brush)
{
    Q_D(HGWidget);
    if (d->mBackgroundStyle)
        d->mBackgroundStyle->setBackgroundBrush(brush);
}

void HGWidget::openGraphicsItemFlag(int flag)
{
    //ItemClipsChildrenToShape
    QGraphicsItem::setFlag((GraphicsItemFlag)flag,true);
}

void HGWidget::closeGraphicsItemFlag(int flag)
{
    //ItemClipsChildrenToShape
    QGraphicsItem::setFlag((GraphicsItemFlag)flag,false);
}

void HGWidget::setWidgetStyle(QSharedPointer<HGWidgetStyle> style)
{
    d_func()->mWidgetStyle = style;

    d_ptr->initStyle(HSTYLE);
}

QSharedPointer<HGWidgetStyle> HGWidget::widgetStyle() const
{
    return d_func()->mWidgetStyle;
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

/** add item to owner layout */
int HGWidget::addItem(QGraphicsLayoutItem* item)
{
    Q_D(HGWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->addItem(item);
    return -1;
}

int HGWidget::insertItem(QGraphicsLayoutItem* item, const HLayoutConf& conf)
{
    Q_D(HGWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->insertItem(item,conf);
    return -1;
}

bool HGWidget::removeItem(QGraphicsLayoutItem* item)
{
    Q_D(HGWidget);
    if (d->mLayoutStyle)
        return d->mLayoutStyle->removeItem(item);
    return false;
}

int HGWidget::addGWidget(QGraphicsWidget* widget)
{
    return insertGWidget(widget,HLayoutConf());
}

int HGWidget::insertGWidget(QGraphicsWidget* widget ,const HLayoutConf& index)
{
    return insertItem(widget,index);
}

bool HGWidget::removeGWidget(QGraphicsWidget* widget)
{
    return removeItem(widget);
}

int HGWidget::addWidget(QWidget* widget)
{
    return insertWidget(widget,HLayoutConf());
}

int HGWidget::insertWidget(QWidget* widget ,const HLayoutConf& index)
{
    QGraphicsProxyWidget* proxy = widget->graphicsProxyWidget();
    if (!proxy) {
        proxy = new HGProxyWidget(this);
        proxy->setParent(this);
        proxy->setObjectName("NoGProxyWidget");
        proxy->setWidget(widget);
    }

    if (!insertGWidget(proxy,index)) {
        delete proxy;
        return -1;
    }
    return 0;
}

bool HGWidget::removeWidget(QWidget* widget)
{
    QGraphicsProxyWidget* proxy = widget->graphicsProxyWidget();
    if (!proxy)
        return false;

    return removeGWidget(proxy);
}

/** the object is alignment in parent layout */
Qt::Alignment HGWidget::alignment() const
{
    HGWidget* p = static_cast<HGWidget*>(parent());
    return (p == NULL) ? Qt::AlignCenter : p->layoutStyle()->alignment(qobject_cast<QGraphicsLayoutItem*>(this));
}

void HGWidget::setAlignment(Qt::Alignment align)
{
    HGWidget* p = static_cast<HGWidget*>(parent());
    if (p == NULL) return ;
    p->layoutStyle()->setAlignment(this,align);
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

    if (d->mBackgroundStyle) {
        d->mBackgroundStyle->draw(painter,rect().toRect());
    }
    QGraphicsWidget::paint(painter,option,widget);
}
