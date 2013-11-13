#include "hgwidget.h"
#include "hbase.h"
#include "hbackgrounditem.h"
#include "hcssstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsGridLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QWidget>
#include "private/hgwidget_p.h"

HGWidgetPrivate::HGWidgetPrivate(const QLatin1String& styleid) :
    q_ptr(NULL),
    mStyleId(styleid)
{
    mCss = HCSSSTYLE->create(styleid,"HCssWidget");
}

HGWidgetPrivate::~HGWidgetPrivate()
{
}

void HGWidgetPrivate::init()
{
    static int s_index = 0;
    QString name = "NoNameWidget" + QString::number(s_index++);
    q_ptr->setObjectName(name);

    long hr = 0;
    HClassInfo cls = q_ptr->css()->backgroundItemCls();
    HBackgroundItem* back = static_cast<HBackgroundItem*>(HFACTORY->createObject(cls,q_ptr,HCreateParameter(),&hr));
    mBackground = QSharedPointer<HBackgroundItem>(back);
}

IMPLEMENT_GWIDGET_STATIC_CREATE(HGWidget)
HGWidget::HGWidget(QGraphicsItem* parent) :
    QGraphicsWidget(parent),
    d_ptr(new HGWidgetPrivate(QLatin1String("widgetId")))
{
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGWidget::HGWidget(const HObjectInfo& objinfo,QGraphicsItem* parent):
    QGraphicsWidget(parent),
    d_ptr(new HGWidgetPrivate(objinfo.mStyleId))
{
    d_ptr->q_ptr = this;
    d_ptr->init();
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.mObjName);
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
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.mObjName);
}

HGWidget::~HGWidget()
{
    delete d_ptr;
}

void HGWidget::setStyleId(const QLatin1String& id)
{
    d_func()->mStyleId = id;
}

QLatin1String HGWidget::styleId() const
{
    return d_func()->mStyleId;
}

HCssWidget* HGWidget::css()  const
{
    return static_cast<HCssWidget*>(d_func()->mCss.data());
}

bool HGWidget::setCss(QSharedPointer<HCssObject> obj)
{
    HCssWidget* css = static_cast<HCssWidget*>(obj.data());
    if (!css)
    {
        return false;
    }
    d_func()->mCss = obj;
    return true;
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

void HGWidget::setDragPolicy(qy::HDragFlag flag )
{
    css()->setDragPolicy(flag);
}

qy::HDragFlag HGWidget::dragPolicy() const
{
    return css()->dragPolicy();
}

void HGWidget::setColorizePolicy(qy::HColorizeFlag flag)
{
    css()->setColorizePolicy(flag);
}

qy::HColorizeFlag HGWidget::colorizePolicy() const
{
    return css()->colorizePolicy();
}

void HGWidget::setBackgroundItem(QSharedPointer<HBackgroundItem> background)
{
    d_func()->mBackground = background;
}

QSharedPointer<HBackgroundItem> HGWidget::backgroundItem() const
{
    return d_func()->mBackground;
}

void HGWidget::doConstruct()
{
    construct();
}

void HGWidget::setSpacing(int s)
{
    switch (layoutType())
    {
    case qy::kVBox:
    case qy::kHBox:
    {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(layout());
        if (l != NULL)
        {
            l->setSpacing(s);
            css()->setSpacing(s);
        }
        break;
    }
    case qy::kGrid:
    {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(layout());
        if (l != NULL)
        {
            l->setSpacing(s);
            css()->setSpacing(s);
        }
        break;
    }
    case qy::kAnchor:
    {
        QGraphicsAnchorLayout* l = static_cast<QGraphicsAnchorLayout*>(layout());
        if (l != NULL)
        {
            l->setSpacing(s);
            css()->setSpacing(s);
        }
        break;
    }
    default:
        break;
    }
}

QMargins HGWidget::margins() const
{
    if (layout())
    {
        qreal left = 0;
        qreal top = 0;
        qreal right = 0;
        qreal bottom = 0;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        return QMargins(left, top, right, bottom);
    }
    return QMargins();
}

void HGWidget::setMargins(const QMargins& m)
{
    if (layout())
    {
        layout()->setContentsMargins(m.left(), m.top(), m.right(), m.bottom());
    }
}

Qt::Alignment HGWidget::alignment() const
{
    HGWidget* p = static_cast<HGWidget*>(parent());
    if (p != NULL && p->layout() != NULL)
    {
        if (p->layoutType() == qy::kHBox ||
            p->layoutType() == qy::kVBox)
        {
            QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(p->layout());
            return l->alignment((QGraphicsLayoutItem*)this);
        }
        else if(p->layoutType() == qy::kGrid)
        {
            QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(p->layout());
            return l->alignment((QGraphicsLayoutItem*)this);
        }
    }
    return Qt::AlignCenter;
}

void HGWidget::setAlignment(Qt::Alignment align)
{
    HGWidget* p = static_cast<HGWidget*>(parent());
    if (p != NULL && p->layout() != NULL)
    {
        if (p->layoutType() == qy::kHBox ||
                p->layoutType() == qy::kVBox)
        {
            QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(p->layout());
            l->setAlignment(this, align);
        }
        else if(p->layoutType() == qy::kGrid)
        {
            QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(p->layout());
            return l->setAlignment(this,align);
        }
    }
}

HAnchor HGWidget::anchor() const
{
    return css()->anchor();
}

void HGWidget::setAnchor(const HAnchor& a)
{
    css()->setAnchor(a);
}

qy::HLayoutType HGWidget::layoutType() const
{
    return css()->layoutType();
}

void HGWidget::setLayout(qy::HLayoutType type)
{
    QGraphicsLayout *layout = NULL;
    switch (type)
    {
    case qy::kVBox:
        layout = new QGraphicsLinearLayout(Qt::Vertical,this);
        break;
    case qy::kHBox:
        layout = new QGraphicsLinearLayout(Qt::Horizontal,this);
        break;
    case qy::kGrid:
        layout = new QGraphicsGridLayout(this);
        break;
    case qy::kAnchor:
        layout = new QGraphicsAnchorLayout(this);
        break;
    default:
        return ;
    }
    css()->setLayout(type);
    QGraphicsWidget::setLayout(layout);
    setMargins(QMargins(0,0,0,0));
    setSpacing(0);
}

bool HGWidget::addItem(QGraphicsLayoutItem* item)
{
    return insertItem(item,HLayoutIndex());
}

bool HGWidget::insertItem(QGraphicsLayoutItem* item, const HLayoutIndex& layIndex)
{
    switch (layoutType())
    {
    case qy::kVBox:
    case qy::kHBox:
    {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(layout());
        l->insertItem(layIndex.index(),item);
        break;
    }
    case qy::kGrid:
    {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(layout());
        l->addItem(item,layIndex.row(),layIndex.column());
        break;
    }
    case qy::kAnchor:
    {
        //anchor layout can't add item here, add item in setAnchor
        return false;
    }
    default:
        return false;
    }
    return true;
}

bool HGWidget::removeItem(QGraphicsLayoutItem *item)
{
    switch (layoutType())
    {
    case qy::kVBox:
    case qy::kHBox:
    {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(layout());
        l->removeItem(item);
        break;
    }
    case qy::kGrid:
    {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(layout());
        l->removeItem(item);
        break;
    }
    case qy::kAnchor:
    {//"anchor layout can't remove item now!"
        return false;
    }
    default:
        return false;
    }
    return true;
}

bool HGWidget::addWidget(QWidget* widget)
{
    return insertWidget(widget,HLayoutIndex());
}

bool HGWidget::insertWidget(QWidget* widget ,const HLayoutIndex& layIndex)
{
    QGraphicsProxyWidget* proxy = widget->graphicsProxyWidget();
    if (!proxy)
    {
        proxy = new QGraphicsProxyWidget(this);
        proxy->setParent(this);
        proxy->setObjectName("NoGraphicsProxyWidget");
        proxy->setWidget(widget);
    }

    if (!insertItem(proxy,layIndex))
    {
        delete proxy;
        return false;
    }
    return true;
}

bool HGWidget::removeWidget(QWidget* widget)
{
    QGraphicsProxyWidget* proxy = widget->graphicsProxyWidget();
    if (!proxy)
        return false;

    return removeItem(proxy);
}

void HGWidget::on_cssStyle_changed(const QString&id)
{
    Q_UNUSED(id);
}

void HGWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_D(HGWidget);

    if (d->mBackground)
    {
        d->mBackground->draw(painter,rect().toRect());
    }
  //  QGraphicsWidget::paint(painter,option,widget);
}
