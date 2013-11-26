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
    inline void setFamily(const QString & f) {
        mFont.setFamily(f);
    }

    inline void setPointSize(int s) {
        mFont.setPointSize(s);
    }

    inline void setPointSizeF(qreal s) {
        mFont.setPointSizeF(s);
    }

    inline void setPixelSize(int s) {
        mFont.setPixelSize(s);
    }

    inline void setWeight(int w) {
        mFont.setWeight(w);
    }

    inline void setBold(bool b) {
        mFont.setBold(b);
    }

    inline void setItalic(bool i){
        mFont.setItalic(i);
    }

    inline void setUnderline(bool under) {
        mFont.setUnderline(under);
    }

    inline void setOverline(bool line) {
        mFont.setOverline(line);
    }

    inline void setStrikeOut(bool strike) {
        mFont.setStrikeOut(strike);
    }

    inline void setFixedPitch(bool pitch) {
        mFont.setFixedPitch(pitch);
    }

    inline void setKerning(bool k) {
        mFont.setKerning(k);
    }

    inline void setStyleStrategy(QFont::StyleStrategy s) {
        mFont.setStyleStrategy(s);
    }

    inline void setStretch(int s) {
        mFont.setStretch(s);
    }

    inline void setWordSpacing(qreal spacing){
        mFont.setWordSpacing(spacing);
    }

    inline void setCapitalization(QFont::Capitalization c) {
        mFont.setCapitalization(c);
    }

    inline void setStyleHint(QFont::StyleHint style) {
        mFont.setStyleHint(style);
    }

    inline void setHintingPreference(QFont::HintingPreference hintingPreference) {
        mFont.setHintingPreference(hintingPreference);
    }

    // is raw mode still needed?
    inline void setRawMode(bool mode) {
        mFont.setRawMode(mode);
    }

    // needed for X11
    inline void setRawName(const QString & name) {
        mFont.setRawName(name);
    }

    // for property need to parser result , format:  type(int)|spacing(qreal)
    void setLetterSpacing(const QString& letter);
    inline void setLetterSpacing(QFont::SpacingType type, qreal spacing){
        mFont.setLetterSpacing(type,spacing);
    }

    QFont font() const {
        return mFont;
    }
protected:
    QFont mFont;
};

#endif // HFONTSTYLE_H
