#ifndef IHFACTORY_H
#define IHFACTORY_H

#include "hbase.h"
#include "hunknown.h"
#include <QLatin1String>

class HGWidget;
class HObjectInfo;
class HClassInfo;
class QWidget;
class QGraphicsItem;
class QObject;

typedef HUnknown*          (*HCreateUnknownInstanceCB)(IHUnknown* pUnkOuter, long *hr);
typedef HGWidget*          (*HCreateGWidgetInstanceCB)(const HObjectInfo& objinfo,QGraphicsItem* parent, const HCreateParameter& param, long *hr);
typedef QWidget*           (*HCreateQWidgetInstanceCB)(const HObjectInfo& objinfo,QWidget* parent, const HCreateParameter& param, long *hr);
typedef QObject*           (*HCreateObjectInstanceCB)(const HObjectInfo& objinfo,QObject* parent, const HCreateParameter& param, long *hr);

struct HRegisterUnknown
{
    const HGuid*  clsrid;
    HCreateUnknownInstanceCB  fnCreate;
};

struct HRegisterGWidget
{
    const char* clsname;
    HCreateGWidgetInstanceCB   fnCreate;
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
    /**
     * @brief 创建实例
     *
     * @param rclsid @see hguid.h
     *
     * @param pUnkOuter 父接口
     * @param riid 请参考 hguid.h
     * @param [out]ppv 返回创建的实例对象
    */
    virtual long createInstance(IHUnknown* pUnkOuter , const HGuid& riid , void** ppv) = 0;

    //
    virtual long coRegisterGWidget(const HRegisterGWidget* com) = 0;
    virtual long coUnRegisterGWidget(const char* clsname) = 0;
    virtual HGWidget* createGWidget(const HClassInfo& clsinfo, QGraphicsItem* parent, const HCreateParameter& param,long *hr) = 0;

    //
    virtual long coRegisterQWidget(const HRegisterQWidget* com) = 0;
    virtual long coUnRegisterQWidget(const char* clsname) = 0;
    virtual QWidget* createQWidget(const HClassInfo& clsinfo, QWidget* parent, const HCreateParameter& param,long *hr) = 0;

    //
    virtual long coRegisterObject(const HRegisterObject* com) = 0;
    virtual long coUnRegisterObject(const char* clsname) = 0;
    virtual QObject* createObject(const HClassInfo& clsinfo, QObject* parent, const HCreateParameter& param,long *hr) = 0;
};

#endif /* HIFACTORY_H */
