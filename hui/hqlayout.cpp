#include "hqlayout.h"
#include <QWidget>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QGridLayout>

//HQLayout
HQLayout::HQLayout(QObject* parent) :
    HLayout(parent),
    mWindow(NULL)
{
}

void HQLayout::setWindow(QWidget* window)
{
    mWindow = window;
    //to do create layout
    setLayoutType(mLayoutType);
    setMargins(mMargins);
    setSpacing(mSpacing);
}

QLayout* HQLayout::layout() const
{
    return mWindow?mWindow->layout():NULL;
}

int HQLayout::spacing() const
{
    return HLayout::spacing();
}

void HQLayout::setSpacing(int s)
{
    HLayout::setSpacing(s);

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

QMargins HQLayout::margins() const
{
    if (layout()) {
        int left = 0;
        int top = 0;
        int right = 0;
        int bottom = 0;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        return QMargins(left, top, right, bottom);
    }
    return HLayout::margins();
}

void HQLayout::setMargins(const QMargins& m)
{
    if (layout()) {
        layout()->setContentsMargins(m.left(), m.top(), m.right(), m.bottom());
    }
    HLayout::setMargins(m);
}

Qt::Alignment HQLayout::alignment() const
{
    return HLayout::alignment();
}

void HQLayout::setAlignment(Qt::Alignment align)
{
    HLayout::setAlignment(align);

    QLayout *l = layout();
    if (!l) return ;
    for (int i = 0; i < l->count(); i++)
        setAlignment(l->itemAt(i)->widget(),alignment());
}

void HQLayout::setAlignment(QWidget* w, Qt::Alignment align)
{
    QLayout *l = layout();
    if (l)
        l->setAlignment(w,align);
}

void HQLayout::setLayoutType(HEnums::HLayoutType type)
{
    HLayout::setLayoutType(type);

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
    mWindow->QWidget::setLayout(layout);
}

int HQLayout::addWidget(QWidget* widget)
{
    Q_UNUSED(widget);
    return insertWidget(widget,HLayoutConfig());
}

int HQLayout::insertWidget(QWidget* widget ,const HLayoutConfig& conf)
{
    Q_UNUSED(widget);
    Q_UNUSED(conf);

    if (!layout())
        return -1;

    switch (layoutType()) {
    case HEnums::kVBox:
    case HEnums::kHBox:
    case HEnums::kVBoxBottomTop:
    case HEnums::kVBoxTopBottom: //=kVBox
    case HEnums::kHBoxLeftRight: //=kHBox
    case HEnums::kHBoxRightLeft: {
        QBoxLayout* l = static_cast<QBoxLayout*>(layout());
        l->insertWidget(conf.index(),widget,conf.stretch(),conf.alignment());
        if (conf.alignment()==0) l->setAlignment(widget,alignment());
        break;
    }
    case HEnums::kGrid: {
        QGridLayout* l = static_cast<QGridLayout*>(layout());
        l->addWidget(widget,conf.row(),conf.column(),conf.alignment());
        if (conf.alignment()==0) l->setAlignment(widget,alignment());
        break;
    }
    case HEnums::kStacked: {
        QStackedLayout* l = static_cast<QStackedLayout*>(layout());
        l->insertWidget(conf.index(),widget);
        l->setAlignment(widget, (conf.alignment()==0)?alignment():conf.alignment());
        break;
    }
    default: {
        Q_ASSERT(0);
        return -1;
    }
    }
    return 0;
}

bool HQLayout::removeWidget(QWidget* widget)
{
    Q_UNUSED(widget);
    if (layout()) {
        layout()->removeWidget(widget);
        return true;
    }
    return false;
}

bool HQLayout::addChildWidget(QWidget* widget ,const HLayoutConfig& conf)
{
    if (!widget)
        return false;

    if(-1 == mChilds.at(widget))
        mChilds.add(widget,conf.margins());
    return true;
}

void HQLayout::removeChildWidget(QWidget* widget)
{
    mChilds.remove(widget);
}

void HQLayout::resizeEvent(const QSize& s)
{
    for (int i = 0; i < mChilds.count(); i++) {
        const HItemWidget<QWidget>* iter = &mChilds.at(i);

        QRect rc(QPoint(0,0),s);

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


