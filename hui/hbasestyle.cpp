#include "hbasestyle.h"

HBaseStyle::HBaseStyle(QObject* parent) :
    QObject(parent)
{
}

HBaseStyle::HBaseStyle(const HObjectInfo& objinfo,QObject *parent) :
    QObject(parent)
{
    mObjinfo = objinfo;
    if (objinfo.mObjName.size()>1)
    {
        setObjectName(objinfo.mObjName.latin1());
    }
}

HBaseStyle::~HBaseStyle()
{
}

void HBaseStyle::copyTo(HBaseStyle* obj)
{
    if (!obj) return ;
    obj->mObjinfo = mObjinfo;
}

HBaseStyle* HBaseStyle::clone()
{
    HBaseStyle* style = new HBaseStyle(mObjinfo,parent());
    return style;
}
