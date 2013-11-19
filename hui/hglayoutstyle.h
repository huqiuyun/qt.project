#ifndef HGLAYOUTSTYLE_H
#define HGLAYOUTSTYLE_H

#include "hlayoutstyle.h"

class HGWidget;
class QWidget;
class QGraphicsLayoutItem;

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

    /** set alignment in parent layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    void setAnchor(const HAnchor& a);

    /** set per child item space in owner layout */
    int spacing() const;
    void setSpacing(int s);

    /** add item to owner layout */
    bool addItem(QGraphicsLayoutItem* item);
    bool insertItem(QGraphicsLayoutItem* item, const HLayoutIndex& layIndex);
    bool removeItem(QGraphicsLayoutItem* item);

    /** add widget to owner layout */
    bool addItem(QWidget* widget);
    bool insertItem(QWidget* widget ,const HLayoutIndex& layIndex);
    bool removeItem(QWidget* widget);

    virtual HBaseStyle* clone();
protected:
    HGWidget* mWidget;
};

#endif // HGLAYOUTSTYLE_H
