#ifndef HBASESTYLE_H
#define HBASESTYLE_H

#include "hbase.h"
#include "henums.h"

class HStyle;
class H_API HBaseStyle : public QObject, public HObject
{
    Q_OBJECT
public:
    explicit HBaseStyle(QObject* parent= 0);
    explicit HBaseStyle(const HObjectInfo& objinfo,QObject* parent= 0);
    virtual ~HBaseStyle();

public:
    Q_INVOKABLE void addChild(const QString& name,const HClassInfo& info);
    Q_INVOKABLE void removeChild(const QString& name);
    HClassInfo childAt(const QString& name);

public:
    void backup(const HStyle* style);
    virtual HBaseStyle* clone();
    virtual void copyTo(HBaseStyle* obj);

signals:
    /** @param type @see HChangeType */
    void typeChanged(int type);

private:
    typedef QMap<QString,HClassInfo> ChildClassMap;
    ChildClassMap mChild;
};
typedef QMap<HString, QSharedPointer<HBaseStyle> > HStyleMap;

#endif // HBASESTYLE_H
