#ifndef HGSPLITTER_H
#define HGSPLITTER_H

#include "hgwidget.h"

class HGSplitterPrivate;
class H_API HGSplitter : public HGWidget
{
    Q_OBJECT
    Q_DISABLE_COPY( HGSplitter )
    Q_DECLARE_PRIVATE( HGSplitter )
public:
    explicit HGSplitter(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGSplitter();

    DECLARE_GITEM_STATIC_CREATE(HGSplitter);
};

#endif // HGSPLITTER_H
