#ifndef HGTREE_H
#define HGTREE_H

#include "hgwidget.h"

class HGTreePrivate;
class H_API HGTree : public HGWidget
{
    Q_OBJECT
    Q_DISABLE_COPY( HGTree )
    Q_DECLARE_PRIVATE( HGTree )
public:
    explicit HGTree(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGTree();

    DECLARE_GITEM_STATIC_CREATE(HGTree);
};

#endif // HGTREE_H
