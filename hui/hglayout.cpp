#include "hglayout.h"
#include "hgwidget.h"
#include <QWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsGridLayout>

//HGLayout
HGLayout::HGLayout(QObject* parent) :
    HLayout(parent),
    mWidget(NULL)
{
}

HGLayout::~HGLayout()
{

}

void HGLayout::setWidget(HGWidget* widget)
{
    //qDebug("HGLayout::setWidget");
    mWidget = widget;

    //todo create layout object
    setLayoutType(mLayoutType);
    setMargins(mMargins);
    setSpacing(mSpacing);
}

QGraphicsLayout* HGLayout::layout() const
{
    return mWidget?mWidget->QGraphicsWidget::layout():NULL;
}

void HGLayout::setSpacing(int s)
{
    HLayout::setSpacing(s);

    QGraphicsLayout* ll = layout();
    if (!ll) return ;

    switch (layoutType()) {
    case HEnums::kVBox:
    case HEnums::kHBox: {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(ll);
        l->setSpacing(s);
        break;
    }
    case HEnums::kGrid: {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(ll);
        l->setSpacing(s);
        break;
    }
    case HEnums::kAnchor: {
        QGraphicsAnchorLayout* l = static_cast<QGraphicsAnchorLayout*>(ll);
        l->setSpacing(s);
        break;
    }
    default:
        break;
    }
}

int HGLayout::spacing() const
{
    return HLayout::spacing();
}

QMargins HGLayout::margins() const
{
    if (layout()) {
        qreal left = 0;
        qreal top = 0;
        qreal right = 0;
        qreal bottom = 0;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        return QMargins(left, top, right, bottom);
    }
    return HLayout::margins();
}

void HGLayout::setMargins(const QMargins& m)
{
    if (layout()) {
        layout()->setContentsMargins(m.left(), m.top(), m.right(), m.bottom());
    }
    HLayout::setMargins(m);
}

Qt::Alignment HGLayout::alignment() const
{
    return HLayout::alignment();
}

void HGLayout::setAlignment(Qt::Alignment align)
{
    HLayout::setAlignment(align);

    if (!layout()) return ;

    QGraphicsLayout* l = layout();
    if (!l) return ;

    for (int i = 0; i <l->count(); i++)
        setAlignment(l->itemAt(i), align);
}

void HGLayout::setAlignment(QGraphicsLayoutItem* item, Qt::Alignment align)
{
    QGraphicsLayout* ll = layout();
    if (!ll)  return ;

    HEnums::HLayoutType type = layoutType() ;
    if (type == HEnums::kHBox || type == HEnums::kVBox) {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(ll);
        l->setAlignment(item, align);
    }
    else if(type == HEnums::kGrid) {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(ll);
        l->setAlignment(item,align);
    }
}

Qt::Alignment HGLayout::alignment(QGraphicsLayoutItem* item) const
{
    QGraphicsLayout* ll = layout();
    if (ll) {
        HEnums::HLayoutType type = layoutType() ;
        if (type == HEnums::kHBox || type == HEnums::kVBox) {
            return static_cast<QGraphicsLinearLayout*>(ll)->alignment(item);
        }
        else if(type == HEnums::kGrid) {
            return static_cast<QGraphicsGridLayout*>(ll)->alignment(item);
        }
    }
    return alignment();
}

void HGLayout::setLayoutType(HEnums::HLayoutType type)
{
    HLayout::setLayoutType(type);

    if (!mWidget) return;

    QGraphicsLayout *layout = NULL;
    switch (type) {
    case HEnums::kVBox:
        layout = new QGraphicsLinearLayout(Qt::Vertical,mWidget);
        break;
    case HEnums::kHBox:
        layout = new QGraphicsLinearLayout(Qt::Horizontal,mWidget);
        break;
    case HEnums::kGrid:
        layout = new QGraphicsGridLayout(mWidget);
        break;
    case HEnums::kAnchor:
        layout = new QGraphicsAnchorLayout(mWidget);
        break;
    default:
        qDebug("HGLayout not layout=%d",type);
        return ;
    }
    mWidget->QGraphicsWidget::setLayout(layout);
}

int HGLayout::addItem(QGraphicsLayoutItem* item)
{
    return insertItem(item,HLayoutConfig());
}

int HGLayout::insertItem(QGraphicsLayoutItem* item, const HLayoutConfig& conf)
{
    if (!layout()) return -1;

    switch (layoutType()) {
    case HEnums::kVBox:
    case HEnums::kHBox: {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(layout());
        l->insertItem(conf.index(),item);
        l->setAlignment(item,alignment());
        break;
    }
    case HEnums::kGrid: {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(layout());
        l->addItem(item,conf.row(),conf.column(),alignment());
        break;
    }
    case HEnums::kAnchor: {
        //anchor layout can't add item here, add item in setAnchor
        QGraphicsAnchorLayout* l = static_cast<QGraphicsAnchorLayout*>(layout());
        Q_UNUSED(l);

        return -1;
    }
    default:
        return -1;
    }
    return 0;
}

bool HGLayout::removeItem(QGraphicsLayoutItem *item)
{
    if (!layout()) return false;

    switch (layoutType()) {
    case HEnums::kVBox:
    case HEnums::kHBox: {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(layout());
        l->removeItem(item);
        break;
    }
    case HEnums::kGrid: {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(layout());
        l->removeItem(item);
        break;
    }
    case HEnums::kAnchor: {//"anchor layout can't remove item now!"
        QGraphicsAnchorLayout* l = static_cast<QGraphicsAnchorLayout*>(layout());
        Q_UNUSED(l);

        return false;
    }
    default:
        return false;
    }
    return true;
}

int HGLayout::addGWidget(QGraphicsWidget* widget)
{
    return insertGWidget(widget,HLayoutConfig());
}

int HGLayout::insertGWidget(QGraphicsWidget* widget, const HLayoutConfig& index)
{
    return insertItem(widget,index);
}

bool HGLayout::removeGWidget(QGraphicsWidget* widget)
{
    return removeItem(widget);
}

bool HGLayout::addChildGWidget(QGraphicsWidget* widget ,const HLayoutConfig& conf)
{
    if (!widget)
        return false;

    if (-1 == mChilds.at(widget))
        mChilds.add(widget,conf.margins());

    return true;
}

void HGLayout::removeChildGWidget(QGraphicsWidget* widget)
{
    mChilds.remove(widget);
}

void HGLayout::resizeEvent(const QSize& s)
{
    for (int i = 0; i < mChilds.count();i++) {

        const HItemWidget<QGraphicsWidget>* iter = &mChilds.at(i);

        QRectF rc(QPoint(0,0),s);

        if (iter->margins.left()<0)
            rc.setLeft( s.width() + iter->margins.left());
        if (iter->margins.left()>0)
            rc.setLeft(iter->margins.left());

        if (iter->margins.right()<0)
            rc.setRight(s.width() + iter->margins.right());
        else if(iter->margins.right()>0)
            rc.setRight(iter->margins.right());

        if (iter->margins.top()<0)
            rc.setTop( s.height() + iter->margins.top());
        else if (iter->margins.top()>0)
            rc.setTop(iter->margins.top());

        if (iter->margins.bottom()<0)
            rc.setBottom(s.height() + iter->margins.bottom());
        else if(iter->margins.bottom()>0)
            rc.setBottom(iter->margins.bottom());

        iter->widget->setGeometry(rc);
    }
}


