#ifndef HGITEMVIEW_H
#define HGITEMVIEW_H

#include "hgscrollarea.h"

class QStandardItemModel;
class QStandardItem;
class QModelIndex;
class HGItemViewPrivate;

class H_API HGItemView : public HGScrollArea
{
    Q_OBJECT
    Q_DISABLE_COPY( HGItemView )
    Q_DECLARE_PRIVATE( HGItemView )
public:
    explicit HGItemView(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGItemView();

    DECLARE_GITEM_STATIC_CREATE(HGItemView);
public:
    QStandardItemModel *model() const;
    void setModel(QStandardItemModel *model);

protected slots:
    virtual void onModelNewReset();
    virtual void onModelOldClear();
    //
    virtual void onRowsAboutToBeInserted(const QModelIndex &parent, int first, int last);
    virtual void onRowsInserted(const QModelIndex &parent, int first, int last);
    virtual void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    virtual void onRowsRemoved(const QModelIndex &parent, int first, int last);

    virtual void onRowsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationRow);
    virtual void onRowsMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
    //
    virtual void onColumnsAboutToBeInserted(const QModelIndex &parent, int first, int last);
    virtual void onColumnsInserted(const QModelIndex &parent, int first, int last);
    virtual void onColumnsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    virtual void onColumnsRemoved(const QModelIndex &parent, int first, int last);

    virtual void onColumnsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationColumn);
    virtual void onColumnsMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int column);

    //
    virtual void onModelAboutToBeReset();
    virtual void onModelReset();

    virtual void onItemChanged(QStandardItem *item);
protected:
    HGItemView(HGItemViewPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent);
};

#endif // HGITEMVIEW_H
