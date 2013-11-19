#include "private/hgwidget_p.h"
#include "HGStackedWidget.h"
#include <QPointer>
#include <QGraphicsSceneResizeEvent>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

class HGStackedWidgetPrivate : public HGWidgetPrivate
{
    Q_DECLARE_PUBLIC( HGStackedWidget )

public:
    HGStackedWidgetPrivate(const char* styleid);
    ~HGStackedWidgetPrivate();

    int m_currentIndex;
    QList<HGWidget *> m_widgetList;
    QPointer<QParallelAnimationGroup> m_animGroup;

    HGStackedWidget::EffectType m_effectType;
    HGStackedWidget::ChildWidgetSizeMode m_childWidgetSizeMode;
};

HGStackedWidgetPrivate::HGStackedWidgetPrivate(const char* styleid):
    HGWidgetPrivate(styleid),
    m_currentIndex( -1 ),
    m_effectType(HGStackedWidget::NullEffect),
    m_childWidgetSizeMode( HGStackedWidget::fixedMode )
{
}

HGStackedWidgetPrivate::~HGStackedWidgetPrivate()
{
}

IMPLEMENT_GITEM_STATIC_CREATE(HGStackedWidget,HGStackedWidget)
HGStackedWidget::HGStackedWidget(QGraphicsItem *parent) :
    HGWidget(*(new HGStackedWidgetPrivate("stackedwidgetId")), parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, true);
}

HGStackedWidget::HGStackedWidget(const HObjectInfo &objinfo, QGraphicsItem *parent) :
    HGWidget(*(new HGStackedWidgetPrivate(objinfo.mStyleId.data())), objinfo, parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, true);
}

HGStackedWidget::~HGStackedWidget()
{
}

int HGStackedWidget::insertHGWidget(int index, HGWidget *widget)
{
    Q_D( HGStackedWidget );

    if (index == -1)
    {
        index = d->m_widgetList.size();
    }
    else if(index > d->m_widgetList.size())
    {
        index = d->m_widgetList.size();
    }

    if (d->m_currentIndex != -1 && index <= d->m_currentIndex)
    {
        d->m_currentIndex++;
    }

    widget->setParentItem(this);
    widget->setParent(this);
    d->m_widgetList.insert(index, widget);
    widget->setVisible(false);

    return index;
}

int HGStackedWidget::currentIndex() const
{
    return d_func()->m_currentIndex;
}

void HGStackedWidget::setCurrentIndex( int index )
{
    Q_D( HGStackedWidget );

    if (index < 0 || index >= d->m_widgetList.size())
    {
        return;
    }

    if (d->m_currentIndex == index)
    {
        return;
    }

    if (d->m_currentIndex == -1 || d->m_effectType == NullEffect)
    {
        d->m_currentIndex = index;
        _resetLayout();
        return;
    }

    if (d->m_currentIndex != -1 &&
            d->m_animGroup &&
            d->m_animGroup->state() == QAbstractAnimation::Running )
    {
        d->m_animGroup->stop();
    }

    if(d->m_effectType == SlideInOutEffect)
    {
        QRectF leftRect(-size().width(), 0, size().width(), size().height());
        QRectF midRect(0, 0, size().width(), size().height());
        QRectF rightRect(size().width(), 0, size().width(), size().height());

        d->m_animGroup = new QParallelAnimationGroup(this);
        connect(d->m_animGroup, SIGNAL(finished()), SLOT(onAnimationFinished()));
        connect(d->m_animGroup,
                SIGNAL(stateChanged (QAbstractAnimation::State, QAbstractAnimation::State)),
                SLOT(onAnimationStateChanged(QAbstractAnimation::State, QAbstractAnimation::State)));

        QPropertyAnimation *slideIn = new QPropertyAnimation(hgwidgetAt(index), "geometry", d->m_animGroup);
        slideIn->setDuration(300);
        slideIn->setEasingCurve(QEasingCurve::OutQuart);
        d->m_animGroup->addAnimation(slideIn);

        QPropertyAnimation *slideOut = new QPropertyAnimation(hgwidgetAt(d->m_currentIndex), "geometry", d->m_animGroup);
        slideOut->setDuration(300);
        slideOut->setEasingCurve(QEasingCurve::OutQuart);
        d->m_animGroup->addAnimation(slideOut);

        if(index > d->m_currentIndex)
        {
            //move from right to left
            slideIn->setStartValue(rightRect);
            slideIn->setEndValue(midRect);

            slideOut->setStartValue(midRect);
            slideOut->setEndValue(leftRect);
        }
        else
        {
            //move from left to right
            slideIn->setStartValue(leftRect);
            slideIn->setEndValue(midRect);

            slideOut->setStartValue(midRect);
            slideOut->setEndValue(rightRect);
        }
        d->m_animGroup->start(QAbstractAnimation::DeleteWhenStopped);

        d->m_currentIndex = index;
        hgwidgetAt(d->m_currentIndex)->show();
    }
}

HGWidget *HGStackedWidget::hgwidgetAt(int index) const
{
    if (index < 0 || index >= d_func()->m_widgetList.count())
    {
        return NULL;
    }
    return d_func()->m_widgetList.at(index);
}

HGWidget* HGStackedWidget::hgwidgetAtByName( const QString& objectName ) const
{
    Q_D( const HGStackedWidget );

    foreach( HGWidget* item, d->m_widgetList )
    {
        if (item->objectName() == objectName )
        {
            return item;
        }
    }
    return NULL;

}

void HGStackedWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_D( HGStackedWidget );
    HGWidget::resizeEvent(event);

    foreach(HGWidget *widget, d->m_widgetList)
    {
        widget->setGeometry(QRectF(QPointF(0, 0), event->newSize()));
    }
}

void HGStackedWidget::addHGWidget(HGWidget* item)
{
    insertHGWidget(d_func()->m_widgetList.size(), item);
}

int HGStackedWidget::count() const
{
    return d_func()->m_widgetList.count();
}

void HGStackedWidget::construct()
{
    HGWidget::construct();

    setFlag( QGraphicsItem::ItemClipsChildrenToShape );
}

void HGStackedWidget::removeHGWidget( HGWidget* item )
{
    int index = hgwidgetIndex( item );
    removeAt( index );
}

void HGStackedWidget::removeAt( int index )
{
    Q_D( HGStackedWidget );
    if (index < 0 || index >= d->m_widgetList.count())
    {
        return;
    }

    if (index == d->m_currentIndex)
    {
        d->m_currentIndex = -1;
    }
    else if ( d->m_currentIndex != -1 && index < d->m_currentIndex )
    {
        d->m_currentIndex--;
    }

    d->m_widgetList.removeAt( index );

}

void HGStackedWidget::removeAll( )
{
    d_func()->m_widgetList.clear();
    d_func()-> m_currentIndex = -1;
}

int HGStackedWidget::hgwidgetIndex( const HGWidget* widget )
{
    Q_D(HGStackedWidget);

    for ( int i = 0 ; i < d->m_widgetList.size(); ++i )
    {
        if (d->m_widgetList[i] == widget)
        {
            return i;
        }
    }
    return -1;
}

void HGStackedWidget::setCurrentHGWidget( const HGWidget *widget )
{
    int index = hgwidgetIndex( widget );
    if ( index != -1 )
    {
        setCurrentIndex( index );
    }
}

void HGStackedWidget::onAnimationFinished()
{
    _resetLayout();
}

void HGStackedWidget::onAnimationStateChanged( QAbstractAnimation::State newState, QAbstractAnimation::State oldState )
{
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running)
    {
        _resetLayout();
    }
}

void HGStackedWidget::_resetLayout()
{
    Q_D(HGStackedWidget);

    if ( d->m_childWidgetSizeMode == HGStackedWidget::fixedMode )
    {
        foreach(HGWidget *widget, d->m_widgetList)
        {
            widget->setGeometry(rect());
        }
    }

    int count = d->m_widgetList.count();
    for(int i = 0; i < count; i++)
    {
        if(d->m_currentIndex == i)
        {
            if ( d->m_childWidgetSizeMode == HGStackedWidget::adjustMode )
            {
                setFixSize( QSizeF(hgwidgetAt(i)->width(), hgwidgetAt(i)->height()) );
            }
            hgwidgetAt(i)->show();
        }
        else
        {
            hgwidgetAt(i)->hide();
        }
    }
}

HGStackedWidget::EffectType HGStackedWidget::effectType() const
{
    return d_func()->m_effectType;
}

void HGStackedWidget::setEffectType(EffectType effect)
{
    d_func()->m_effectType = effect;
}

void HGStackedWidget::setChildWidgetSizeMode( ChildWidgetSizeMode mode )
{
    d_func()->m_childWidgetSizeMode = mode;
}
