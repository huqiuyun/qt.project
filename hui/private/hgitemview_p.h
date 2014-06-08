#ifndef HGITEMVIEW_P_H
#define HGITEMVIEW_P_H

#include "hbase.h"
#include "hgitemview.h"
#include "hgscrollarea_p.h"

class QStandardItemModel;

class H_API HGItemViewPrivate : public HGScrollAreaPrivate
{
    Q_DISABLE_COPY(HGItemViewPrivate)
    Q_DECLARE_PUBLIC( HGItemView )
public:
    HGItemViewPrivate():
        HGScrollAreaPrivate(),
        mModel(NULL)
    {
    }

    ~HGItemViewPrivate()
    {
    }
protected:
    QStandardItemModel* mModel;
};

#endif // HGITEMVIEW_P_H
