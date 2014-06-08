#ifndef HGLAYOUT_H
#define HGLAYOUT_H

#include "hlayout.h"
#include "hlayoutconfig.h"
#include <QPointer>

class HGWidget;
class QWidget;
class QGraphicsLayoutItem;
class QGraphicsWidget;
class QGraphicsLayout;

class H_API HGLayout : public HLayout
{
public:
    explicit HGLayout(QObject *parent = 0);
    ~HGLayout();

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
    virtual int  insertItem(QGraphicsLayoutItem* item, const HLayoutConfig& conf);
    virtual bool removeItem(QGraphicsLayoutItem* item);

    virtual int  addGWidget(QGraphicsWidget* item);
    virtual int  insertGWidget(QGraphicsWidget* item, const HLayoutConfig& conf);
    virtual bool removeGWidget(QGraphicsWidget* item);

    virtual bool addChildGWidget(QGraphicsWidget* widget ,const HLayoutConfig& conf);
    virtual void removeChildGWidget(QGraphicsWidget* widget);

    virtual void resizeEvent(const QSize& );
protected:
    HItemWidgets<QGraphicsWidget> mChilds;
    HGWidget* mWidget;
};

#endif // HGLAYOUT_H
