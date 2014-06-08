#include "hgtree.h"
#include "private/hgwidget_p.h"

class HGTreePrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGTreePrivate)
    Q_DECLARE_PUBLIC( HGTree )
public:
    HGTreePrivate():
        HGWidgetPrivate()
    {
    }
    ~HGTreePrivate()
    {
    }
};

IMPLEMENT_GITEM_STATIC_CREATE(HGTree,HGTree)
HGTree::HGTree(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGTreePrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGTree);
    setAcceptHoverEvents(true);
    openGItemFlag(ItemClipsChildrenToShape);
}

HGTree::~HGTree()
{
}
