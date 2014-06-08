#include "hcolorstyle.h"

IMPLEMENT_OBJECT_STATIC_CREATE(HColorStyle)
HColorStyle::HColorStyle(QObject *parent) :
    HBaseStyle(parent)
{
    mCurrentIndex = 0;
    mObjType = USEOBJTYPE(HColorStyle);
}

HColorStyle::HColorStyle(const HObjectInfo& objinfo, QObject *parent) :
    HBaseStyle(objinfo,parent)
{
    //qDebug("HColorStyle styleid=%s",objinfo.mStyleId.data());
    mCurrentIndex = 0;
    mObjType = USEOBJTYPE(HColorStyle);
}

HColorStyle::~HColorStyle()
{
}

void HColorStyle::setCurrentColor(int index)
{
    //qDebug("HColorStyle::setCurrentColor=%d",index);
    mCurrentIndex = index;
}

QColor HColorStyle::currentColor(const QColor& defColor) const
{
    return color(mCurrentIndex,defColor);
}

QColor HColorStyle::color(int index,const QColor& defColor) const
{
    //qDebug("HColorStyle::color=%d,%d",index,mColor.size());
    return (index<0||index>=mColor.size())?defColor:mColor[index];
}

void HColorStyle::setColor(int index,const QColor& color)
{
    //qDebug("setColor:index=%d,color=%d,%d,%d",index,color.red(),color.green(),color.blue());
    if (index<0||index>=mColor.size())
        mColor.push_back(color);
    else
        mColor[index] = color;
}

void HColorStyle::copyTo(HBaseStyle* obj)
{
    HColorStyle* style = static_cast<HColorStyle*>(obj);
    if (!style) return ;

    style->mColor = mColor;
    HBaseStyle::copyTo(obj);
}

HBaseStyle* HColorStyle::clone()
{
    HColorStyle* style = new HColorStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}

