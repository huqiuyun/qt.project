#ifndef HGSCENEITEM_H
#define HGSCENEITEM_H

#include "hbase.h"
#include <QSizePolicy>
#include <QBrush>

class QGraphicsView;
class QGraphicsItem;
class HGScene;
class HGWidget;
class HLayoutConfig;

class HGSceneItemPrivate;
class H_API HGSceneItem : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HGSceneItem )

    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush )
    Q_PROPERTY( QBrush foregroundBrush READ foregroundBrush WRITE setForegroundBrush )
    Q_PROPERTY( QSizePolicy::Policy sizePolicy READ sizePolicy WRITE setSizePolicy )
public:
    explicit HGSceneItem(QObject *parent = 0);
    ~HGSceneItem();

public:
    void setGView(QGraphicsView* view);

    /** set alignment in scene*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    QSizePolicy::Policy sizePolicy() const;
    void setSizePolicy(QSizePolicy::Policy policy);

    bool hasBackgroundBrush() const;
    QBrush backgroundBrush() const;
    void setBackgroundBrush(const QBrush& brush);

    bool hasForegroundBrush() const;
    QBrush foregroundBrush() const;
    void setForegroundBrush(const QBrush& brush);

    bool hasScene() const;
    HGScene* scene() const;

    bool addGWidget(HGWidget* widget,const HLayoutConfig& conf);
    void removeGWidget(HGWidget* widget);
    HGWidget* widgetAt(int index);
    HGWidget* widgetOf(const QString& name);

    bool addItem(QGraphicsItem* item,const HLayoutConfig& conf);
    void removeItem(QGraphicsItem* item);

    void reSize(const QRectF& rect);
private:
    HGSceneItemPrivate* d_ptr;
};

#endif // HGSCENEITEM_H
