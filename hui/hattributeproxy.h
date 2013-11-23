#ifndef HATTRIBUTEPROXY_H
#define HATTRIBUTEPROXY_H

#include "hconfig.h"
#include <QObject>

class H_API HAttributeProxy : public QObject
{
public:
    enum ProxyType
    {
        ProxyUnk = 0, // not based QObject : QGraphicsItem...
        ProxyQObject,
        ProxyEnd
    };
    Q_ENUMS(ProxyType)

public:
    explicit HAttributeProxy(QObject *parent = 0);

    /**
      * @param proxyType @see enum ProxyType , use can defined
    */
    virtual bool set(int proxyType, const char* id, const QVariant& val, void* obj, int type/* @see HEnums::HObjectType*/) = 0;
};

#endif // HATTRIBUTEPROXY_H
