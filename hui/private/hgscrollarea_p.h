#ifndef HGITEMVIEW_P_H
#define HGITEMVIEW_P_H

#include "hbase.h"
#include "hgitemview.h"
#include "hgwidget_p.h"

class QStandardItemModel;

class H_API HGItemViewPrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGItemViewPrivate)
    Q_DECLARE_PUBLIC( HGItemView )
public:
    HGItemViewPrivate():
        HGWidgetPrivate(),
        mItemModel(NULL)
    {
    }

    ~HGItemViewPrivate()
    {
    }
protected:
    QStandardItemModel* mItemModel;
};

#endif // HGITEMVIEW_P_H
