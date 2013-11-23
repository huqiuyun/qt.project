#ifndef HGSTACKEDWIDGET_H
#define HGSTACKEDWIDGET_H

#include "hgwidget.h"
#include <QAbstractAnimation>

class QGraphicsSceneResizeEvent;
class HGStackedWidgetPrivate;
class QGraphicsWidget;

class H_API HGStackedWidget : public HGWidget
{
	Q_OBJECT
    Q_DISABLE_COPY( HGStackedWidget )
    Q_DECLARE_PRIVATE( HGStackedWidget )
public:
	enum EffectType
	{
		NullEffect,
		SlideInOutEffect
	};
	Q_ENUMS(EffectType)
	Q_PROPERTY( EffectType effectType READ effectType WRITE setEffectType )
    Q_PROPERTY( int currentIndex READ currentIndex WRITE setCurrentIndex )
    Q_PROPERTY( int count READ count)
    Q_PROPERTY( bool isGLayout READ isGLayout)

	enum ChildWidgetSizeMode
	{
		fixedMode,
		adjustMode
	};
    Q_ENUMS(ChildWidgetSizeMode)

public:
    DECLARE_GITEM_STATIC_CREATE(HGStackedWidget);
    explicit HGStackedWidget( QGraphicsItem *parent = NULL );
    explicit HGStackedWidget(const HObjectInfo& objinfo, QGraphicsItem *parent = NULL );
    ~HGStackedWidget();

public:
    virtual bool isGLayout() { return true;}
    int  addGWidget(QGraphicsWidget* item);
    int  insertGWidget(QGraphicsWidget* item, const HLayoutIndex& index);
    bool removeGWidget(QGraphicsWidget* item);

    void removeAt( int index );
	void removeAll();

	int currentIndex() const;
	Q_INVOKABLE void setCurrentIndex(int index);
    Q_INVOKABLE void setCurrentItem( const QGraphicsWidget *widget );

    QGraphicsWidget *widgetAt(int index) const;
    QGraphicsWidget *widgetAtByName( const QString& objectName ) const;
    int widgetIndex( const QGraphicsWidget* widget );

	int count() const;

	EffectType effectType() const;
	void setEffectType(EffectType effect);

    void setChildWidgetSizeMode( HGStackedWidget::ChildWidgetSizeMode mode );

protected slots:
	void onAnimationStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
	void onAnimationFinished();

	virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
	virtual void construct();

private:
	void _resetLayout();
};

#endif //HGSTACKEDWIDGET_H
