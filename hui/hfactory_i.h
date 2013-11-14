#ifndef IHFACTORY_H
#define IHFACTORY_H

#include "hbase.h"
#include "hunknown.h"
#include <QLatin1String>

class HObjectInfo;
class HClassInfo;
class QWidget;
class QGraphicsItem;
class QObject;

typedef HUnknown*          (*HCreateUnknownInstanceCB)(IHUnknown* pUnkOuter, long *hr);
typedef void*              (*HCreateGItemInstanceCB)(const HObjectInfo& objinfo,QGraphicsItem* parent, const HCreateParameter& param, long *hr);
typedef QWidget*           (*HCreateQWidgetInstanceCB)(const HObjectInfo& objinfo,QWidget* parent, const HCreateParameter& param, long *hr);
typedef QObject*           (*HCreateObjectInstanceCB)(const HObjectInfo& objinfo,QObject* parent, const HCreateParameter& param, long *hr);

struct HRegisterUnknown
{
    const HGuid*  clsrid;
    HCreateUnknownInstanceCB  fnCreate;
};

struct HRegisterGItem
{
    const char* clsname;
    HCreateGItemInstanceCB   fnCreate;
};

struct HRegisterQWidget
{
    const char* clsname;
    HCreateQWidgetInstanceCB  fnCreate;
};

struct HRegisterObject
{
    const char* clsname;
    HCreateObjectInstanceCB  fnCreate;
};

struct  IHFactory
{
    virtual long coRegisterUnknown(const HRegisterUnknown* com) = 0;
    virtual long coUnRegisterUnknown(const HGuid* guid) = 0;
    virtual long createInstance(IHUnknown* pUnkOuter , const HGuid& riid , void** ppv) = 0;

    //
    virtual bool isGItem(const QLatin1String& clsname) = 0;
    virtual long coRegisterGItem(const HRegisterGItem* com) = 0;
    virtual long coUnRegisterGItem(const QLatin1String& clsname) = 0;
    virtual void* createGItem(const HClassInfo& clsinfo, QGraphicsItem* parent, const HCreateParameter& param,long *hr) = 0;
    //
    virtual bool isQWidget(const QLatin1String& clsname) = 0;
    virtual long coRegisterQWidget(const HRegisterQWidget* com) = 0;
    virtual long coUnRegisterQWidget(const QLatin1String& clsname) = 0;
    virtual QWidget* createQWidget(const HClassInfo& clsinfo, QWidget* parent, const HCreateParameter& param,long *hr) = 0;

    //
    virtual bool isObject(const QLatin1String& clsname) = 0;
    virtual long coRegisterObject(const HRegisterObject* com) = 0;
    virtual long coUnRegisterObject(const QLatin1String& clsname) = 0;
    virtual QObject* createObject(const HClassInfo& clsinfo, QObject* parent, const HCreateParameter& param,long *hr) = 0;
};

#endif /* HIFACTORY_H */
