#ifndef HWIDGETSTYLE_H
#define HWIDGETSTYLE_H

#include "hbasestyle.h"

class HWidgetStyle : public HBaseStyle
{
    Q_OBJECT
    Q_PROPERTY( QString styleSheet READ styleSheet WRITE setStyleSheet)
    Q_PROPERTY(	HClassInfo backgroundStyle READ backgroundStyle WRITE setBackgroundStyle )
    Q_PROPERTY(	HClassInfo layoutStyle READ layoutStyle WRITE setLayoutStyle)
public:
    explicit HWidgetStyle(QObject *parent = 0);
    explicit HWidgetStyle(const HObjectInfo& objinfo, QObject *parent = 0);

    DECLARE_OBJECT_STATIC_CREATE(HWidgetStyle);
public:

    bool hasStyleSheet() const;
    void setStyleSheet(const QString& sheet);
    QString styleSheet() const;

    bool hasBackgroundStyle() const;
    void setBackgroundStyle(const HClassInfo& cls);
    HClassInfo backgroundStyle() const;

    bool hasLayoutStyle() const;
    void setLayoutStyle(const HClassInfo& cls);
    HClassInfo layoutStyle() const;

    void copyTo(HBaseStyle* obj);
    HBaseStyle* clone();

protected:
    QString   mStyleSheet;
    HClassInfo mBackgroundStyle;
    HClassInfo mLayoutStyle;
};

#endif // HWIDGETSTYLE_H
