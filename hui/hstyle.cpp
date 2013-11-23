#include "HStyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "hresourcemgr.h"
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

//HStyle
HStyle::HStyle(QObject *parent) :
    QObject(parent)
{
    mObjType = USEOBJTYPE(HStyle);
}

HStyle::~HStyle()
{
}


bool HStyle::isPrivate(const char* styleid)
{
    const char* prex = "private.";
    return (styleid == strstr(styleid,prex));
}

std::string HStyle::prex(const std::string& cls, bool& pri)
{
    const char* prex = "private.";
    pri = isPrivate(cls.c_str());
    return (pri) ? cls.substr(sizeof(char)*sizeof(prex)) : cls;
}

QSharedPointer<HBaseStyle> HStyle::create(const char* styleid,const char* clsname)
{
    HClassInfo cls(clsname, styleid, "");

    if(0==cls.mStyleId.mId.find("undefined")) {
        return QSharedPointer<HBaseStyle>(NULL);
    }
    QSharedPointer<HBaseStyle> item = itemAt(styleid);
    if (item)
        return item;

    HCreateParam param;
    QSharedPointer<HBaseStyle> css(static_cast<HBaseStyle*>(HFACTORY->createObject(cls,NULL,param)));
    if (css.data()) {
        mStyle.insert(styleid,css);
    }
    return css;
}

QSharedPointer<HBaseStyle> HStyle::itemAt(const char* styleid) const
{
    bool pri = false;
    std::string findid = prex(styleid,pri);

    HStyleMap::const_iterator iter = mStyle.constFind(findid);
    if (iter != mStyle.constEnd()) {
        return iter.value();
    }
    return QSharedPointer<HBaseStyle>(NULL);
}

bool HStyle::addItem(const char* styleid, QSharedPointer<HBaseStyle> item)
{
    if (itemAt(styleid))
        return false;
    mStyle.insert(styleid,item);
    return true;
}

void HStyle::removeItem(const char* styleid)
{
    HStyleMap::iterator iter = mStyle.find(styleid);
    if (iter != mStyle.end()) {
        mStyle.erase(iter);
    }
}

void HStyle::add(const HStyleMap& styles)
{
    HStyleMap::const_iterator iter = styles.constBegin();
    while (iter != styles.constEnd()) {
        addItem(iter.key().data(),iter.value());
        ++iter;
    }
}

int HStyle::size() const
{
    return mStyle.size();
}
