#ifndef HBASESTYLE_H
#define HBASESTYLE_H

#include "hbase.h"
#include "henums.h"
#include <QMargins>

class H_API HBaseStyle : public QObject, public HObject
{
public:
    explicit HBaseStyle(QObject* parent= 0);
    explicit HBaseStyle(const HObjectInfo& objinfo,QObject* parent= 0);
    virtual ~HBaseStyle();

public:
    virtual HBaseStyle* clone();
    virtual void copyTo(HBaseStyle* obj);

protected:
    HObjectInfo  mObjinfo;
};
typedef QMap<HString, QSharedPointer<HBaseStyle> > HStyleMap;

#endif // HBASESTYLE_H
