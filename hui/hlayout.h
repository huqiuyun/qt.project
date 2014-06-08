#ifndef HLAYOUT_H
#define HLAYOUT_H

#include "hbase.h"
#include "henums.h"

class H_API HLayout : public QObject
{
    Q_OBJECT

    Q_PROPERTY( HEnums::HLayoutType layoutType READ layoutType WRITE setLayoutType )
    Q_PROPERTY( QMargins margins READ margins WRITE setMargins )
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( int spacing READ spacing WRITE setSpacing )

public:
    explicit HLayout(QObject *parent = 0);

public:
    HEnums::HLayoutType layoutType() const;
    virtual void setLayoutType(HEnums::HLayoutType type);

    /** set margins for all child item in layout */
    virtual void setMargins(const QMargins& m);
    virtual QMargins margins() const;

    /** set alignment in parent layout*/
    virtual Qt::Alignment alignment() const;
    virtual void setAlignment(Qt::Alignment align);

    /** set per child item space in owner layout */
    virtual void setSpacing(int s);
    virtual int spacing() const;

    virtual void resizeEvent(const QSize& ){}
protected:
    HEnums::HLayoutType mLayoutType;
    QMargins      mMargins;
    Qt::Alignment mAlignment;
    int           mSpacing;
};

#endif // HLAYOUT_H
