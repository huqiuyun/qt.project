#ifndef HGPROXYWIDGET_H
#define HGPROXYWIDGET_H

#include "hbase.h"
#include <QGraphicsProxyWidget>

class HStyle;
class HGProxyWidgetPrivate;
class H_API HGProxyWidget : public QGraphicsProxyWidget, public HObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HGProxyWidget)
    Q_DECLARE_PRIVATE(HGProxyWidget)

    Q_PROPERTY( bool isHGProxyWidget READ isHGProxyWidget)
public:
    explicit HGProxyWidget(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGProxyWidget();

    bool isHGProxyWidget() const { return true; }
    void installStyle(const HStyle* style);
protected:
    virtual void construct();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);
protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    HGProxyWidget(HGProxyWidgetPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent);
    HGProxyWidgetPrivate* d_ptr;
};

#endif // HGPROXYWIDGET_H
