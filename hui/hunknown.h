#ifndef  HUNKNOWN_H
#define  HUNKNOWN_H

#include "hconfig.h"
#include "hunknown_i.h"

template <typename T>
class HComPtr
{
public:
    HComPtr()
    {
        mUnk = 0;
	}

    HComPtr(T* p)
    {
        mUnk = p;
        hAddRef(mUnk);
	}

    ~HComPtr()
    {
        hRelease(mUnk);
	}

    operator T*() const
    {
        return mUnk;
	}

	T& operator*() const
	{	
        return *mUnk;
	}

    T* operator ->() const
    {
        return mUnk;
	}

	T** operator&()
	{
        return &mUnk;
	}

	bool operator!() const
	{
        return (mUnk == 0);
	}

	bool operator != (T* pT) const
	{
		return !operator==(pT);
	}

	bool operator == (T* pT) const
	{
        return mUnk == pT;
	}

    void addRef()
	{
        hAddRef(mUnk);
	}
	// Release the interface and set to NULL
    void release()
	{
        T* u = mUnk;
        mUnk = 0;

        hRelease(u);
	}
	// attach to an existing interface (does not AddRef)
	void attach(T* p2)
    {
        T* o = mUnk;
        mUnk = p2;
        hRelease(o);
	}
	// detach the interface (does not Release)
	T* detach()
	{
        T* pt = mUnk;
        mUnk = 0;
		return pt;
	}
    T* mUnk;
};

struct IHNonDelegatingUnknown
{
    virtual long    NonDelegatingQueryInterface(const HGuid& riid ,void** ppv) = 0;
    virtual ulong   NonDelegatingAddRef() = 0;
    virtual ulong   NonDelegatingRelease() = 0;
};

class H_API HUnknown : public IHNonDelegatingUnknown
{
private:
	/* Owner of this object */
    IHUnknown* mUnk;

protected:
    volatile long mRef;

public:
	/// Constructor
    HUnknown (IHUnknown* pUnk);
    virtual ~HUnknown ();

    IHUnknown* owner(void);
public:
    virtual long  NonDelegatingQueryInterface(const HGuid& guid, void** ppv);
    virtual ulong NonDelegatingAddRef();
    virtual ulong NonDelegatingRelease(void);
};

#define DECLARE_IHUNKNOWN()                              \
    virtual long query(const HGuid& guid, void** ppv)  { \
    return owner()->query(guid,ppv);}                    \
    virtual ulong addRef() {                             \
    return owner()->addRef();}                           \
    virtual ulong release() {                            \
    return owner()->release();}

#define DECLARE_IUNK_CREATE(clsname) static HUnknown* createInstance(IHUnknown* unk, long *hr)
#define IMPLEMENT_IUNK_CREATE(clsname) HUnknown* clsname::createInstance(IHUnknown* unk, long *hr) {\
    *hr = qy::kHOk;                 \
    return new clsname(unk); }

class HGlobalUnkPrivate;
class H_API HGlobalUnk : public HUnknown , public IHGlobalUnk
{
public:
    HGlobalUnk(IHUnknown* unk);
    ~HGlobalUnk();

    DECLARE_IUNK_CREATE(HGlobalUnk);
public:
    long  query(const HGuid& guid, void** ppv);
    ulong addRef();
    ulong release();

    void addUnk(const HGuid& guid, IHUnknown* unk);
    void removeUnk(const HGuid& guid);

    void addUnsafe(const HGuid& guid, void* unk);
    void removeUnsafe(const HGuid& guid);
    long queryUnsafe(const HGuid& guid, void** ppv);
private:
    HGlobalUnkPrivate* d_ptr;
};

#endif // HUNKNOWN_H
