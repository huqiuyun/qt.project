#include "hgwidget.h"
#include "himagestyle.h"
#include "hgwidgetstyle.h"
#include "hfontstyle.h"
#include "hstyle.h"
#include "hglayout.h"
#include "hcore.h"
#include "hfactory.h"
#include "hgproxywidget.h"
#include "hbus.h"
#include "private/hgwidget_p.h"
#include "hglobal.h"
#include <QGraphicsSceneEvent>
#include <QGraphicsLayoutItem>
#include <QGraphicsProxyWidget>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

HGWidgetPrivate::HGWidgetPrivate() :
    q_ptr(NULL),
    mLayout(NULL),
    mItemStyle(HGWidget::GUnk),
    mState(HEnums::kStateNormal)
{
}

HGWidgetPrivate::~HGWidgetPrivate()
{
    hDelete(mLayout);
}

void HGWidgetPrivate::init()
{
    QString name = "hui.gwidget." + QString::number(HObject::objectIndex());
    q_ptr->setObjectName(name);
    q_ptr->setFocusPolicy(Qt::NoFocus);
    if (installStyle(HSTYLE))
        mWidgetStyle->init();
}

bool HGWidgetPrivate::installStyle(const HStyle* style)
{
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

    HClassInfo backgroundcls = widgetstyle->childAt(QLatin1String("backgroundStyle"));
    if (backgroundcls.isValid()) {
        HCreateParam param;
        HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(backgroundcls,q_ptr,param));
        mBkgStyle = QSharedPointer<HImageStyle>(back);
        mBkgStyle->backup(style);
    }

    // font
    HClassInfo fontcls = mWidgetStyle->childAt(QLatin1String("fontStyle"));
    if (fontcls.isValid()) {
        initFontStyle(style,fontcls.mStyleId.data());
    }
    onInitStyle(style);
}

void HGWidgetPrivate::initFontStyle(const HStyle* style,const char* styleid)
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

IMPLEMENT_GITEM_STATIC_CREATE(HGWidget,HGWidget)
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

void HGWidget::initFontStyle(const char* styleid,const HStyle* style)
{
    Q_D(HGWidget);
    d->initFontStyle(style?style:HSTYLE,styleid);
}

void HGWidget::initialize()
{
}

HGWidget::ItemStyles HGWidget::itemStyle() const
{
    return d_func()->mItemStyle;
}

void HGWidget::setItemStyle(const ItemStyles &style)
{
    d_func()->mItemStyle = style;
    on_itemStyleChanged();
}

void HGWidget::on_itemStyleChanged() {}
void HGWidget::on_mousePressed() {}
void HGWidget::on_mouseReleased() {}
void HGWidget::on_keyPressed() {}

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

void HGWidget::setIndexOfBkgmage(int index)
{
    Q_D(HGWidget);
    if (d->mBkgStyle)
        d->mBkgStyle->setIndex(index);
}

int HGWidget::indexOfBkgImage() const
{
    Q_D(const HGWidget);
    return (d->mBkgStyle)?d->mBkgStyle->index():0;
}

void HGWidget::openGItemFlag(int flag)
{
    //ItemClipsChildrenToShape
    QGraphicsItem::setFlag((GraphicsItemFlag)flag,true);
}

void HGWidget::closeGItemFlag(int flag)
{
    //ItemClipsChildrenToShape
    QGraphicsItem::setFlag((GraphicsItemFlag)flag,false);
}

Qt::MouseButtons HGWidget::acceptedMouseButtons() const
{
    return QGraphicsWidget::acceptedMouseButtons();
}

void HGWidget::setAcceptedMouseButtons(Qt::MouseButtons buttons)
{
    //qDebug("HGWidget::setAcceptedMouseButtons");
    QGraphicsWidget::setAcceptedMouseButtons(buttons);
}

bool HGWidget::acceptHoverEvents() const
{
    return QGraphicsWidget::acceptHoverEvents();
}

void HGWidget::setAcceptHoverEvents(bool enabled)
{
    //qDebug("HGWidget::setAcceptHoverEvents %d",enabled);
    QGraphicsWidget::setAcceptHoverEvents(enabled);
}

bool HGWidget::acceptTouchEvents() const
{
    return QGraphicsWidget::acceptTouchEvents();
}

void HGWidget::setAcceptTouchEvents(bool enabled)
{
    QGraphicsWidget::setAcceptTouchEvents(enabled);
}

void HGWidget::setToolTip(const QString& tip)
{
    QGraphicsWidget::setToolTip(tip);
}

QString HGWidget::toolTip() const
{
    return QGraphicsWidget::toolTip();
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

void HGWidget::setBackgroundStyle(QSharedPointer<HImageStyle> style)
{
    d_func()->mBkgStyle = style;
}

QSharedPointer<HImageStyle> HGWidget::backgroundStyle() const
{
    return d_func()->mBkgStyle;
}

void HGWidget::setLayout(HGLayout* l)
{
    HGLayout* o = d_func()->mLayout;
    d_func()->mLayout = l;
    if (l)
        l->setWidget(this);
    hDelete(o);
}

HGLayout* HGWidget::layout() const
{
    return d_func()->mLayout;
}

HEnums::HLayoutType HGWidget::layoutType() const
{
    Q_D(const HGWidget);
    return d->mLayout?d->mLayout->layoutType():HEnums::kNone;
}

void HGWidget::setStatisticsId(const QString& id)
{
    Q_D(HGWidget);
    d->mStatisticsId = id;
}

QString HGWidget::statisticsId() const
{
    return d_func()->mStatisticsId;
}

/** add item to owner layout */
int HGWidget::addGItem(QGraphicsLayoutItem* item)
{
    Q_D(HGWidget);
    if (d->mLayout)
        return d->mLayout->addItem(item);
    return -1;
}

int HGWidget::insertGItem(QGraphicsLayoutItem* item, const HLayoutConfig& conf)
{
    Q_D(HGWidget);
    if (d->mLayout)
        return d->mLayout->insertItem(item,conf);
    return -1;
}

bool HGWidget::removeGItem(QGraphicsLayoutItem* item)
{
    Q_D(HGWidget);
    if (d->mLayout)
        return d->mLayout->removeItem(item);
    return false;
}

int HGWidget::addGWidget(QGraphicsWidget* widget)
{
    return insertGWidget(widget,HLayoutConfig());
}

int HGWidget::insertGWidget(QGraphicsWidget* widget ,const HLayoutConfig& index)
{
    return insertGItem(widget,index);
}

bool HGWidget::removeGWidget(QGraphicsWidget* widget)
{
    return removeGItem(widget);
}

int HGWidget::addWidget(QWidget* widget)
{
    return insertWidget(widget,HLayoutConfig());
}

int HGWidget::insertWidget(QWidget* widget ,const HLayoutConfig& conf)
{
    QGraphicsProxyWidget* proxy = widget->graphicsProxyWidget();
    if (!proxy) {
        HGProxyWidget* p = createProxyWidget(conf.proxyWidget());
        p->setParent(this);
        p->setObjectName(QLatin1String("hui.gpwidget.") + widget->objectName());
        p->installStyle(conf.style());
        p->setWidget(widget);
        proxy = p;
    }

    if (0!=insertGWidget(proxy,conf)) {
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

    if (removeGWidget(proxy)) {
        proxy->setWidget(NULL);
        delete proxy;
        return true;
    }
    return false;
}

QWidget* HGWidget::qwidgetOf(const QString& name)
{
     QGraphicsProxyWidget* proxy =
             findChild<QGraphicsProxyWidget*>(QLatin1String("hui.gpwidget.")+name);
     return (!proxy) ? NULL : proxy->widget();
}

HGProxyWidget* HGWidget::createProxyWidget(const HClassInfo& info)
{
    //qDebug("HGWidget::createProxyWidget class=%s styleid=%s",info.mClsName.data(),info.mStyleId.data());
    return hDoConstructT(new HGProxyWidget(info,this));
}

bool HGWidget::addChildGWidget(QGraphicsWidget* item, const HLayoutConfig& conf)
{
    Q_D(HGWidget);
    if (d->mLayout)
        return d->mLayout->addChildGWidget(item,conf);
    return false;
}

void HGWidget::removeChildGWidget(QGraphicsWidget* item)
{
    Q_D(HGWidget);
    if (d->mLayout)
        d->mLayout->removeChildGWidget(item);
}

/** the object is alignment in parent layout */
Qt::Alignment HGWidget::alignment() const
{
    HGWidget* p = static_cast<HGWidget*>(parent());
    return (p == NULL) ? Qt::AlignCenter : p->layout()->alignment(qobject_cast<QGraphicsLayoutItem*>(this));
}

void HGWidget::setAlignment(Qt::Alignment align)
{
    HGWidget* p = static_cast<HGWidget*>(parent());
    if (p == NULL) return ;
    p->layout()->setAlignment(this,align);
}

void HGWidget::construct(){}

void HGWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    Q_D(HGWidget);
    if (d->mBkgStyle) {
        d->mBkgStyle->draw(painter,option->rect);
        d->mBkgStyle->drawSizeHint(painter,rect().toRect());
    }
}

void HGWidget::paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    qDebug("HGWidget::paintWindowFrame");
}

void HGWidget::resizeEvent(QGraphicsSceneResizeEvent *e)
{
    Q_UNUSED(e);
    Q_D(HGWidget);
    if (d->mLayout)
        d->mLayout->resizeEvent(e->newSize().toSize());
}

void HGWidget::contextMenuEvent(QGraphicsSceneContextMenuEvent *e)
{
    Q_UNUSED(e);
}

void HGWidget::mousePressEvent ( QGraphicsSceneMouseEvent * e )
{
    Q_D(HGWidget);
    if (!HEnums::testState(d->mState,HEnums::kStatePressed)) {
        //qDebug("HGWidget::mousePress");
        d->mState |= HEnums::kStatePressed;
        d->stateChanged();
        on_mousePressed();
    }
    emit pressed(e->pos());
}

void HGWidget::mouseReleaseEvent ( QGraphicsSceneMouseEvent * e )
{
    Q_D(HGWidget);
    if (HEnums::testState(d->mState,HEnums::kStatePressed)) {
        //qDebug("HGWidget::mouseRelease");
        d->mState &= ~HEnums::kStatePressed;
        d->stateChanged();
    }
    if (rect().contains(e->pos())) {
        on_mouseReleased();
    }
    emit released(e->pos());
}

void HGWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    Q_D(HGWidget);

    if (HEnums::testState(d->mState,HEnums::kStatePressed)) {
        if (rect().contains(e->pos())) {
            if (!HEnums::testState(d->mState,HEnums::kStateOver)) {
                d->mState |= HEnums::kStateOver;
                d->stateChanged();
            }
        }
        else if (HEnums::testState(d->mState,HEnums::kStateOver)) {
            d->mState &= ~HEnums::kStateOver;
            d->stateChanged();
        }
    }
}

void HGWidget::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    Q_D(HGWidget);
    if (!HEnums::testState(d->mState,HEnums::kStateOver)) {
        //qDebug("HGWidget::hoverEnter %s",objectName().toLocal8Bit().data());
        d->mState |= HEnums::kStateOver;
        d->stateChanged();
    }
    emit hoverEnter(e->pos());
}

void HGWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    Q_UNUSED(e);
    Q_D(HGWidget);
    if (HEnums::testState(d->mState,HEnums::kStateOver)) {
        //qDebug("HGWidget::hoverLeave %s",objectName().toLocal8Bit().data());
        d->mState &= ~HEnums::kStateOver;
        d->stateChanged();
    }
    emit hoverLeave(e->pos());
}

void HGWidget::focusInEvent(QFocusEvent *e)
{
    Q_UNUSED(e);
    Q_D(HGWidget);
    if (!HEnums::testState(d->mState,HEnums::kStateFoucs)) {
        qDebug("HGWidget::focusIn %s",objectName().toLocal8Bit().data());
        d->mState |= HEnums::kStateFoucs;
        d->stateChanged();
    }
    emit focusIn();
}

void HGWidget::focusOutEvent(QFocusEvent *e)
{
    Q_UNUSED(e);
    Q_D(HGWidget);
    if (HEnums::testState(d->mState,HEnums::kStateFoucs)) {
        qDebug("HGWidget::focusOut %s",objectName().toLocal8Bit().data());
        d->mState &= ~HEnums::kStateFoucs;
        d->stateChanged();
    }
    emit focusOut();
}

void HGWidget::keyPressEvent(QKeyEvent *e)
{
    Q_D(HGWidget);
    if (isEnabled()) {

        QGraphicsItem::GraphicsItemFlags itemFlags = flags();
        if (!itemFlags.testFlag(QGraphicsItem::ItemIsFocusable) ||
                Qt::NoFocus == focusPolicy()) {
            return QGraphicsWidget::keyPressEvent(e);
        }
        //qDebug("HGWidget::keyPressEvent");
        switch (e->key()) {
        case Qt::Key_Enter:
            if (d->mItemStyle.testFlag(KeyEnterClicked))  {
                on_keyPressed();
                return;
            }
        case Qt::Key_Return:
            if (d->mItemStyle.testFlag(KeyReturnClicked)) {
                on_keyPressed();
                return;
            }
        case Qt::Key_Space:
            if (d->mItemStyle.testFlag(KeySpaceClicked))  {
                on_keyPressed();
                return;
            }
        }
    }
    QGraphicsWidget::keyPressEvent(e);
}

void HGWidget::on_enabledChanged()
{
    Q_D(HGWidget);

    if (HGWidget::isEnabled()) {
        if (HEnums::testState(d->mState,HEnums::kStateDisable)) {
            //qDebug("HGWidget::on_enabledChanged true");
            d->mState &= ~HEnums::kStateDisable;
            d->stateChanged();
        }
    }
    else if (!HEnums::testState(d->mState,HEnums::kStateDisable)) {
        //qDebug("HGWidget::on_enabledChanged false");
        d->mState |= HEnums::kStateDisable;
        d->stateChanged();
    }
}

void HGWidget::on_clicked()
{
    emit clicked();

    QVariantList args;
    args << statisticsId();
    HBUS->directCall(QLatin1String("hui.app.statistics"), "IStatistics", "clicked", args);
}

