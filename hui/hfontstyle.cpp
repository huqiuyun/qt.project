#include "hfontstyle.h"
#include <QStringList>

Q_DECLARE_METATYPE(QFont::StyleStrategy)
Q_DECLARE_METATYPE(QFont::Capitalization)
Q_DECLARE_METATYPE(QFont::HintingPreference)
Q_DECLARE_METATYPE(QFont::StyleHint)

IMPLEMENT_OBJECT_STATIC_CREATE(HFontStyle)

HFontStyle::HFontStyle(QObject *parent) :
    HBaseStyle(parent),
    mFont("宋体")
{
    mObjType = USEOBJTYPE(HFontStyle);
}

HFontStyle::HFontStyle(const HObjectInfo& objinfo, QObject *parent) :
    HBaseStyle(objinfo,parent),
    mFont("宋体")
{
    mObjType = USEOBJTYPE(HFontStyle);
}

HFontStyle::~HFontStyle()
{
}

void HFontStyle::setFamily(const QString & f)
{
    mFont.setFamily(f);
}

void HFontStyle::setPointSize(int s)
{
    mFont.setPointSize(s);
}

void HFontStyle::setPointSizeF(qreal s)
{
    mFont.setPointSizeF(s);
}

void HFontStyle::setPixelSize(int s)
{
    mFont.setPixelSize(s);
}

void HFontStyle::setWeight(int w)
{
    mFont.setWeight(w);
}

void HFontStyle::setBold(bool b)
{
    mFont.setBold(b);
}

void HFontStyle::setItalic(bool i)
{
    mFont.setItalic(i);
}

void HFontStyle::setUnderline(bool under)
{
    mFont.setUnderline(under);
}

void HFontStyle::setOverline(bool line)
{
    mFont.setOverline(line);
}

void HFontStyle::setStrikeOut(bool strike)
{
    mFont.setStrikeOut(strike);
}

void HFontStyle::setFixedPitch(bool pitch)
{
    mFont.setFixedPitch(pitch);
}

void HFontStyle::setKerning(bool k)
{
    mFont.setKerning(k);
}

void HFontStyle::setStyleStrategy(QFont::StyleStrategy s)
{
    mFont.setStyleStrategy(s);
}

void HFontStyle::setStretch(int s)
{
    mFont.setStretch(s);
}

void HFontStyle::setWordSpacing(qreal spacing)
{
    mFont.setWordSpacing(spacing);
}

void HFontStyle::setCapitalization(QFont::Capitalization c)
{
    mFont.setCapitalization(c);
}

void HFontStyle::setStyleHint(QFont::StyleHint style)
{
    mFont.setStyleHint(style);
}

void HFontStyle::setHintingPreference(QFont::HintingPreference hintingPreference)
{
    mFont.setHintingPreference(hintingPreference);
}

// is raw mode still needed?
void HFontStyle::setRawMode(bool mode)
{
    mFont.setRawMode(mode);
}

// needed for X11
void HFontStyle::setRawName(const QString & name)
{
    mFont.setRawName(name);
}

void HFontStyle::setLetterSpacing(QFont::SpacingType type, qreal spacing)
{
    mFont.setLetterSpacing(type,spacing);
}

void HFontStyle::setLetterSpacing(const QString& letter)
{
    QStringList s = letter.split('|');
    if (s.size() >= 2) {
        setLetterSpacing((QFont::SpacingType)s.at(0).toInt(),s.at(1).toFloat());
    }
}

void  HFontStyle::setFont(const QFont& f)
{
    mFont = f;
}

QFont HFontStyle::font() const
{
    return mFont;
}

void HFontStyle::copyTo(HBaseStyle* obj)
{
    HFontStyle* style = static_cast<HFontStyle*>(obj);
    if (!style) return ;

    style->setFont(mFont);
    HBaseStyle::copyTo(obj);
}

HBaseStyle* HFontStyle::clone()
{
    HFontStyle* style = new HFontStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}
