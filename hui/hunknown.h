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

class HUnknown : public IHNonDelegatingUnknown
{
private:
	/* Owner of this object */
    IHUnknown* mUnk;

protected:
	/// 引用计数
    volatile long mRef;

public:
	/// Constructor
    HUnknown (IHUnknown* pUnk)
	{
        mRef = 0;
        mUnk = (pUnk != 0 ? pUnk : reinterpret_cast<IHUnknown*>(static_cast<IHNonDelegatingUnknown*>(this)));
	}
    virtual ~HUnknown () {}
public:
    IHUnknown* GetOwner(void)
	{
        return mUnk;
	}

    virtual long NonDelegatingQueryInterface(const HGuid& guid, void** ppv)
	{
        if  (!ppv)
		{
            return qy::kHPointer;
        }

        if (compareHGuid(&guid ,&IID_IUnknown))
		{
            IHUnknown* pUnk = (IHUnknown*)((IHNonDelegatingUnknown*)this);
            pUnk->addRef();
            *ppv = pUnk;
            return qy::kHOk;
		}
        *ppv = 0;
        return qy::kHNoInterface;
	}

    virtual ulong NonDelegatingAddRef()
	{
#ifdef WIN32
        InterlockedIncrement(&mRef);
#else
        mRef ++;
#endif //WIN32
        return mRef;
	}

    virtual ulong NonDelegatingRelease(void)
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
};

//声明 IHUnknown 接口函数
#define DECLARE_IHUNKNOWN()                                  \
    virtual long queryInterface(QY_REFID riid, void** ppv)  { \
    return GetOwner()->queryInterface(riid,ppv);}             \
    virtual ulong addRef() {                                  \
    return GetOwner()->addRef();}                             \
    virtual ulong release() {                                 \
    return GetOwner()->release();}

#define DECLARE_CLASS_STATIC_CREATE(clsname) static HUnknown* createInstance(IHUnknown* pUnkOuter, long *hr);
#define IMPLEMENT_CLASS_STATIC_CREATE(clsname) HUnknown* clsname::createInstance(IHUnknown* pUnkOuter, long *hr) {\
    hr = qy::kHOk;                 \
    return new clsname(pUnkOuter); \
    }

#endif // HUNKNOWN_H
