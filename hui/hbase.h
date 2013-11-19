#ifndef HBASE_H
#define HBASE_H

#include "hconfig.h"
#include <QByteArray>
#include <QLatin1String>
#include <QVariant>
#include <QMetaType>


class H_API HObject
{
public:

    HObject(){}
    virtual ~HObject(){}

protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    virtual void doConstruct(){}
};

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
Q_DECLARE_METATYPE(HAnchor);

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
Q_DECLARE_METATYPE(HLayoutIndex);

/** stylid , objectname, classname */
class HString
{
  public:
    HString(){}

    HString(const char* id ) :
        mId(id?id:""){}

    HString(const std::string& id) :
        mId(id){}

    HString(const HString& id):
        mId(id.mId){}

    HString(const QLatin1String& id) :
        mId(id.size()>1?id.data():""){}

    HString(const QString& id) :
        mId(id.toStdString()){}

public:
    QString toString() const { return QString::fromStdString(mId); }
    QLatin1String latin1() const { return QLatin1String(mId.c_str(),mId.length());}
    const char* data() const { return mId.data();}
    const char* data(const char* def) { return size()>1?data():def; }
    int size() const { return (int)mId.size(); }

    inline bool operator==(const HString &s) const
    {
        return (latin1() == s.latin1());
    }
    inline bool operator!=(const HString &s) const
    {
        return (latin1() != s.latin1());
    }
    inline bool operator>(const HString &s) const
    {
        return (latin1() > s.latin1());
    }
    inline bool operator<(const HString &s) const
    {
        return (latin1()<s.latin1());
    }
    inline bool operator>=(const HString &s) const
    {
        return (latin1()>=s.latin1());
    }
    inline bool operator<=(const HString &s) const
    {
        return (latin1()<=s.latin1());
    }

    std::string mId;
};

/** if create object class , need clsname AND styleid */
class HObjectInfo
{
public:
    HObjectInfo() :
        mStyleId(""),
        mObjName(""){}

    HObjectInfo(const HObjectInfo& info):
        mStyleId(""),
        mObjName("")
    {
        *this = info;
    }

    HObjectInfo& operator=(const HObjectInfo& info)
    {
        mStyleId = info.mStyleId;
        mObjName = info.mObjName;
        return *this;
    }

    HObjectInfo(const char* stylid, const char* name) :
        mStyleId(stylid),
        mObjName(name) {}

    HObjectInfo(const HString& stylid,const HString& name):
        mStyleId(stylid.latin1()),
        mObjName(name.latin1()){}

    HObjectInfo(const QLatin1String& stylid,const QLatin1String& name):
        mStyleId(stylid),
        mObjName(name){}

    const char* objName() const { return mObjName.data();}

    HString mStyleId;
    HString mObjName;
};

class HClassInfo : public HObjectInfo
{
public:
    HClassInfo() :
        mClsName("")
    {
    }
    HClassInfo(const HClassInfo& info):
        mClsName("")
    {
        *this = info;
    }

    HClassInfo& operator=(const HClassInfo& info)
    {
        this->mClsName = info.mClsName;
        this->mStyleId = info.mStyleId;
        this->mObjName = info.mObjName;
        return *this;
    }

    HClassInfo(const char* cls, const char* styleid,const char* name) :
        HObjectInfo(styleid,name),
        mClsName(cls){}

    HClassInfo(const HString& cls,const HString& styleid,const HString& name):
        HObjectInfo(styleid,name),
        mClsName(cls.latin1()){}

    HClassInfo(const QLatin1String& cls,const QLatin1String& stylid,const QLatin1String& name):
        HObjectInfo(stylid,name),
        mClsName(cls){}

    bool isValid() const
    {
        return (mClsName.size()>1 && mStyleId.size()>1);
    }

    HString mClsName;
};

Q_DECLARE_METATYPE(HClassInfo);
Q_DECLARE_METATYPE(HObjectInfo);

inline QVariant classInfo2QVariant(const HClassInfo& info)
{
    QVariant v;
    v.setValue(info);
    return v;
}

inline QVariant objectInfo2QVariant(const HObjectInfo& info)
{
    QVariant v;
    v.setValue(info);
    return v;
}

template<class OBJ>
inline OBJ* hDoConstructT(OBJ* obj)
{
    obj->doConstruct();
    return obj;
}

template<class OBJ>
inline OBJ* hSetObjectT(const HObjectInfo& objinfo, OBJ* obj)
{
    if (objinfo.mObjName.size()>1) obj->setObjectName(objinfo.objName());
    return obj;
}

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
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QObject)

#define IMPLEMENT_OBJECT_STATIC_CREATE(CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(CLSNAME,CLSNAME,create##CLSNAME,QObject)

// QGraphicsItem
#define DECLARE_GITEM_STATIC_CREATE(CLSNAME)      \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QGraphicsItem)

#define IMPLEMENT_GITEM_STATIC_CREATE(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(NEWOBJ,CLSNAME,create##NEWOBJ,QGraphicsItem)

#define IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC_DEFINED(NEWOBJ,CLSNAME,create##NEWOBJ,QGraphicsItem)

// HGView
#define DECLARE_GVIEW_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QWidget)

#define IMPLEMENT_GVIEW_STATIC_CREATE(CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(CLSNAME,CLSNAME,create##CLSNAME,QWidget)

// QWidget
#define DECLARE_QWIDGET_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QWidget)

#define IMPLEMENT_QWIDGET_STATIC_CREATE(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(NEWOBJ,CLSNAME,create##NEWOBJ,QWidget)

#define IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC_DEFINED(NEWOBJ,CLSNAME,create##NEWOBJ,QWidget)

#define REG_QWIDGET(CLSNAME,CREATOR)   \
   {#CLSNAME,(HCreateQWidgetInstanceCB)&CREATOR::create##CLSNAME}

#define REG_GITEM(CLSNAME,CREATOR)     \
   {#CLSNAME,(HCreateGItemInstanceCB)&CREATOR::create##CLSNAME}

#define REG_OBJECT(CLSNAME,CREATOR)    \
   {#CLSNAME,(HCreateObjectInstanceCB)&CREATOR::create##CLSNAME}
//
#define DECLARE_STATIC_CONVERT_FUNC(RETVAL,PARAM,TYPE)    \
    static RETVAL convert##TYPE(const PARAM& val, long *hr)

#define IMPLEMENT_STATIC_CONVERT_FUNC(CLSNAME,RETVAL,PARAM,TYPE)  \
    RETVAL CLSNAME::convert##TYPE(const PARAM& val, long *hr)

#define REG_CONVERT(ID,TYPE,CREATOR)     \
    {ID, (HConvertString2QvariantCB)&CREATOR::convertQVariant_##TYPE,(HConvertQvariant2StringCB)&CREATOR::convertQString_##TYPE}

#endif // HBASE_H
