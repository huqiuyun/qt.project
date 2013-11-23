#include "hcore.h"
#include "HStyle.h"
#include "hresourcemgr.h"
#include "hfactory.h"
#include "hsystem.h"
#include "private/hcore_p.h"
#include "hcreator.h"

HCorePrivate::HCorePrivate() :
    q_ptr(NULL),
    mStyle(NULL),
    mResMgr(NULL),
    mFactory(NULL),
    mSystem(NULL)
{
}

HCorePrivate::~HCorePrivate()
{
    hDelete(mStyle);
    hDelete(mResMgr);
    hDelete(mFactory);
    hDelete(mSystem);
}

//HCore
HCore* HCore::gHCore = NULL;
HCore::HCore(QObject *parent) :
    QObject(parent),
    d_ptr(new HCorePrivate)
{
    d_ptr->q_ptr = this;
}

HCore::HCore(HCorePrivate& dd,QObject* parent):
    QObject(parent),
    d_ptr(&dd)
{
    d_ptr->q_ptr = this;
}

HCore::~HCore()
{
    delete d_ptr;
}

HFactory* HCore::factory()
{
    Q_D(HCore);
    if (!d->mFactory) {
        d->mFactory = new HFactory();
        d->mFactory->coInitialize();

        {for (uint i = 0; i < sizeof(s_converts)/sizeof(s_converts[0]); i++)
        {
            d->mFactory->coRegisterConvert(&s_converts[i]);
        }}
        // register object
        {for (uint i = 0; i < sizeof(s_objs)/sizeof(s_objs[0]); i++)
        {
            d->mFactory->coRegisterObject(&s_objs[i]);
        }}

        {for (uint i = 0; i < sizeof(s_gitems)/sizeof(s_gitems[0]); i++)
        {
            d->mFactory->coRegisterGItem(&s_gitems[i]);
        }}

        {for (uint i = 0; i < sizeof(s_gwidgets)/sizeof(s_gwidgets[0]); i++)
        {
            d->mFactory->coRegisterGWidget(&s_gwidgets[i]);
        }}

        {for (uint i = 0; i < sizeof(s_qwidgets)/sizeof(s_qwidgets[0]); i++)
        {
            d->mFactory->coRegisterQWidget(&s_qwidgets[i]);
        }}
    }
    return d->mFactory;
}

HResourceMgr* HCore::resMgr()
{
    Q_D(HCore);
    if (!d->mResMgr) {
        d->mResMgr = new HResourceMgr(this);
    }
    return d->mResMgr;
}

HStyle* HCore::style()
{
    Q_D(HCore);
    if (!d->mStyle) {
        d->mStyle = new HStyle(this);
    }
    return d->mStyle;
}

HSystem* HCore::system()
{
    Q_D(HCore);
    if (!d->mSystem) {
        d->mSystem = new HSystem();
    }
    return d->mSystem;
}

HCore* HCore::core()
{
    return HCore::gHCore;
}

void HCore::initHCore(HCore* core)
{
    HCore::gHCore = core;
}

