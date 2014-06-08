#include "hgitemview.h"
#include "private/hgitemview_p.h"
#include <QStandardItemModel>

IMPLEMENT_GITEM_STATIC_CREATE(HGItemView,HGItemView)
HGItemView::HGItemView(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGScrollArea(*(new HGItemViewPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGItemView);
}

HGItemView::HGItemView(HGItemViewPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent)
    :HGScrollArea(dd,objinfo,parent)
{
    mObjType = USEOBJTYPE(HGItemView);
}

HGItemView::~HGItemView()
{
}

QStandardItemModel *HGItemView::model() const
{
    return d_func()->mModel;
}

void HGItemView::setModel(QStandardItemModel *model)
{
    Q_D(HGItemView);
    if (d->mModel == model)
        return;

    if (d->mModel)
    {
        d->mModel->disconnect(this);
        onModelOldClear();
    }

    d->mModel = model;
    if (model) {
        d->mModel->setParent(this);

        QObject::connect(model,
                         SIGNAL(rowsAboutToBeInserted(const QModelIndex &, int , int )),
                         this,
                         SLOT(onRowsAboutToBeInserted(const QModelIndex &, int , int )));
        QObject::connect(model,
                         SIGNAL(rowsInserted(const QModelIndex &, int , int )),
                         this,
                         SLOT(onRowsInserted(const QModelIndex &, int , int )));
        QObject::connect(model,
                         SIGNAL(rowsAboutToBeRemoved(const QModelIndex &, int , int )),
                         this,
                         SLOT(onRowsAboutToBeRemoved(const QModelIndex &, int , int )));
        QObject::connect(model,
                         SIGNAL(rowsRemoved(const QModelIndex &, int , int )),
                         this,
                         SLOT(onRowsRemoved(const QModelIndex &, int , int )));

        QObject::connect(model,
                         SIGNAL(rowsAboutToBeMoved( const QModelIndex &, int , int , const QModelIndex &, int )),
                         this,
                         SLOT(onRowsAboutToBeMoved( const QModelIndex &, int , int , const QModelIndex &, int )));
        QObject::connect(model,
                         SIGNAL(rowsMoved( const QModelIndex &, int , int , const QModelIndex &, int )),
                         this,
                         SLOT(onRowsMoved( const QModelIndex &, int , int , const QModelIndex &, int )));

        QObject::connect(model,
                         SIGNAL(columnsAboutToBeInserted(const QModelIndex &, int , int )),
                         this,
                         SLOT(onColumnsAboutToBeInserted(const QModelIndex &, int , int )));
        QObject::connect(model,
                         SIGNAL(columnsInserted(const QModelIndex &, int , int )),
                         this,
                         SLOT(onColumnsInserted(const QModelIndex &, int , int )));
        QObject::connect(model,
                         SIGNAL(),
                         this,
                         SLOT(onColumnsAboutToBeRemoved(const QModelIndex &, int , int )));
        QObject::connect(model,
                         SIGNAL(columnsRemoved(const QModelIndex &, int , int )),
                         this,
                         SLOT(onColumnsRemoved(const QModelIndex &, int , int )));

        QObject::connect(model,
                         SIGNAL(columnsAboutToBeMoved( const QModelIndex &, int , int , const QModelIndex &, int )),
                         this,
                         SLOT(onColumnsAboutToBeMoved( const QModelIndex &, int , int , const QModelIndex &, int )));
        QObject::connect(model,
                         SIGNAL(columnsMoved( const QModelIndex &, int , int , const QModelIndex &, int )),
                         this,
                         SLOT(onColumnsMoved( const QModelIndex &, int , int , const QModelIndex &, int )));

        QObject::connect(model,SIGNAL(modelAboutToBeReset()),this,SLOT(onModelAboutToBeReset()));
        QObject::connect(model,SIGNAL(modelReset()),this,SLOT(onModelReset()));

        QObject::connect(model,
                         SIGNAL(itemChanged(QStandardItem *)),
                         this,
                         SLOT(onItemChanged(QStandardItem *)));
    }
    onModelNewReset();
}

void HGItemView::onModelNewReset()
{
}

void HGItemView::onModelOldClear()
{
}

void HGItemView::onRowsAboutToBeInserted(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onRowsRemoved(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onRowsAboutToBeMoved( const QModelIndex &sourceParent,
                                       int sourceStart, int sourceEnd,
                                       const QModelIndex &destinationParent, int destinationRow)
{
    H_UNUSED3(sourceParent,sourceStart,sourceEnd);
    H_UNUSED2(destinationParent,destinationRow);
}

void HGItemView::onRowsMoved( const QModelIndex &parent, int start, int end,
                              const QModelIndex &destination, int row)
{
    H_UNUSED3(parent,start,end);
    H_UNUSED2(destination,row);
}

void HGItemView::onColumnsAboutToBeInserted(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onColumnsInserted(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onColumnsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onColumnsRemoved(const QModelIndex &parent, int first, int last)
{
    H_UNUSED3(parent,first,last);
}

void HGItemView::onColumnsAboutToBeMoved( const QModelIndex &sourceParent,
                                          int sourceStart, int sourceEnd,
                                          const QModelIndex &destinationParent,
                                          int destinationColumn)
{
    H_UNUSED3(sourceParent,sourceStart,sourceEnd);
    H_UNUSED2(destinationParent,destinationColumn);
}

void HGItemView::onColumnsMoved( const QModelIndex &parent,
                                 int start, int end,
                                 const QModelIndex &destination, int column)
{
    H_UNUSED3(parent,start,end);
    H_UNUSED2(destination,column);
}

void HGItemView::onModelAboutToBeReset()
{
}

void HGItemView::onModelReset()
{
}

void HGItemView::onItemChanged(QStandardItem *item)
{
    Q_UNUSED(item);
}
