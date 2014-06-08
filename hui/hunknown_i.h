#ifndef IHUNKNOWN_H
#define IHUNKNOWN_H

#include "hguid.h"

/** 基类接口 */
struct  IHUnknown
{
    virtual long query(const HGuid& guid, void** ppv) = 0;
    virtual ulong addRef() = 0;
    virtual ulong release() = 0;
};

struct IHGlobalUnk : public IHUnknown
{
    virtual void addUnk(const HGuid& guid,IHUnknown* unk) = 0;
    virtual void removeUnk(const HGuid& guid) = 0;

    /** 不安全接口(没有引用计数) */
    virtual void addUnsafe(const HGuid& guid, void* unk) = 0;
    virtual void removeUnsafe(const HGuid& guid) = 0;
    virtual long queryUnsafe(const HGuid& guid, void** ppv) = 0;
};

// {C47EE582-7E56-4f0a-9BFF-772A1210ABF6}
DEFINE_HGUID(IID_IUnknown,
               0xc47ee582, 0x7e56, 0x4f0a, 0x9b, 0xff, 0x77, 0x2a, 0x12, 0x10, 0xab, 0xf6);

#define hAddRef(u)  if (u) {(u)->addRef();}
#define hRelease(u) if (u) {(u)->release(); (u) = 0;}

#endif //IHUNKNOWN_H
