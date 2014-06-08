#ifndef HFONTSTYLE_H
#define HFONTSTYLE_H

#include "hbasestyle.h"
#include <QFont>
#include <QString>

class H_API HFontStyle : public HBaseStyle
{
    Q_OBJECT

    Q_PROPERTY(QString family WRITE setFamily)
    Q_PROPERTY(int pointSize WRITE setPointSize)
    Q_PROPERTY(qreal pointSizeF WRITE setPointSizeF)
    Q_PROPERTY(int pixelSize WRITE setPixelSize)
    Q_PROPERTY(int weight WRITE setWeight)
    Q_PROPERTY(bool bold WRITE setBold)
    Q_PROPERTY(bool italic WRITE setItalic)
    Q_PROPERTY(bool underline WRITE setUnderline)
    Q_PROPERTY(bool overline WRITE setOverline)
    Q_PROPERTY(bool strikeOut WRITE setStrikeOut)
    Q_PROPERTY(bool fixedPitch WRITE setFixedPitch)
    Q_PROPERTY(bool kerning WRITE setKerning)
    Q_PROPERTY(QFont::StyleStrategy styleStrategy WRITE setStyleStrategy)
    Q_PROPERTY(int stretch WRITE setStretch)
    Q_PROPERTY(qreal wordSpacing WRITE setWordSpacing)
    Q_PROPERTY(QFont::Capitalization capitalization WRITE setCapitalization)
    Q_PROPERTY(QFont::HintingPreference hintingPreference WRITE setHintingPreference)
    Q_PROPERTY(QFont::StyleHint styleHint WRITE setStyleHint)
    Q_PROPERTY(bool rawMode WRITE setRawMode)
    Q_PROPERTY(QString rawName WRITE setRawName)
    Q_PROPERTY(QString letterSpacing WRITE setLetterSpacing)

public:
    explicit HFontStyle(QObject *parent = 0);
    explicit HFontStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    ~HFontStyle();

    DECLARE_OBJECT_STATIC_CREATE(HFontStyle);
public:
    void setFamily(const QString & f);
    void setPointSize(int s);
    void setPointSizeF(qreal s);
    void setPixelSize(int s);
    void setWeight(int w);
    void setBold(bool b);
    void setItalic(bool i);
    void setUnderline(bool under);
    void setOverline(bool line);
    void setStrikeOut(bool strike);
    void setFixedPitch(bool pitch);
    void setKerning(bool k);
    void setStyleStrategy(QFont::StyleStrategy s);
    void setStretch(int s);
    void setWordSpacing(qreal spacing);

    void setCapitalization(QFont::Capitalization c);
    void setStyleHint(QFont::StyleHint style);

    void setHintingPreference(QFont::HintingPreference hintingPreference);

    // is raw mode still needed?
    void setRawMode(bool mode);

    // needed for X11
    void setRawName(const QString & name);

    // for property need to parser result , format:  type(int)|spacing(qreal)
    void setLetterSpacing(const QString& letter);
    void setLetterSpacing(QFont::SpacingType type, qreal spacing);

    void  setFont(const QFont& f);
    QFont font() const;

    void copyTo(HBaseStyle* obj);
    HBaseStyle* clone();
protected:
    QFont mFont;
};

#endif // HFONTSTYLE_H
