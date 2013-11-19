#ifndef HLAYOUTSTYLE_H
#define HLAYOUTSTYLE_H

#include "hbasestyle.h"
class QGraphicsLayoutItem;
class QWidget;

class H_API HLayoutStyle : public HBaseStyle
{
    Q_OBJECT

    Q_PROPERTY( HEnums::HLayoutType layoutType READ layoutType WRITE setLayoutType )
    Q_PROPERTY( HAnchor anchor READ anchor WRITE setAnchor )
    Q_PROPERTY( QMargins margins READ margins WRITE setMargins )
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( int spacing READ spacing WRITE setSpacing )

public:
    explicit HLayoutStyle(QObject *parent = 0);
    explicit HLayoutStyle(const HObjectInfo& objinfo, QObject *parent = 0);

public:
    HEnums::HLayoutType layoutType() const;
    virtual void setLayoutType(HEnums::HLayoutType type);

    /** set margins for all child item in layout */
    virtual void setMargins(const QMargins& m);
    virtual QMargins margins() const;

    /** set alignment in parent layout*/
    virtual Qt::Alignment alignment() const;
    virtual void setAlignment(Qt::Alignment align);

    virtual HAnchor anchor() const;
    virtual void setAnchor(const HAnchor& a);

    /** set per child item space in owner layout */
    virtual void setSpacing(int s);
    virtual int spacing() const;

    /** add item to owner layout */
    virtual bool addItem(QGraphicsLayoutItem* item) = 0;
    virtual bool insertItem(QGraphicsLayoutItem* item, const HLayoutIndex& layIndex) = 0;
    virtual bool removeItem(QGraphicsLayoutItem* item) = 0;

    /** add widget to owner layout */
    virtual bool addWidget(QWidget* widget) = 0;
    virtual bool insertWidget(QWidget* widget ,const HLayoutIndex& layIndex) = 0;
    virtual bool removeWidget(QWidget* widget) = 0;

    void doConstruct();
protected:
    void copyTo(HBaseStyle* obj);

protected:
    HEnums::HLayoutType mLayoutType;
    QMargins      mMargins;
    Qt::Alignment mAlignment;
    HAnchor       mAnchor;
    int           mSpacing;
};

#endif // HLAYOUTSTYLE_H
