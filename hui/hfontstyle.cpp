#include "hfontstyle.h"
#include <QStringList>

Q_DECLARE_METATYPE(QFont::StyleStrategy)
Q_DECLARE_METATYPE(QFont::Capitalization)
Q_DECLARE_METATYPE(QFont::HintingPreference)
Q_DECLARE_METATYPE(QFont::StyleHint)

IMPLEMENT_OBJECT_STATIC_CREATE(HFontStyle)

HFontStyle::HFontStyle(QObject *parent) :
    HBaseStyle(parent)
{
    mObjType = USEOBJTYPE(HFontStyle);
}

HFontStyle::HFontStyle(const HObjectInfo& objinfo, QObject *parent) :
    HBaseStyle(objinfo,parent)
{
    mObjType = USEOBJTYPE(HFontStyle);
}

HFontStyle::~HFontStyle()
{
}

void HFontStyle::setLetterSpacing(const QString& letter)
{
    QStringList s = letter.split('|');
    if (s.size() >= 2) {
        setLetterSpacing((QFont::SpacingType)s.at(0).toInt(),s.at(1).toFloat());
    }
}

