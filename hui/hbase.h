#ifndef HBASE_H
#define HBASE_H

#include "hconfig.h"
#include "henums.h"
#include <QByteArray>
#include <QLatin1String>
#include <QVariant>
#include <QMetaType>
#include <QMargins>
#include <QList>
#include <QSharedPointer>

/** stylid , objectname, classname */
class HString
{
  public:
    HString(){}

    HString(const char* id ) :
        mId(id?id:""){}

    HString(const std::string& id) :
        mId(id){}

    HString(const HString& id)
    {
        *this = id;
    }

    HString& operator =(const HString& id)
    {
        mId = id.mId;
        return *this;
    }

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

class H_API HObject
{
public:
    HObject(const HString& styleid = HString()) :
        mObjType(USEOBJTYPE(Unk)),
        mStyleId(styleid)
    {}
    virtual ~HObject(){}

    int objType() const {return mObjType;}
    const char* styleId() const { return mStyleId.data();}
protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    virtual void doConstruct(){}

protected:
    int mObjType;
    HString  mStyleId;
};

class HIdValue
{
public:
    QString mId;
    QVariant mVal;
    bool mProxy;

    HIdValue():
        mProxy(false){}

    HIdValue(const QString& id,const QString& val,bool proxy=false):
        mId(id),
        mVal(val),
        mProxy(proxy){}
};

template<class WIDGET>
class HChildWidget
{
public:
    HChildWidget(WIDGET* w, const QMargins& m) :
        widget(w),
        margins(m)
    {}
    QPointer<WIDGET> widget;
    QMargins margins;
};

template<class WIDGET>
class HChildWidgetList
{
    typedef HChildWidget<WIDGET> VALUE;
    QList<VALUE> mChilds;
public:
    HChildWidgetList(){
    }

    int count() const {
        return mChilds.count();
    }

    const VALUE& at(int idx) const
    {
        return mChilds.at(idx);
    }

    int at(const WIDGET* w) {
        for (int i=0; i<mChilds.count();i++)
            if (mChilds.at(i).widget == w) return i;
        return -1;
    }

    void  add(WIDGET* w,const QMargins& m) {
        mChilds.append(VALUE(w,m));
    }

    void remove(WIDGET* w) {
        int idx = at(w);
        if (idx!=-1) mChilds.removeAt(idx);
    }
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
Q_DECLARE_METATYPE(HAnchor)

class H_API HLayoutConf
{
public:
    HLayoutConf()
    {
    }

    HLayoutConf(int index)
    {
        mConf.use = true;
        mConf.row = index;
        mConf.col = -1;
    }

    HLayoutConf(int row,int col)
    {
        mConf.use = true;
        mConf.row = row;
        mConf.col = col;
    }
public:
    int pos() const { return mConf.row;}
    int row() const { return mConf.row;}
    int column() const { return mConf.col;}

    // for QBoxLayout
    int stretch() const {
        return mConf.cf0;
    }

    void setStretch(int stretch) {
        mConf.cf0 = stretch;
    }

    void setAlignment(Qt::Alignment align) {
        mConf.cf1 = (int)align;
    }

    Qt::Alignment alignment() const {
        return (Qt::Alignment)mConf.cf1;
    }

    void fromMargins(const QMargins& m) {
        mConf.use = true;
        mConf.row = m.left();
        mConf.col = m.top();
        mConf.cf0 = m.right();
        mConf.cf1 = m.bottom();
    }

    QMargins toMargins() const {
        return QMargins(mConf.row,mConf.col,mConf.cf0,mConf.cf1);
    }

    struct Conf {
        bool use;
        int  row; // for HBOX,VBOX, grid row , QMargins.left
        int  col; // QMargins.top
        int  cf0; // for QBoxLayout stretch, QMargins.right
        int  cf1; // for QBoxLayout Alignment, QMargins.bottom
        Conf() {
            use = false;
            row = col = -1;
            cf0 = 0;
            cf1 = 0;
        }
    };
    Conf mConf;
};
Q_DECLARE_METATYPE(HLayoutConf)

class HTileP
{
public:
    HTileP()
    {
        p0 = p1 = 0;
    }
    int p0;
    int p1;
};
Q_DECLARE_METATYPE(HTileP)

class HTile
{
public:
    HTile()
    {
    }

    HTile(const HTile& t)
    {
        *this = t;
    }

    HTile& operator=(const HTile& t)
    {
        mLeft = t.mLeft;
        mMid = t.mMid;
        mRight = t.mRight;
        mY = t.mY;
        return *this;
    }

    void initX(int w, int x0, int x1)
    {
        if (x0>w) x0=w;
        if (x1>w) x1=w;

        mLeft.p0=0;
        mLeft.p1=x0;

        mMid.p0 = x0+1;
        mMid.p1 = x1;

        mRight.p0 = x1+1;
        mRight.p1 = w;
    }

    void offsetX(int x)
    {
        mLeft.p0+=x;
        mLeft.p1+=x;

        mMid.p0+=x;
        mMid.p1+=x;

        mRight.p0+=x;
        mRight.p1+=x;
    }

    void initY(int y0,int y1)
    {
        mY.p0 = y0;
        mY.p1 = y1;
    }

    void offsetY(int y)
    {
        mY.p0+=y;
        mY.p1+=y;
    }

    int height() const
    {
        return (mY.p1-mY.p0);
    }

    bool onlyOne() const
    {
        return (mMid.p0>=mMid.p1 &&mRight.p0>=mRight.p1);
    }
    HTileP mLeft;
    HTileP mMid;
    HTileP mRight;
    HTileP mY;
};
Q_DECLARE_METATYPE(HTile)

class H9Tile
{
public:
    H9Tile()
    {}

    H9Tile(const H9Tile& t)
    {
        *this = t;
    }
    H9Tile& operator=(const H9Tile& t)
    {
        mOne = t.mOne;
        mTwo = t.mTwo;
        mThree = t.mThree;
        return *this;
    }

    void initX(int w, int x0, int x1)
    {
        mOne.initX(w,x0,x1);
        mTwo.initX(w,x0,x1);
        mThree.initX(w,x0,x1);
    }

    void offsetX(int x)
    {
        mOne.offsetX(x);
        mTwo.offsetX(x);
        mThree.offsetX(x);
    }

    void initY(int h,int y0, int y1)
    {
        if (y0>h) y0=h;
        if (y1>h) y1=h;
        mOne.initY(0,y0);
        mTwo.initY(y0+1,y1);
        mThree.initY(y1+1,h);
    }

    void offsetY(int y)
    {
        mOne.offsetY(y);
        mTwo.offsetY(y);
        mThree.offsetY(y);
    }

    bool onlyOne() const
    {
        return (mTwo.height()<=0&&mThree.height()<=0);
    }

    HTile mOne;
    HTile mTwo;
    HTile mThree;
};
Q_DECLARE_METATYPE(H9Tile)

class H_API HImageTile
{
public:
    HImageTile()
    {
        mSys = false;
        mWidth = mHeight = 0;
        mHoriLine = mVertLine = 1;
    }

    void initX(int x0, int x1);
    void initY(int y0, int y1);
    bool next(int idx);
    void sysTile();
    void divX();
    void divY();

    // printf info
    void debug() const;

    bool mSys;
    int mWidth; //per tile width
    int mHeight;//per tile height
    int mHoriLine;
    int mVertLine;
    H9Tile m9Tile;
};
Q_DECLARE_METATYPE(HImageTile)

/** if create object class , need clsname AND styleid */
class HObjectInfo
{
public:
    HString mStyleId;
    HString mObjName;

    HObjectInfo(){}

    HObjectInfo(const HObjectInfo& info)
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

    QVariant toQVariant() const
    {
        QVariant v;
        v.setValue(*this);
        return v;
    }
};

class HClassInfo : public HObjectInfo
{
public:
    HString mClsName;

    HClassInfo()
    {
    }
    HClassInfo(const HClassInfo& info)
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
    QVariant toQVariant() const
    {
        QVariant v;
        v.setValue(*this);
        return v;
    }
};

Q_DECLARE_METATYPE(HClassInfo)
Q_DECLARE_METATYPE(HObjectInfo)

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

class HBaseStyle;
template<class OBJ>
inline OBJ* hStyleCast(HBaseStyle* obj)
{
    return static_cast<OBJ*>(obj);
}

template<class OBJ>
inline OBJ* hStyleSharedCast(QSharedPointer<HBaseStyle> obj)
{
    return static_cast<OBJ*>(obj.data());
}

template<class OBJ>
inline QSharedPointer<OBJ> hStyleShared(HBaseStyle* obj)
{
    return QSharedPointer<OBJ>(static_cast<OBJ*>(obj));
}

class HCreateParam
{
public:
    explicit HCreateParam():
        mConstruct(true),
        mType(USEOBJTYPE(Unk)),
        mError(-1)
    {
    }
    explicit HCreateParam(bool construct, const QVariant& var0) :
        mConstruct(construct),
        mVar0(var0),
        mType(USEOBJTYPE(Unk)),
        mError(-1)
    {
    }
    explicit HCreateParam(bool construct, const QVariant& var0, const QVariant& var1) :
        mConstruct(construct),
        mVar0(var0),
        mVar1(var1),
        mType(USEOBJTYPE(Unk)),
        mError(-1)
    {
    }
    inline bool construct() const {return mConstruct;}
    inline bool hasError() const { return mError != 0;}

    inline int&  type() { return mType;}
    inline long& error() { return mError;}
public:
    //输入参数
    bool mConstruct;
    QVariant mVar0;
    QVariant mVar1;
    // 输出参数
    int  mType;
    long mError;
};

#define DECLARE_STATIC_CREATE_FUNC(NEWOBJ,FUNC,PAPENT)    \
    static NEWOBJ* FUNC(const HObjectInfo& objinfo, PAPENT* parent, HCreateParam& param)

#define IMPLEMENT_STATIC_CREATE_FUNC(NEWOBJ,CLSNAME,FUNC,PAPENT,TYPE)   \
    NEWOBJ* CLSNAME::FUNC(const HObjectInfo& objinfo, PAPENT* parent, HCreateParam& param) {\
    param.error() = qy::kHOk;  \
    param.type() = TYPE;       \
    return (param.construct()) ? hDoConstructT(new NEWOBJ(objinfo,parent)) : new NEWOBJ(objinfo,parent);  \
    }

#define IMPLEMENT_STATIC_CREATE_FUNC_DEFINED(NEWOBJ,CLSNAME,FUNC,PAPENT)  \
    NEWOBJ* CLSNAME::FUNC(const HObjectInfo& objinfo, PAPENT* parent, HCreateParam& param)

// QObject
#define DECLARE_OBJECT_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QObject)

#define IMPLEMENT_OBJECT_STATIC_CREATE(CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(CLSNAME,CLSNAME,create##CLSNAME,QObject,USEOBJTYPE(CLSNAME))

// QGraphicsItem
#define DECLARE_GITEM_STATIC_CREATE(CLSNAME)      \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QGraphicsItem)

#define IMPLEMENT_GITEM_STATIC_CREATE(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC(NEWOBJ,CLSNAME,create##NEWOBJ,QGraphicsItem,USEOBJTYPE(NEWOBJ))

#define IMPLEMENT_GITEM_STATIC_CREATE_DEFINED(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC_DEFINED(NEWOBJ,CLSNAME,create##NEWOBJ,QGraphicsItem)

// HGView
#define DECLARE_GVIEW_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QWidget)

#define IMPLEMENT_GVIEW_STATIC_CREATE(CLSNAME,TYPE)  \
    IMPLEMENT_STATIC_CREATE_FUNC(CLSNAME,CLSNAME,create##CLSNAME,QWidget,TYPE)

// QWidget
#define DECLARE_QWIDGET_STATIC_CREATE(CLSNAME)    \
    DECLARE_STATIC_CREATE_FUNC(CLSNAME,create##CLSNAME,QWidget)

#define IMPLEMENT_QWIDGET_STATIC_CREATE(NEWOBJ,CLSNAME,TYPE)  \
    IMPLEMENT_STATIC_CREATE_FUNC(NEWOBJ,CLSNAME,create##NEWOBJ,QWidget,TYPE)

#define IMPLEMENT_QWIDGET_STATIC_CREATE_DEFINED(NEWOBJ,CLSNAME)  \
    IMPLEMENT_STATIC_CREATE_FUNC_DEFINED(NEWOBJ,CLSNAME,create##NEWOBJ,QWidget)

#define REG_QWIDGET(CLSNAME,CREATOR)   \
   {#CLSNAME,(HCreateQWidgetInstanceCB)&CREATOR::create##CLSNAME}

#define REG_GWIDGET(CLSNAME,CREATOR)     \
   {#CLSNAME,(HCreateGWidgetInstanceCB)&CREATOR::create##CLSNAME}

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
