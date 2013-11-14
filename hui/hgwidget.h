#ifndef HGWidget_H
#define HGWidget_H

#include "hbase.h"
#include <QMargins>
#include <QGraphicsWidget>

class QWidget;
class HGWidgetPrivate;
class HBackgroundItem;
class HCssWidget;
class HCssObject;

class H_API HGWidget : public QGraphicsWidget, public HObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HGWidget)
    Q_DECLARE_PRIVATE(HGWidget)
public:
    explicit HGWidget(QGraphicsItem* parent = NULL);
    explicit HGWidget(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGWidget();

    DECLARE_GITEM_STATIC_CREATE(HGWidget);
public:
    /** for css */
    bool setCss(QSharedPointer<HCssObject> obj);

    void setStyleId(const QLatin1String& id);
    QLatin1String styleId() const;

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

    void setDragPolicy(qy::HDragFlag flag );
    qy::HDragFlag dragPolicy() const;

    void setBackgroundItem(QSharedPointer<HBackgroundItem> background);
    QSharedPointer<HBackgroundItem> backgroundItem() const;

    // next layout functions
    qy::HLayoutType layoutType() const;
    void setLayout(qy::HLayoutType type);

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set alignment in parent layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    HAnchor anchor() const;
    void setAnchor(const HAnchor& a);

    /** set per child item space in owner layout */
    void setSpacing(int s);

    /** add item to owner layout */
    bool addItem(QGraphicsLayoutItem* item);
    bool insertItem(QGraphicsLayoutItem* item, const HLayoutIndex& layIndex);
    bool removeItem(QGraphicsLayoutItem* item);

    /** add widget to owner layout */
    bool addWidget(QWidget* widget);
    bool insertWidget(QWidget* widget ,const HLayoutIndex& layIndex);
    bool removeWidget(QWidget* widget);
    // end layout functions
protected:
    HCssWidget* css()  const;

protected:
    void doConstruct();
    virtual void construct(){}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private slots:
    void on_cssStyle_changed(const QString&id);

protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    HGWidget(HGWidgetPrivate& dd,QGraphicsItem* parent);
    HGWidget(HGWidgetPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent);
    HGWidgetPrivate* d_ptr;
};

#endif // HGWidget_H
