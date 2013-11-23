#ifndef IHFACTORY_H
#define IHFACTORY_H

#include "hbase.h"
#include "hunknown.h"
#include <QString>
#include <QVariant>

class HGWidget;
class QWidget;
class QGraphicsItem;
class QObject;
class QGraphicsWidget;

typedef HUnknown*          (*HCreateUnknownInstanceCB)(IHUnknown* pUnkOuter, long *hr);
typedef QGraphicsItem*     (*HCreateGItemInstanceCB)(const HObjectInfo& objinfo, QGraphicsItem* parent,  HCreateParam& param/*in/out*/);
typedef HGWidget*          (*HCreateGWidgetInstanceCB)(const HObjectInfo& objinfo, QGraphicsItem* parent,  HCreateParam& param/*in/out*/);
typedef QWidget*           (*HCreateQWidgetInstanceCB)(const HObjectInfo& objinfo,QWidget* parent, HCreateParam& param);
typedef QObject*           (*HCreateObjectInstanceCB)(const HObjectInfo& objinfo, QObject* parent, HCreateParam& param);
typedef QVariant           (*HConvertString2QvariantCB)(const QString&, long *hr);
typedef QString            (*HConvertQvariant2StringCB)(const QVariant&, long *hr);

struct HRegisterUnknown
{
    const HGuid*  clsrid;
    HCreateUnknownInstanceCB  fnCreate;
};

//based QGraphicsItem
struct HRegisterGItem
{
    const char* clsname;
    HCreateGItemInstanceCB   fnCreate;
};

//based QGraphicsWidget
struct HRegisterGWidget
{
    const char* clsname;
    HCreateGWidgetInstanceCB fnCreate;
};

//based QWidget(HGView,HQWidget,QPushButton...)
struct HRegisterQWidget
{
    const char* clsname;
    HCreateQWidgetInstanceCB  fnCreate;
};

//based QObject
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
    virtual bool isGItem(const char* clsname) = 0;
    virtual long coRegisterGItem(const HRegisterGItem* com) = 0;
    virtual long coUnRegisterGItem(const char* clsname) = 0;
    virtual QGraphicsItem* createGItem(const HClassInfo& clsinfo, QGraphicsItem* parent, HCreateParam& param) = 0;
    //
    virtual bool isGWidget(const char* clsname) = 0;
    virtual long coRegisterGWidget(const HRegisterGWidget* com) = 0;
    virtual long coUnRegisterGWidget(const char* clsname) = 0;
    virtual HGWidget* createGWidget(const HClassInfo& clsinfo, QGraphicsItem* parent, HCreateParam& param) = 0;
    //
    virtual bool isQWidget(const char* clsname) = 0;
    virtual long coRegisterQWidget(const HRegisterQWidget* com) = 0;
    virtual long coUnRegisterQWidget(const char* clsname) = 0;
    virtual QWidget* createQWidget(const HClassInfo& clsinfo, QWidget* parent, HCreateParam& param) = 0;
    //
    virtual bool isObject(const char* clsname) = 0;
    virtual long coRegisterObject(const HRegisterObject* com) = 0;
    virtual long coUnRegisterObject(const char* clsname) = 0;
    virtual QObject* createObject(const HClassInfo& clsinfo, QObject* parent, HCreateParam& param) = 0;
    //
    virtual bool isConvert(CONVERT_ID_PTR id) = 0;
    virtual long coRegisterConvert(const HRegisterConvert* com) = 0;
    virtual long coUnRegisterConvert(CONVERT_ID_PTR id) = 0;
    virtual QVariant convertString(CONVERT_ID_PTR id,const QString& var,long *hr) = 0;
    virtual QString  convertQVariant(CONVERT_ID_PTR id,const QVariant& var,long *hr) = 0;
};

#endif /* HIFACTORY_H */
