#include "hbasestyle.h"
#include "hcore.h"
#include "hstyle.h"

HBaseStyle::HBaseStyle(QObject* parent) :
    QObject(parent)
{
}

HBaseStyle::HBaseStyle(const HObjectInfo& objinfo,QObject *parent) :
    QObject(parent),HObject(objinfo.mStyleId)
{
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.mObjName.latin1());
}

void HBaseStyle::backup(const HStyle* style)
{
    QSharedPointer<HBaseStyle> back = style->itemAt(styleId());
    if (back) {
        back->copyTo(this);
    }
    else if(style != HSTYLE)
    {
        backup(HSTYLE);
    }
    else
        qDebug("backup:Not find font style=%s in system style",styleId());
}

HBaseStyle::~HBaseStyle()
{
}

void HBaseStyle::copyTo(HBaseStyle* obj)
{
    if (!obj) return ;
    obj->mChild = mChild;
}

HBaseStyle* HBaseStyle::clone()
{
    HBaseStyle* style = new HBaseStyle(HObjectInfo(styleId(),""),parent());
    return style;
}

void HBaseStyle::addChild(const QString& name,const HClassInfo& info)
{
    //qDebug("HBaseStyle::addChild");
    mChild[name] = info;
}

void HBaseStyle::removeChild(const QString& name)
{
    mChild.remove(name);
}

HClassInfo HBaseStyle::childAt(const QString& name)
{
    ChildClassMap::iterator iter = mChild.find(name);
    return (iter != mChild.end())?iter.value():HClassInfo();
}
