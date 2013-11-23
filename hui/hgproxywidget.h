#ifndef HGPROXYWIDGET_H
#define HGPROXYWIDGET_H

#include "hbase.h"
#include <QGraphicsProxyWidget>

class H_API HGProxyWidget : public QGraphicsProxyWidget, public HObject
{
    Q_OBJECT
public:
    DECLARE_GITEM_STATIC_CREATE(HGProxyWidget);
    explicit HGProxyWidget(QGraphicsItem* parent = NULL);
    explicit HGProxyWidget(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
};

#endif // HGPROXYWIDGET_H
