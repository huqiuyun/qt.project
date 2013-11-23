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
}

HBaseStyle::~HBaseStyle()
{
}

void HBaseStyle::copyTo(HBaseStyle* obj)
{
    if (!obj) return ;
}

HBaseStyle* HBaseStyle::clone()
{
    HBaseStyle* style = new HBaseStyle(HObjectInfo(styleId(),""),parent());
    return style;
}
