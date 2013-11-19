#ifndef HGWIDGET_H
#define HGWIDGET_H

#include "hbase.h"
#include "henums.h"
#include <QMargins>
#include <QGraphicsWidget>

class HGWidgetPrivate;
class HBackgroundStyle;
class HGLayoutStyle;
class HGWidgetStyle;

class H_API HGWidget : public QGraphicsWidget, public HObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HGWidget)
    Q_DECLARE_PRIVATE(HGWidget)
    Q_PROPERTY( int height READ height WRITE setHeight )
    Q_PROPERTY( int width READ width WRITE setWidth )
    Q_PROPERTY( QSizeF fixSize READ fixSize WRITE setFixSize )
    Q_PROPERTY( int fixHeight READ fixHeight WRITE setFixHeight )
    Q_PROPERTY( int fixWidth READ fixWidth WRITE setFixWidth )

public:
    explicit HGWidget(QGraphicsItem* parent = NULL);
    explicit HGWidget(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGWidget();

    DECLARE_GITEM_STATIC_CREATE(HGWidget);
public:
    void setGWidgetStyle(QSharedPointer<HGWidgetStyle> style);
    QSharedPointer<HGWidgetStyle> gwidgetStyle() const;

    void setBackgroundStyle(QSharedPointer<HBackgroundStyle> style);
    QSharedPointer<HBackgroundStyle> backgroundStyle() const;

    void setLayoutStyle(QSharedPointer<HGLayoutStyle> style);
    QSharedPointer<HGLayoutStyle> layoutStyle() const;

    HEnums::HLayoutType layoutType() const;
    // property
public:
    int height() const;
    void setHeight(int h);

    int width() const;
    void setWidth(int w);

    void setFixSize(const QSizeF &s);
    QSizeF fixSize() const;

    void setFixHeight(int h);
    int fixHeight() const;

    int fixWidth() const;
    void setFixWidth(int w);

protected:
    void doConstruct();
    virtual void construct(){}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    HGWidget(HGWidgetPrivate& dd,QGraphicsItem* parent);
    HGWidget(HGWidgetPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent);
    HGWidgetPrivate* d_ptr;
};

#endif // HGWIDGET_H
