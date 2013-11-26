#ifndef HGPROXYWIDGET_H
#define HGPROXYWIDGET_H

#include "hbase.h"
#include <QGraphicsProxyWidget>

class H_API HGProxyWidget : public QGraphicsProxyWidget, public HObject
{
    Q_OBJECT
    Q_PROPERTY( bool isHGProxyWidget READ isHGProxyWidget)
public:
    DECLARE_GITEM_STATIC_CREATE(HGProxyWidget);
    explicit HGProxyWidget(QGraphicsItem* parent = NULL);
    explicit HGProxyWidget(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);

    bool isHGProxyWidget() const { return true; }
protected:
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
};

#endif // HGPROXYWIDGET_H
