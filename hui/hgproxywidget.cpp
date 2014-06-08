#include "hgproxywidget.h"
#include "hstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "private/hgproxywidget_p.h"
#include <QStyleOptionGraphicsItem>

HGProxyWidgetPrivate::HGProxyWidgetPrivate() :
    q_ptr(NULL)
{
}

HGProxyWidgetPrivate::~HGProxyWidgetPrivate()
{
}

void HGProxyWidgetPrivate::init()
{
    QString name = "hui.gpwidget." + QString::number(HObject::objectIndex());
    q_ptr->setObjectName(name);
    if (installStyle(HSTYLE))
        mWidgetStyle->init();
}

bool HGProxyWidgetPrivate::installStyle(const HStyle* style)
{
    HGWidgetStyle* widgetstyle = hStyleSharedCast<HGWidgetStyle>(style->itemAt(q_ptr->styleId()));
    if (widgetstyle) {
        mWidgetStyle = hStyleShared<HGWidgetStyle>(widgetstyle->clone());
        initStyle(style);
        return true;
    }
    else if(style != HSTYLE)
    {
        installStyle(HSTYLE);
    }
    else
        qDebug("HGProxyWidget not widget style %s",q_ptr->styleId());

    return false;
 }

void HGProxyWidgetPrivate::initStyle(const HStyle* style)
{
    HGWidgetStyle* widgetstyle = mWidgetStyle.data();
    if (!widgetstyle) {
        qDebug("HGProxyWidget initStyle style object is null");
        return;
    }
    widgetstyle->setWidget(q_ptr);

    HClassInfo bkgcls = widgetstyle->childAt(QLatin1String("backgroundStyle"));
    if (bkgcls.isValid()) {
        HCreateParam param;
        HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(bkgcls,q_ptr,param));
        mBkgStyle = QSharedPointer<HImageStyle>(back);
        mBkgStyle->backup(style);
    }

    onInitStyle(style);
}

HGProxyWidget::HGProxyWidget(const HObjectInfo& objinfo,QGraphicsItem* parent):
    QGraphicsProxyWidget(parent),
    HObject(objinfo.mStyleId),
    d_ptr(new HGProxyWidgetPrivate())
{
    mObjType = USEOBJTYPE(HGProxyWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGProxyWidget::HGProxyWidget(HGProxyWidgetPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent) :
    QGraphicsProxyWidget(parent),
    HObject(objinfo.mStyleId),
    d_ptr(&dd)
{
    mObjType = USEOBJTYPE(HGProxyWidget);
    d_ptr->q_ptr = this;
    d_ptr->init();
}

HGProxyWidget::~HGProxyWidget()
{
    delete d_ptr;
}

void HGProxyWidget::installStyle(const HStyle* style)
{
    d_ptr->installStyle(style);
}

void HGProxyWidget::construct()
{
}

void HGProxyWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRect rc = rect().toRect();
    Q_D(HGProxyWidget);
    if (d->mBkgStyle) {
        d->mBkgStyle->draw(painter,rc);
        d->mBkgStyle->drawSizeHint(painter,rc);
    }
    QGraphicsProxyWidget::paint(painter,option,widget);
}

void HGProxyWidget::contextMenuEvent(QGraphicsSceneContextMenuEvent *e)
{
    Q_UNUSED(e);
}
