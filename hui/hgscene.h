#ifndef HGSCENE_H
#define HGSCENE_H

#include "hbase.h"
#include <QGraphicsScene>

class H_API HGScene : public QGraphicsScene , public HObject
{
    Q_OBJECT
public:
    explicit HGScene(QObject *parent = 0);
    explicit HGScene(const QRectF &sceneRect, QObject *parent = 0);
    explicit HGScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);

};

#endif // HGSCENE_H
