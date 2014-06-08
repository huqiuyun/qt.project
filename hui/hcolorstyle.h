#ifndef HCOLORSTYLE_H
#define HCOLORSTYLE_H

#include "hbasestyle.h"

class H_API HColorStyle : public HBaseStyle
{
    Q_OBJECT

public:
    explicit HColorStyle(QObject *parent = 0);
    explicit HColorStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    ~HColorStyle();

    DECLARE_OBJECT_STATIC_CREATE(HColorStyle);
public:

    Q_INVOKABLE void setCurrentColor(int index);
    Q_INVOKABLE QColor currentColor(const QColor& defColor) const;

    Q_INVOKABLE QColor color(int index,const QColor& defColor) const;
    Q_INVOKABLE void setColor(int index,const QColor& color);

    void copyTo(HBaseStyle* obj);
    HBaseStyle* clone();
private:
    int mCurrentIndex;
    QVector<QColor> mColor;
};

#endif // HCOLORSTYLE_H
