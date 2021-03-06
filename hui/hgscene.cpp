#include "hgscene.h"

HGScene::HGScene(QObject *parent) :
    QGraphicsScene(parent)
{
    //qDebug("HGScene::HGScene");
    mObjType = USEOBJTYPE(HGScene);
}

HGScene::HGScene(const QRectF &sceneRect, QObject *parent) :
    QGraphicsScene(sceneRect,parent)
{
    //qDebug("HGScene::HGScene");
    mObjType = USEOBJTYPE(HGScene);
}

HGScene::HGScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
        QGraphicsScene(x,y,width,height,parent)
{
    mObjType = USEOBJTYPE(HGScene);
}
