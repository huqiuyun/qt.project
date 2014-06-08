#ifndef HGCAPTION_H
#define HGCAPTION_H

#include "hgwidget.h"

class HGCaptionPrivate;
class H_API HGCaption : public HGWidget
{
    Q_OBJECT
    Q_DISABLE_COPY( HGCaption )
    Q_DECLARE_PRIVATE( HGCaption )
public:
    explicit HGCaption(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGCaption();

    DECLARE_GITEM_STATIC_CREATE(HGCaption);
};


#endif // HGCAPTION_H
