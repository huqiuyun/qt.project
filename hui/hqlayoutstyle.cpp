#include "HQLayoutStyle.h"
#include <QWidget>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QGridLayout>

//HQLayoutStyle
IMPLEMENT_OBJECT_STATIC_CREATE(HQLayoutStyle)

HQLayoutStyle::HQLayoutStyle(QObject* parent) :
    HLayoutStyle(parent),
    mWindow(NULL)
{
    mObjType = USEOBJTYPE(HQLayoutStyle);
}

HQLayoutStyle::HQLayoutStyle(const HObjectInfo& objinfo,QObject* parent) :
    HLayoutStyle(objinfo,parent),
    mWindow(NULL)
{
    mObjType = USEOBJTYPE(HQLayoutStyle);
}

void HQLayoutStyle::setWindow(QWidget* window)
{
    mWindow = window;
    //to do create layout
    setLayoutType(mLayoutType);
    setMargins(mMargins);
    setSpacing(mSpacing);
}

QLayout* HQLayoutStyle::layout() const
{
    return mWindow?mWindow->layout():NULL;
}

int HQLayoutStyle::spacing() const
{
    return HLayoutStyle::spacing();
}

void HQLayoutStyle::setSpacing(int s)
{
    HLayoutStyle::setSpacing(s);

    QLayout* l = static_cast<QLayout*>(layout());
    if (!l) return ;

    switch (layoutType()) {
    case HEnums::kVBox:
    case HEnums::kHBox:
    case HEnums::kVBoxBottomTop:
    case HEnums::kVBoxTopBottom:
    case HEnums::kHBoxLeftRight:
    case HEnums::kHBoxRightLeft: {
        static_cast<QBoxLayout*>(l)->setSpacing(s);
        break;
    }
    case HEnums::kGrid: {
        static_cast<QGridLayout*>(l)->setSpacing(s);
        break;
    }
    case HEnums::kStacked: {
        static_cast<QStackedLayout*>(l)->setSpacing(s);
        break;
    }
    default:
        break;
    }
}

QMargins HQLayoutStyle::margins() const
{
    if (layout()) {
        int left = 0;
        int top = 0;
        int right = 0;
        int bottom = 0;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        return QMargins(left, top, right, bottom);
    }
    return HLayoutStyle::margins();
}

void HQLayoutStyle::setMargins(const QMargins& m)
{
    if (layout()) {
        layout()->setContentsMargins(m.left(), m.top(), m.right(), m.bottom());
    }
    HLayoutStyle::setMargins(m);
}

Qt::Alignment HQLayoutStyle::alignment() const
{
    return HLayoutStyle::alignment();
}

void HQLayoutStyle::setAlignment(Qt::Alignment align)
{
    HLayoutStyle::setAlignment(align);

    QLayout *l = layout();
    if (!l) return ;
    for (int i = 0; i < l->count(); i++)
        setAlignment(l->itemAt(i)->widget(),alignment());
}

void HQLayoutStyle::setAlignment(QWidget* w, Qt::Alignment align)
{
    QLayout *l = layout();
    if (l)
        l->setAlignment(w,align);
}

void HQLayoutStyle::setLayoutType(HEnums::HLayoutType type)
{
    HLayoutStyle::setLayoutType(type);

    if (!mWindow)
        return ;

    QLayout *layout = NULL;
    switch (type) {
    case HEnums::kVBox:
        layout = new QVBoxLayout(mWindow);
        break;
    case HEnums::kHBox:
        layout = new QHBoxLayout(mWindow);
        break;
    case HEnums::kVBoxBottomTop:
        layout = new QBoxLayout(QBoxLayout::BottomToTop,mWindow);
        break;
    case HEnums::kVBoxTopBottom:
        layout = new QBoxLayout(QBoxLayout::TopToBottom,mWindow);
        break;
    case HEnums::kHBoxLeftRight:
        layout = new QBoxLayout(QBoxLayout::LeftToRight,mWindow);
        break;
    case HEnums::kHBoxRightLeft:
        layout = new QBoxLayout(QBoxLayout::RightToLeft,mWindow);
        break;
    case HEnums::kGrid:
        layout = new QGridLayout(mWindow);
        break;
    case HEnums::kStacked:
        layout = new QStackedLayout(mWindow);
        break;
    default:
        return ;
    }
    mWindow->setLayout(layout);
}

int HQLayoutStyle::addWidget(QWidget* widget)
{
    Q_UNUSED(widget);
    return insertWidget(widget,HLayoutIndex());
}

int HQLayoutStyle::insertWidget(QWidget* widget ,const HLayoutIndex& index)
{
    Q_UNUSED(widget);
    Q_UNUSED(index);
    if (layout()) {
        layout()->addWidget(widget);
        layout()->setAlignment(widget,alignment());
        return 0;
    }
    return -1;
}

bool HQLayoutStyle::removeWidget(QWidget* widget)
{
    Q_UNUSED(widget);
    if (layout()) {
        layout()->removeWidget(widget);
        return true;
    }
    return false;
}

HBaseStyle* HQLayoutStyle::clone()
{
    HQLayoutStyle* style = new HQLayoutStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}



