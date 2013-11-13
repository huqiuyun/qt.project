#ifndef HFACTORY_H
#define HFACTORY_H

#include "hconfig.h"
#include "hunknown.h"
#include "hfactory_i.h"

class HFactoryPrivate;
class H_API HFactory : public IHFactory
{
public:
    HFactory();
    virtual ~HFactory();

public:
    long coInitialize();
    long coUninitialize();

    long coRegisterUnknown(const HRegisterUnknown* com);
    long coUnRegisterUnknown(const HGuid* clsrid);
    long createInstance(IHUnknown* pUnkOuter, const HGuid& riid, void** ppv);
    //
    long coRegisterGWidget(const HRegisterGWidget* com);
    long coUnRegisterGWidget(const char* clsname);
    HGWidget* createGWidget(const HClassInfo& clsinfo, QGraphicsItem* parent, const HCreateParameter& param,long *hr);

    //
    long coRegisterQWidget(const HRegisterQWidget* com);
    long coUnRegisterQWidget(const char* clsname);
    QWidget* createQWidget(const HClassInfo& clsinfo, QWidget* parent, const HCreateParameter& param,long *hr);

    long coRegisterObject(const HRegisterObject* com);
    long coUnRegisterObject(const char* clsname);
    QObject* createObject(const HClassInfo& clsinfo, QObject* parent, const HCreateParameter& param,long *hr);
private:
    friend class HFactoryPrivate;
    HFactoryPrivate*  d_ptr;
};

/**
 * exmaple:
 *    class HExample : public HUnknown , public IHUnknown
 *    {
     public:
         DECLARE_IHUNKNOWN()

 *       DECLARE_CLASS_STATIC_CREATE
 *    };
 *
 *    const HRegisterUnknown exmaple = {IID_exmaple , &HExample::create };
 *   
 *    
 *    HFactory* factory = NULL;
 *    factory->coRegisterUnknown(&exmaple);
 * 
 *    
*/

#endif // HFACTORY_H