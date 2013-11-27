#include "hgproxywidget.h"

IMPLEMENT_GITEM_STATIC_CREATE(HGProxyWidget,HGProxyWidget)
HGProxyWidget::HGProxyWidget(QGraphicsItem* parent) :
    QGraphicsProxyWidget(parent)
{
    mObjType = USEOBJTYPE(HGProxyWidget);
}

HGProxyWidget::HGProxyWidget(const HObjectInfo& objinfo,QGraphicsItem* parent):
    QGraphicsProxyWidget(parent),HObject(objinfo.mStyleId)
{
    mObjType = USEOBJTYPE(HGProxyWidget);
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.objName());
}
/*
 void HGProxyWidget::paintWindowFrame(QPainter *painter,
                                      const QStyleOptionGraphicsItem *option,QWidget *widget)
 {
     Q_UNUSED(painter);
     Q_UNUSED(option);
     Q_UNUSED(widget);
 }*/
