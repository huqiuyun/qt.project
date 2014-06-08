#include "hgsplitter.h"
#include "private/hgwidget_p.h"

class HGSplitterPrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGSplitterPrivate)
    Q_DECLARE_PUBLIC( HGSplitter )
public:
    HGSplitterPrivate():
        HGWidgetPrivate()
    {
    }
    ~HGSplitterPrivate()
    {
    }
};

IMPLEMENT_GITEM_STATIC_CREATE(HGSplitter,HGSplitter)
HGSplitter::HGSplitter(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGSplitterPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGSplitter);
    setAcceptHoverEvents(true);
    openGItemFlag(ItemClipsChildrenToShape);
}

HGSplitter::~HGSplitter()
{
}
