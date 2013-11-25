#ifndef HPROXYPROXY_H
#define HPROXYPROXY_H

#include "hconfig.h"
#include <QObject>

class QGraphicsWidget;
class QWidget;
class QGraphicsItem;

class H_API IHProxyHandler
{
public:
    virtual bool handler(void* obj , int type, const char* id, const QVariant& val) = 0;
};

class H_API HPropertyProxy
{
public:
    explicit HPropertyProxy();

    virtual bool handlerQWidget(QWidget* obj, int objType/* @see HEnums::HObjectType*/,const char* id, const QVariant& val);
    virtual bool handlerGWidget(QGraphicsWidget* obj,int objType, const char* id, const QVariant& val);
    virtual bool handlerGItem(QGraphicsItem* obj,int objType, const char* id, const QVariant& val);
};

#endif // HPROXYPROXY_H
