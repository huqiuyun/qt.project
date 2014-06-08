#ifndef HGSCROLLAREA_P_H
#define HGSCROLLAREA_P_H

#include "hbase.h"
#include "hgscrollarea.h"
#include "hgwidget_p.h"

class HGScrollBar;
class H_API HGScrollAreaPrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGScrollAreaPrivate)
    Q_DECLARE_PUBLIC(HGScrollArea)

public:
    HGScrollAreaPrivate();

protected:
    void onInitStyle(const HStyle * style);

    QGraphicsWidget* mViewport;
    HGScrollBar* mHorizontalScrollBar;
    HGScrollBar* mVerticalScrollBar;
    Qt::ScrollBarPolicy mVerticalScrollBarPolicy;
    Qt::ScrollBarPolicy mHorizontalScrollBarPolicy;
    qreal mPrevHorizontalValue;
    qreal mPrevVerticalValue;
};

#endif // HGSCROLLAREA_P_H
