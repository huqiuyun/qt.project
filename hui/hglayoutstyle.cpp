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
    return 0;
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

void HGLayoutStyle::setAnchor(const HAnchor& a)
{
    HLayoutStyle::setAnchor(a);
    if (HEnums::kAnchor != layoutType()) return ;
}

Qt::Alignment HGLayoutStyle::alignment() const
{
    if (!mWidget) {
        return HLayoutStyle::alignment();
    }
    HGWidget* parent = static_cast<HGWidget*>(mWidget->parent());
    if (parent != NULL) {
        QGraphicsLayout* ll = parent->layout();
        if (ll) {
            HEnums::HLayoutType type = parent->layoutType() ;
            if (type == HEnums::kHBox ||
                    type == HEnums::kVBox) {
                QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(ll);
                return l->alignment((QGraphicsLayoutItem*)mWidget);
            }
            else if(type == HEnums::kGrid) {
                QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(ll);
                return l->alignment((QGraphicsLayoutItem*)mWidget);
            }
        }
    }
    return HLayoutStyle::alignment();
}

void HGLayoutStyle::setAlignment(Qt::Alignment align)
{
    if (!mWidget) {
        HLayoutStyle::setAlignment(align);
        return;
    }

    HGWidget* parent = static_cast<HGWidget*>(mWidget->parent());
    if (parent != NULL) {
        QGraphicsLayout* ll = parent->layout();
        if (ll) {
            HEnums::HLayoutType type = parent->layoutType() ;
            if (type == HEnums::kHBox ||
                type == HEnums::kVBox) {
                QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(ll);
                l->setAlignment(mWidget, align);
            }
            else if(type == HEnums::kGrid) {
                QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(ll);
                l->setAlignment(mWidget,align);
            }
        }
    }
    HLayoutStyle::setAlignment(align);
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
    setMargins(QMargins(0,0,0,0));
    setSpacing(0);
}

int HGLayoutStyle::addItem(QGraphicsLayoutItem* item)
{
    return insertItem(item,HLayoutIndex());
}

int HGLayoutStyle::insertItem(QGraphicsLayoutItem* item, const HLayoutIndex& index)
{
    if (!layout()) return -1;

    switch (layoutType()) {
    case HEnums::kVBox:
    case HEnums::kHBox: {
        QGraphicsLinearLayout* l = static_cast<QGraphicsLinearLayout*>(layout());
        l->insertItem(index.pos(),item);
        break;
    }
    case HEnums::kGrid: {
        QGraphicsGridLayout* l = static_cast<QGraphicsGridLayout*>(layout());
        l->addItem(item,index.pos(),index.column());
        break;
    }
    case HEnums::kAnchor: {
        //anchor layout can't add item here, add item in setAnchor

        return -1;
    }
    default:
        return -1;
    }
    return index.pos();
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
    return insertGWidget(widget,HLayoutIndex());
}

int HGLayoutStyle::insertGWidget(QGraphicsWidget* widget, const HLayoutIndex& index)
{
    return insertItem(widget,index);
}

bool HGLayoutStyle::removeGWidget(QGraphicsWidget* widget)
{
    return removeItem(widget);
}

HBaseStyle* HGLayoutStyle::clone()
{
    HGLayoutStyle* style = new HGLayoutStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}


