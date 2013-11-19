#ifndef HCORE_P_H
#define HCORE_P_H

#include "hconfig.h"
class HResourceMgr;
class HStyle;
class HFactory;
class HSystem;

class H_API HCorePrivate
{
public:
    HCorePrivate();
    virtual ~HCorePrivate();

protected:
    friend class HCore;
    HCore *q_ptr;
    HStyle *mStyle;
    HResourceMgr *mResMgr;
    HFactory *mFactory;
    HSystem *mSystem;
};

#endif // HCORE_P_H
