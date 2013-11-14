#include "hfactory.h"
#include "hgwidget.h"
#include <QMap>

typedef QMap<HGuid,const HRegisterUnknown*> UnkMap;
typedef QMap<QLatin1String,const HRegisterGItem*> GItemMap;
typedef QMap<QLatin1String,const HRegisterQWidget*> QWidgetMap;
typedef QMap<QLatin1String,const HRegisterObject*> ObjectMap;

class HFactoryPrivate
{
public:
    ~HFactoryPrivate()
	{	
        mInit = false;
	}
    bool isInit(void) const { return mInit; }

private:
    friend class HFactory;

    UnkMap mUnks;
    GItemMap mWidgets;
    QWidgetMap mQWidgets;
    ObjectMap mObjects;
    bool   mInit;
};

HFactory::HFactory()
:d_ptr(new HFactoryPrivate())
{
}

HFactory::~HFactory()
{
	coUninitialize();
    delete d_ptr;
}

long HFactory::coInitialize()
{
    H_D(HFactory);
    if (!d->mInit)
	{
        d->mInit = true;
	}
	return 0;
}

long HFactory::coUninitialize()
{
    H_D(HFactory);
	if (!d->isInit())
	{
		return 0;
	}
    d->mQWidgets.clear();
    d->mUnks.clear();
    d->mWidgets.clear();
    d->mObjects.clear();
    d->mInit = false;
	return 0;
}

long HFactory::coRegisterUnknown(const HRegisterUnknown *com)
{
    H_D(HFactory);
    if (!d->isInit())
	{
        return qy::kHNotInit;
	}

    if (!com || !com->clsrid || !com->fnCreate)
    {
        return qy::kHPointer;
    }
    HGuid guid = *com->clsrid;
    UnkMap::iterator iter = d->mUnks.find(guid);
    if (iter != d->mUnks.end())
    {
        return qy::kHExisted;
    }
    d->mUnks.insert(guid,com);
    return qy::kHOk;
}

long HFactory::coUnRegisterUnknown(const HGuid* guid)
{
    H_D(HFactory);
	if (!d->isInit())
	{
        return qy::kHNotInit;
    }

    UnkMap::iterator iter = d->mUnks.find(*guid);
    if (iter != d->mUnks.end())
    {
        d->mUnks.erase(iter);
    }
    return qy::kHOk;
}

long HFactory::createInstance(IHUnknown *pUnk, const HGuid& riid, void **ppv)
{
    H_D(HFactory);
    long hr = qy::kHOk;
	if (!d->isInit())
	{
        return qy::kHNotInit;
	}
    UnkMap::iterator iter = d->mUnks.find(riid);
    if (iter == d->mUnks.end())
    {
        *ppv = 0;
        return qy::kHNoInterface;
    }
    const HRegisterUnknown* unk = iter.value();
    if (!unk || !unk->fnCreate)
    {
        *ppv = 0;
        return qy::kHNoInterface;
    }

    HUnknown *obj = unk->fnCreate(pUnk, &hr);
    if (!obj)
    {
        *ppv = 0;
        return qy::kHFailure;
    }
    obj->NonDelegatingAddRef();
    hr = obj->NonDelegatingQueryInterface(riid, ppv);
    obj->NonDelegatingRelease();
    return hr;
}

//
bool HFactory::isGItem(const QLatin1String& clsname)
{
    H_D(HFactory);
    GItemMap::iterator iter = d->mWidgets.find(clsname);
    if (iter != d->mWidgets.end())
    {
        return true;
    }
    return false;
}

long HFactory::coRegisterGItem(const HRegisterGItem* com)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        return qy::kHNotInit;
    }

    if (!com || !com->clsname || !com->fnCreate)
    {
        return qy::kHPointer;
    }
    QLatin1String id = QLatin1String(com->clsname);
    if (isGItem(id))
    {
        return qy::kHExisted;
    }
    d->mWidgets.insert(id,com);
    return qy::kHOk;
}

long HFactory::coUnRegisterGItem(const QLatin1String& clsname)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        return qy::kHNotInit;
    }
    GItemMap::iterator iter = d->mWidgets.find(clsname);
    if (iter != d->mWidgets.end())
    {
       d->mWidgets.erase(iter);
    }
    return qy::kHOk;
}

void* HFactory::createGItem(const HClassInfo& clsinfo, QGraphicsItem* parent, const HCreateParameter& param, long *hr)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        *hr = qy::kHNotInit;
        return NULL;
    }
    GItemMap::iterator iter = d->mWidgets.find(clsinfo.mClsName);
    if (iter == d->mWidgets.end() || !iter.value())
    {
        *hr = qy::kHNoInterface;
        return NULL;
    }
    const HRegisterGItem* unk = iter.value();
    void *obj = unk->fnCreate?unk->fnCreate(clsinfo, parent, param, hr) : NULL;
    if (!obj)
    {
        *hr = qy::kHFailure;
    }
    return obj;
}

//
bool HFactory::isQWidget(const QLatin1String &clsname)
{
    H_D(HFactory);
    QWidgetMap::iterator iter = d->mQWidgets.find(clsname);
    if (iter != d->mQWidgets.end())
    {
        return true;
    }
    return false;
}

long HFactory::coRegisterQWidget(const HRegisterQWidget* com)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        return qy::kHNotInit;
    }
    if (!com || !com->clsname || !com->fnCreate)
    {
        return qy::kHPointer;
    }
    QLatin1String id = QLatin1String(com->clsname);
    if (isQWidget(id))
    {
        return qy::kHExisted;
    }
    d->mQWidgets.insert(id,com);
    return qy::kHOk;
}

long HFactory::coUnRegisterQWidget(const QLatin1String& clsname)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        return qy::kHNotInit;
    }
    QWidgetMap::iterator iter = d->mQWidgets.find(clsname);
    if (iter != d->mQWidgets.end())
    {
       d->mQWidgets.erase(iter);
    }
    return qy::kHOk;
}

QWidget* HFactory::createQWidget(const HClassInfo& clsinfo,QWidget* parent, const HCreateParameter& param,long *hr)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        *hr = qy::kHNotInit;
        return NULL;
    }
    QWidgetMap::iterator iter = d->mQWidgets.find(clsinfo.mClsName);
    if (iter == d->mQWidgets.end() || !iter.value())
    {
        *hr = qy::kHNoInterface;
        return NULL;
    }
    const HRegisterQWidget* unk = iter.value();
    QWidget *obj = unk->fnCreate?unk->fnCreate(clsinfo,parent, param,hr) : NULL;
    if (!obj)
    {
        *hr = qy::kHFailure;
    }
    return obj;
}

//
bool HFactory::isObject(const QLatin1String &clsname)
{
    H_D(HFactory);
    ObjectMap::iterator iter = d->mObjects.find(clsname);
    if (iter != d->mObjects.end())
    {
        return true;
    }
    return false;
}

long HFactory::coRegisterObject(const HRegisterObject* com)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        return qy::kHNotInit;
    }
    QLatin1String id = QLatin1String(com->clsname);
    if (isObject(id))
    {
        return qy::kHExisted;
    }
    d->mObjects.insert(id,com);
    return qy::kHOk;
}

long HFactory::coUnRegisterObject(const QLatin1String& clsname)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        return qy::kHNotInit;
    }
    ObjectMap::iterator iter = d->mObjects.find(clsname);
    if (iter != d->mObjects.end())
    {
       d->mObjects.erase(iter);
    }
    return qy::kHOk;
}

QObject* HFactory::createObject(const HClassInfo& clsinfo, QObject *parent, const HCreateParameter& param,long *hr)
{
    H_D(HFactory);
    if (!d->isInit())
    {
        *hr = qy::kHNotInit;
        return NULL;
    }
    ObjectMap::iterator iter = d->mObjects.find(clsinfo.mClsName);
    if (iter == d->mObjects.end() || !iter.value())
    {
        *hr = qy::kHNoInterface;
        return NULL;
    }
    const HRegisterObject* unk = iter.value();
    QObject *obj = unk->fnCreate?unk->fnCreate(clsinfo,parent, param, hr) : NULL;
    if (!obj)
    {
        *hr = qy::kHFailure;
    }
    return obj;
}
