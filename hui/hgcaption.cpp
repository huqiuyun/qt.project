#include "hgcaption.h"
#include "private/hgwidget_p.h"

class HGCaptionPrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGCaptionPrivate)
    Q_DECLARE_PUBLIC( HGCaption )
public:
    HGCaptionPrivate():
        HGWidgetPrivate()
    {
    }
    ~HGCaptionPrivate()
    {
    }
};

IMPLEMENT_GITEM_STATIC_CREATE(HGCaption,HGCaption)
HGCaption::HGCaption(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGCaptionPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGCaption);
    setAcceptHoverEvents(true);
    openGItemFlag(ItemClipsChildrenToShape);
}

HGCaption::~HGCaption()
{
}
