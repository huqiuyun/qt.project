#ifndef HBASE_H
#define HBASE_H

#include "hconfig.h"
#include <QByteArray>
#include <QLatin1String>
#include <QVariant>

typedef struct tagHAnchorItem
{
    Qt::AnchorPoint first;
    Qt::AnchorPoint second;
    int distance;
}HAnchorItem_t,*PHAnchorItem_t;

class H_API HAnchor
{
public:
    HAnchor();
    HAnchor(const HAnchorItem_t item[4]);
    HAnchor(const HAnchor& anchor);
    HAnchor& operator=(const HAnchor& anchor);

    int counts() const;
    HAnchorItem_t at(int index);

    void operator >> (QByteArray& bytes);
    void operator << (const QByteArray& bytes);
private:
    HAnchorItem_t mItems[4];
};

class H_API HLayoutIndex
{
public:
    explicit HLayoutIndex() :
        mIndex(-1),
        mRow(-1),
        mColumn(-1)
    {
    }

    explicit HLayoutIndex(int index) :
        mIndex(index),
        mRow(-1),
        mColumn(-1)
    {
    }

    explicit HLayoutIndex(int row,int col) :
        mIndex(-1),
        mRow(row),
        mColumn(col)
    {
    }
public:
    int index() const { return mIndex;}
    int row() const { return mRow;}
    int column() const { return mColumn;}
private:
    int mIndex; // for HBOX,VBOX

    int mRow; // for grid box
    int mColumn;
};

/** if create object class , need clsname AND styleid */
class HObjectInfo
{
public:
    HObjectInfo() :
        mStyleId("undefined"),
        mObjName("")
    {
    }

    HObjectInfo(const char* id, const char* name) :
        mStyleId(id),
        mObjName(name)
    {
    }
    QLatin1String mStyleId;
    QLatin1String mObjName;
};

class HClassInfo : public HObjectInfo
{
public:
    HClassInfo() :
        mClsName("undefined")
    {
    }
    HClassInfo(const char* cls, const char* id,const char* name) :
        HObjectInfo(id,name),
        mClsName(cls)
    {
    }
    QLatin1String mClsName;
};

template<class OBJ>
inline OBJ* hDoConstructT(OBJ* obj)
{
    obj->doConstruct();
    return obj;
}

template<class OBJ>
inline OBJ* hSetObjectT(const HObjectInfo& objinfo, OBJ* obj)
{
    if (objinfo.mObjName.size()>1) obj->setObjectName(objinfo.mObjName);
    return obj;
}

class H_API HObject
{
public:
    HObject(){}
    virtual ~HObject(){}
protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    virtual void doConstruct(){}
};

class HCreateParameter
{
public:
    explicit HCreateParameter():
        mConstruct(true)
    {
    }
    explicit HCreateParameter(bool construct, const QVariant& var0) :
        mConstruct(construct),
        mVar0(var0)
    {
    }
    explicit HCreateParameter(bool construct, const QVariant& var0,const QVariant& var1) :
        mConstruct(construct),
        mVar0(var0),
        mVar1(var1)
    {
    }
    inline bool construct() const {return mConstruct;}
    bool     mConstruct;
    QVariant mVar0;
    QVariant mVar1;
};

#define DECLARE_STATIC_CREATE_FUNC(CLSNAME,FUNC,PAPENT)    \
    static CLSNAME* FUNC(const HObjectInfo& objinfo, PAPENT* parent, const HCreateParameter& param, long *hr)

#define IMPLEMENT_STATIC_CREATE_FUNC(NEWOBJ,CLSNAME,FUNC,PAPENT)  \
    NEWOBJ* CLSNAME::FUNC(const HObjectInfo& objinfo, PAPENT* parent, const HCreateParameter& param, long *hr) {\
    *hr = qy::kHOk;                                                                                 \
    return (param.construct()) ? hDoConstructT(new NEWOBJ(objinfo,parent)) : new NEWOBJ(objinfo,parent);  \
    }

#define IMPLEMENT_STATIC_CREATE_FUNC_DEFINED(NEWOBJ,CLSNAME,FUNC,PAPENT)  \
    NEWOBJ* CLSNAME::FUNC(const HObjectInfo& objinfo, PAPENT* parent, const HCreateParameter& param, long *hr)


// QObject
#define DECLARE_OBJECT_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create,QObject)

#define IMPLEMENT_OBJECT_STATIC_CREATE(CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(CLSNAME,CLSNAME,create,QObject)

// HGWidget
#define DECLARE_GWIDGET_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create,QGraphicsItem)

#define IMPLEMENT_GWIDGET_STATIC_CREATE(CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(CLSNAME,CLSNAME,create,QGraphicsItem)

// HGView
#define DECLARE_GRAPHICSVIEW_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QWidget)

#define IMPLEMENT_GRAPHICSVIEW_STATIC_CREATE(CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(CLSNAME,CLSNAME,create##CLSNAME,QWidget)

// QWidget
#define DECLARE_QWIDGET_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QWidget)

#define IMPLEMENT_QWIDGET_STATIC_CREATE(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(NEWOBJ,CLSNAME,create##NEWOBJ,QWidget)

#define IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC_DEFINED(NEWOBJ,CLSNAME,create##NEWOBJ,QWidget)

#define REG_QWIDGET(CLSSTR,CLSNAME,CREATOR)   \
    {CLSSTR,(HCreateQWidgetInstanceCB)&CREATOR::create##CLSNAME}

#endif // HBASE_H
