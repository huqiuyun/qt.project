#ifndef HLayoutConfig_H
#define HLayoutConfig_H

#include "hbase.h"

class HStyle;
class HLayoutConfigPrivate;
class H_API HLayoutConfig : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QMargins margins READ margins WRITE setMargins )
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( int index READ index WRITE setIndex )
    Q_PROPERTY( int row READ row WRITE setRow )
    Q_PROPERTY( int column READ column WRITE setColumn )
    Q_PROPERTY( int stretch READ stretch WRITE setStretch )

public:
    explicit HLayoutConfig(QObject *parent = 0);
    explicit HLayoutConfig(int index, QObject *parent = 0);
    explicit HLayoutConfig(int row,int col,QObject *parent = 0);
    ~HLayoutConfig();

    void setStyle(const HStyle* style);
    const HStyle* style() const;
    // property
public:
    int index() const;
    void setIndex(int idx);

    int row() const;
    void setRow(int row);

    int column() const;
    void setColumn(int col);

    int stretch() const;
    void setStretch(int s);

    QMargins margins() const;
    void setMargins(const QMargins& m);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align) ;

public:
    Q_INVOKABLE HClassInfo proxyWidget() const;
    /**
      * name = "proxyWidget"
    */
    Q_INVOKABLE void addChild(const QString& name,const HClassInfo& info);
private:
    HLayoutConfigPrivate* d_ptr;
};

#endif // HLayoutConfig_H
