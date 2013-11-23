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
class HStyle;
class QGraphicsLayoutItem;
class QWidget;

class H_API HGWidget : public QGraphicsWidget, public HObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HGWidget)
    Q_DECLARE_PRIVATE(HGWidget)

public:
    Q_PROPERTY( int height READ height WRITE setHeight )
    Q_PROPERTY( int width READ width WRITE setWidth )
    Q_PROPERTY( QSizeF fixedSize READ fixedSize WRITE setFixedSize )
    Q_PROPERTY( int fixedHeight READ fixedHeight WRITE setFixedHeight )
    Q_PROPERTY( int fixedWidth READ fixedWidth WRITE setFixedWidth )
    Q_PROPERTY( bool isHGWidget READ isHGWidget)

    Q_PROPERTY( QString imagePath WRITE setImagePath )
    Q_PROPERTY( QColor color WRITE setColor )
    Q_PROPERTY( QBrush backgroundBrush WRITE setBackgroundBrush )
public:
    explicit HGWidget(QGraphicsItem* parent = NULL);
    explicit HGWidget(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGWidget();

    DECLARE_GITEM_STATIC_CREATE(HGWidget);
public:
    Q_INVOKABLE void installStyle(const HStyle* style);
    bool isHGWidget() const { return true; }

    void setWidgetStyle(QSharedPointer<HGWidgetStyle> style);
    QSharedPointer<HGWidgetStyle> widgetStyle() const;

    void setBackgroundStyle(QSharedPointer<HBackgroundStyle> style);
    QSharedPointer<HBackgroundStyle> backgroundStyle() const;

    void setLayoutStyle(QSharedPointer<HGLayoutStyle> style);
    QSharedPointer<HGLayoutStyle> layoutStyle() const;

    HEnums::HLayoutType layoutType() const;

    /** add item to owner layout */
    virtual int  addItem(QGraphicsLayoutItem* item);
    virtual int  insertItem(QGraphicsLayoutItem* item, const HLayoutIndex& index);
    virtual bool removeItem(QGraphicsLayoutItem* item);

    virtual int  addGWidget(QGraphicsWidget* item);
    virtual int  insertGWidget(QGraphicsWidget* item, const HLayoutIndex& index);
    virtual bool removeGWidget(QGraphicsWidget* item);

    /** add widget to owner layout */
    virtual int  addWidget(QWidget* widget);
    virtual int  insertWidget(QWidget* widget ,const HLayoutIndex& index);
    virtual bool removeWidget(QWidget* widget);
    // property
public:
    int height() const;
    void setHeight(int h);

    int width() const;
    void setWidth(int w);

    void setFixedSize(const QSizeF &s);
    QSizeF fixedSize() const;

    void setFixedHeight(int h);
    int fixedHeight() const;

    int fixedWidth() const;
    void setFixedWidth(int w);

    // for write backgroundStyle
    void setImagePath(const QString& path);
    void setColor(const QColor& rgb);
    void setBackgroundBrush(const QBrush& brush);
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
