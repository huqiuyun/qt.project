#ifndef HGWIDGETSTYLE_H
#define HGWIDGETSTYLE_H

#include "hbasestyle.h"

class HGWidget;

class H_API HGWidgetStyle : public HBaseStyle
{
    Q_OBJECT
    Q_PROPERTY( QString styleSheet READ styleSheet WRITE setStyleSheet)
    Q_PROPERTY(	HClassInfo backgroundStyle READ backgroundStyle WRITE setBackgroundStyle )
    Q_PROPERTY(	HClassInfo layoutStyle READ layoutStyle WRITE setLayoutStyle)
public:
    explicit HGWidgetStyle(QObject *parent = 0);
    explicit HGWidgetStyle(const HObjectInfo& objinfo, QObject *parent = 0);

    DECLARE_OBJECT_STATIC_CREATE(HGWidgetStyle);
public:
    void setWidget(HGWidget* widget);

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
    HGWidget *mWidget;
    QString   mStyleSheet;
    HClassInfo mBackgroundStyle;
    HClassInfo mLayoutStyle;
};

#endif // HGWIDGETSTYLE_H
