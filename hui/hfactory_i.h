#ifndef IHFACTORY_H
#define IHFACTORY_H

#include "hbase.h"
#include "hunknown.h"
#include <QString>
#include <QVariant>

class QWidget;
class QGraphicsItem;
class QObject;

typedef HUnknown*          (*HCreateUnknownInstanceCB)(IHUnknown* pUnkOuter, long *hr);
typedef void*              (*HCreateGItemInstanceCB)(const HObjectInfo& objinfo,QGraphicsItem* parent, const HCreateParameter& param, long *hr);
typedef QWidget*           (*HCreateQWidgetInstanceCB)(const HObjectInfo& objinfo,QWidget* parent, const HCreateParameter& param, long *hr);
typedef QObject*           (*HCreateObjectInstanceCB)(const HObjectInfo& objinfo,QObject* parent, const HCreateParameter& param, long *hr);
typedef QVariant           (*HConvertString2QvariantCB)(const QString&, long *hr);
typedef QString            (*HConvertQvariant2StringCB)(const QVariant&, long *hr);

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

typedef int CONVERT_ID_PTR;
typedef int CONVERT_ID;

struct HRegisterConvert
{
    CONVERT_ID_PTR id;
    HConvertString2QvariantCB fnString2Qvar;
    HConvertQvariant2StringCB fnQvar2String;
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
    //
    virtual bool isConvert(CONVERT_ID_PTR id) = 0;
    virtual long coRegisterConvert(const HRegisterConvert* com) = 0;
    virtual long coUnRegisterConvert(CONVERT_ID_PTR id) = 0;
    virtual QVariant convertString(CONVERT_ID_PTR id,const QString& var,long *hr) = 0;
    virtual QString  convertQVariant(CONVERT_ID_PTR id,const QVariant& var,long *hr) = 0;
};

#endif /* HIFACTORY_H */
