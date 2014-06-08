#include "hunknown.h"
#include <QMap>

HUnknown::HUnknown (IHUnknown* unk)
{
    mRef = 0;
    mUnk = (unk != 0 ? unk : reinterpret_cast<IHUnknown*>(static_cast<IHNonDelegatingUnknown*>(this)));
}

HUnknown::~HUnknown()
{
}

IHUnknown* HUnknown::owner(void)
{
    return mUnk;
}

long HUnknown::NonDelegatingQueryInterface(const HGuid& guid, void** ppv)
{
    if (compareHGuid(&guid ,&IID_IUnknown)) {
        IHUnknown* unk = reinterpret_cast<IHUnknown*>(static_cast<IHNonDelegatingUnknown*>(this));
        unk->addRef();
        *ppv = unk;
        return qy::kHOk;
    }
    *ppv = 0;
    return qy::kHNoInterface;
}

ulong HUnknown::NonDelegatingAddRef()
{
#ifdef WIN32
    InterlockedIncrement(&mRef);
#else
    mRef ++;
#endif //WIN32
    return mRef;
}

ulong HUnknown::NonDelegatingRelease(void)
{
#ifdef WIN32
    if (0 == InterlockedDecrement(&mRef))
    {
        delete this;
        return( 0 );
    }
#else
    mRef --;
    if (mRef <= 0)
    {
        delete this;
        return 0;
    }
#endif //WIN32
    return mRef;
}
//
class HGlobalUnkPrivate
{
public:
    HGlobalUnkPrivate()
    {
    }

    ~HGlobalUnkPrivate()
    {
        foreach (IHUnknown* unk, mUnks) {
           unk->release();
        }
        mUnks.clear();
        mUnSafes.clear();
    }
    QMap<HGuid,IHUnknown*> mUnks;
    QMap<HGuid,void*> mUnSafes;
};

IMPLEMENT_IUNK_CREATE(HGlobalUnk)
HGlobalUnk::HGlobalUnk(IHUnknown* unk)
    :HUnknown(unk)
    ,d_ptr(new HGlobalUnkPrivate())
{
}

HGlobalUnk::~HGlobalUnk()
{
    delete d_ptr;
}

long  HGlobalUnk::query(const HGuid& guid, void** ppv)
{
    QMap<HGuid,IHUnknown*>::iterator iter = d_ptr->mUnks.find(guid);
    if (iter != d_ptr->mUnks.end()) {
        IHUnknown* unk = iter.value();
        unk->addRef();
        *ppv = unk;
        return qy::kHOk;
    }
    return owner()->query(guid,ppv);
}

ulong HGlobalUnk::addRef()
{
    return owner()->addRef();
}

ulong HGlobalUnk::release()
{
    return owner()->release();
}

void HGlobalUnk::addUnk(const HGuid& guid,IHUnknown* unk)
{
    if (unk)
    {
        QMap<HGuid,IHUnknown*>::iterator iter = d_ptr->mUnks.find(guid);
        if (iter != d_ptr->mUnks.end())
            return ;

        d_ptr->mUnks[guid] = unk;
        hAddRef(unk);
    }
}

void HGlobalUnk::removeUnk(const HGuid& guid)
{
    QMap<HGuid,IHUnknown*>::iterator iter = d_ptr->mUnks.find(guid);
    if (iter != d_ptr->mUnks.end()) {
        IHUnknown* unk = iter.value();
        d_ptr->mUnks.erase(iter);
        hRelease(unk);
    }
}

void HGlobalUnk::addUnsafe(const HGuid& guid, void* unk)
{
    if (unk)
    {
        QMap<HGuid,void*>::iterator iter = d_ptr->mUnSafes.find(guid);
        if (iter != d_ptr->mUnSafes.end())
            return ;

        d_ptr->mUnSafes[guid] = unk;
    }
}

void HGlobalUnk::removeUnsafe(const HGuid& guid)
{
    d_ptr->mUnSafes.remove(guid);
}

long HGlobalUnk::queryUnsafe(const HGuid& guid, void** ppv)
{
    QMap<HGuid,void*>::iterator iter = d_ptr->mUnSafes.find(guid);
    if (iter != d_ptr->mUnSafes.end()) {
        *ppv = iter.value();
        return qy::kHOk;
    }
    return qy::kHNoInterface;
}
