#ifndef HGWIDGETSTYLE_H
#define HGWIDGETSTYLE_H

#include "hwidgetstyle.h"

class HGWidget;

class H_API HGWidgetStyle : public HWidgetStyle
{
    Q_OBJECT
public:
    explicit HGWidgetStyle(QObject *parent = 0);
    explicit HGWidgetStyle(const HObjectInfo& objinfo, QObject *parent = 0);

    DECLARE_OBJECT_STATIC_CREATE(HGWidgetStyle);
public:
    void setWidget(HGWidget* widget);

    HBaseStyle* clone();
protected:
    HGWidget *mWidget;
};

#endif // HGWIDGETSTYLE_H
