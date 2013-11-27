#include "hglayoutStyle.h"
#include "hgwidget.h"
#include <QWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsGridLayout>

//HGLayoutStyle
IMPLEMENT_OBJECT_STATIC_CREATE(HGLayoutStyle)

HGLayoutStyle::HGLayoutStyle(QObject* parent) :
    HLayoutStyle(parent),
    mWidget(NULL)
{
    mObjType = USEOBJTYPE(HGLayoutStyle);
}

HGLayoutStyle::HGLayoutStyle(const HObjectInfo& objinfo,QObject* parent) :
    HLayoutStyle(objinfo,parent),
    mWidget(NULL)
{
    mObjType = USEOBJTYPE(HGLayoutStyle);
}

void HGLayoutStyle::setWidget(HGWidget* widget)
{
    mWidget = widget;

    //todo create layout object
    setLayoutType(mLayoutType);
    setMargins(mMargins);
    setSpacing(mSpacing);
}

QGraphicsLayout* HGLayoutStyle::layout() const
{
    return mWidget?mWidget->layout():NULL;
}

void HGLayoutStyle::setSpacing(int s)
{
    HLayoutStyle::setSpacing(s);

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

int HGLayoutStyle::spacing() const
{
    return HLayoutStyle::spacing();
}

QMargins HGLayoutStyle::margins() const
{
    if (layout()) {
        qreal left = 0;
        qreal top = 0;
        qreal right = 0;
        qreal bottom = 0;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        return QMargins(left, top, right, bottom);
    }
    return HLayoutStyle::margins();
}

void HGLayoutStyle::setMargins(const QMargins& m)
{
    if (layout()) {
        layout()->setContentsMargins(m.left(), m.top(), m.right(), m.bottom());
    }
    HLayoutStyle::setMargins(m);
}

Qt::Alignment HGLayoutStyle::alignment() const
{
    return HLayoutStyle::alignment();
}

void HGLayoutStyle::setAlignment(Qt::Alignment align)
{
    HLayoutStyle::setAlignment(align);

    if (!layout()) return ;

    QGraphicsLayout* l = layout();
    if (!l) return ;

    for (int i = 0; i <l->count(); i++)
        setAlignment(l->itemAt(i), align);
}

void HGLayoutStyle::setAlignment(QGraphicsLayoutItem* item, Qt::Alignment align)
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

Qt::Alignment HGLayoutStyle::alignment(QGraphicsLayoutItem* item) const
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

void HGLayoutStyle::setLayoutType(HEnums::HLayoutType type)
{
    HLayoutStyle::setLayoutType(type);

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
        return ;
    }
    mWidget->setLayout(layout);
}

int HGLayoutStyle::addItem(QGraphicsLayoutItem* item)
{
    return insertItem(item,HLayoutConf());
}

int HGLayoutStyle::insertItem(QGraphicsLayoutItem* item, const HLayoutConf& conf)
{
    if (!layout()) return -1;

    switch (layoutType()) {
    case HEnums::kVBox:
    case HEnums::kHBox: {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(layout());
        l->insertItem(conf.pos(),item);
        l->setAlignment(item,alignment());
        break;
    }
    case HEnums::kGrid: {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(layout());
        l->addItem(item,conf.pos(),conf.column(),alignment());
        break;
    }
    case HEnums::kAnchor: {
        //anchor layout can't add item here, add item in setAnchor

        return -1;
    }
    default:
        return -1;
    }
    return conf.pos();
}

bool HGLayoutStyle::removeItem(QGraphicsLayoutItem *item)
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
        return false;
    }
    default:
        return false;
    }
    return true;
}

int HGLayoutStyle::addGWidget(QGraphicsWidget* widget)
{
    return insertGWidget(widget,HLayoutConf());
}

int HGLayoutStyle::insertGWidget(QGraphicsWidget* widget, const HLayoutConf& index)
{
    return insertItem(widget,index);
}

bool HGLayoutStyle::removeGWidget(QGraphicsWidget* widget)
{
    return removeItem(widget);
}

bool HGLayoutStyle::addChildGWidget(QGraphicsWidget* widget ,const HLayoutConf& conf)
{
    if (!conf.mConf.use || !widget)
        return false;

    if (-1 == mChilds.at(widget))
        mChilds.add(widget,conf.toMargins());

    return true;
}

void HGLayoutStyle::removeChildGWidget(QGraphicsWidget* widget)
{
    mChilds.remove(widget);
}

void HGLayoutStyle::resizeEvent(const QSize& s)
{
    for (int i = 0; i < mChilds.count();i++) {

        const HChildWidget<QGraphicsWidget>* iter = &mChilds.at(i);

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

HBaseStyle* HGLayoutStyle::clone()
{
    HGLayoutStyle* style = new HGLayoutStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}


