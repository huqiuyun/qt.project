#ifndef HQLAYOUTSTYLE_H
#define HQLAYOUTSTYLE_H

#include "hlayoutstyle.h"

class QWidget;
class QLayout;

class H_API HQLayoutStyle : public HLayoutStyle
{
public:
    explicit HQLayoutStyle(QObject *parent = 0);
    explicit HQLayoutStyle(const HObjectInfo& objinfo, QObject *parent = 0);

     DECLARE_OBJECT_STATIC_CREATE(HQLayoutStyle);
public:
    void setWindow(QWidget* window);
    QLayout* layout() const;

    void setLayoutType(HEnums::HLayoutType type);

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set per child item space in owner layout */
    int spacing() const;
    void setSpacing(int s);

    virtual HBaseStyle* clone();
protected:
    QWidget* mWindow;
};

#endif // HQLAYOUTSTYLE_H
