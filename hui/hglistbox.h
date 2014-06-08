#ifndef HGLISTBOX_H
#define HGLISTBOX_H

#include "hgitemview.h"

class HGListBoxPrivate;
class H_API HGListBox : public HGItemView
{
    Q_OBJECT
    Q_DISABLE_COPY( HGListBox )
    Q_DECLARE_PRIVATE( HGListBox )
public:
    explicit HGListBox(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGListBox();

    DECLARE_GITEM_STATIC_CREATE(HGListBox);
public:

};


#endif // HGLISTBOX_H
