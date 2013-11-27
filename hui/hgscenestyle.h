#ifndef HGSCENESTYLE_H
#define HGSCENESTYLE_H

#include "hbasestyle.h"
#include <QSizePolicy>
#include <QBrush>

class QGraphicsView;
class QGraphicsItem;
class HGScene;
class HGWidget;

class HGSceneStylePrivate;
class H_API HGSceneStyle : public HBaseStyle
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HGSceneStyle )

    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush )
    Q_PROPERTY( QBrush foregroundBrush READ foregroundBrush WRITE setForegroundBrush )
    Q_PROPERTY( QSizePolicy::Policy sizePolicy READ sizePolicy WRITE setSizePolicy )
public:
    explicit HGSceneStyle(QObject *parent = 0);
    explicit HGSceneStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    ~HGSceneStyle();

    DECLARE_OBJECT_STATIC_CREATE(HGSceneStyle);
public:
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

    bool addGWidget(HGWidget* widget,const HLayoutConf& conf);
    void removeGWidget(HGWidget* widget);

    bool addItem(QGraphicsItem* item,const HLayoutConf& conf);
    void removeItem(QGraphicsItem* item);

public:
    void copyTo(HBaseStyle* obj);
    HBaseStyle* clone();

    void setGView(QGraphicsView* view);
    void reSize(const QRectF& rect);

protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    void doConstruct();
private:
    HGSceneStylePrivate* d_ptr;
};

#endif // HGSCENESTYLE_H
