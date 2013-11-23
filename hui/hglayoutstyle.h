#ifndef HGLAYOUTSTYLE_H
#define HGLAYOUTSTYLE_H

#include "hlayoutstyle.h"

class HGWidget;
class QWidget;
class QGraphicsLayoutItem;
class QGraphicsWidget;
class QGraphicsLayout;

class H_API HGLayoutStyle : public HLayoutStyle
{
public:
    explicit HGLayoutStyle(QObject *parent = 0);
    explicit HGLayoutStyle(const HObjectInfo& objinfo, QObject *parent = 0);

    DECLARE_OBJECT_STATIC_CREATE(HGLayoutStyle);
public:
    void setWidget(HGWidget* widget);
    QGraphicsLayout* layout() const;

    void setLayoutType(HEnums::HLayoutType type);

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set alignment all child item in layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    /** set per child item space in owner layout */
    int spacing() const;
    void setSpacing(int s);

    void setAlignment(QGraphicsLayoutItem* item, Qt::Alignment align);
    Qt::Alignment alignment(QGraphicsLayoutItem* item) const;

    /** add item to owner layout */
    virtual int  addItem(QGraphicsLayoutItem* item);
    virtual int  insertItem(QGraphicsLayoutItem* item, const HLayoutIndex& index);
    virtual bool removeItem(QGraphicsLayoutItem* item);

    virtual int  addGWidget(QGraphicsWidget* item);
    virtual int  insertGWidget(QGraphicsWidget* item, const HLayoutIndex& index);
    virtual bool removeGWidget(QGraphicsWidget* item);

    virtual HBaseStyle* clone();
protected:
    HGWidget* mWidget;
};

#endif // HGLAYOUTSTYLE_H
