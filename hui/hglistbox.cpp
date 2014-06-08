#include "hglistbox.h"
#include "private/hgitemview_p.h"
#include <QStandardItemModel>

class HGListBoxPrivate : public HGItemViewPrivate
{
    Q_DISABLE_COPY(HGListBoxPrivate)
    Q_DECLARE_PUBLIC( HGListBox )
public:
    HGListBoxPrivate():
        HGItemViewPrivate()
    {
    }

    ~HGListBoxPrivate()
    {
    }
};

IMPLEMENT_GITEM_STATIC_CREATE(HGListBox,HGListBox)
HGListBox::HGListBox(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGItemView(*(new HGListBoxPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGListBox);
    setAcceptHoverEvents(true);
    openGItemFlag(ItemClipsChildrenToShape);
}

HGListBox::~HGListBox()
{
}

