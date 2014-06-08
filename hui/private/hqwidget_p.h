#ifndef HGWIDGET_P_H
#define HGWIDGET_P_H

#include "hbase.h"
#include "hqlayout.h"

class HImageStyle;
class HQWidget;
class HFrameStyle;
class HStyle;

class H_API HQWidgetPrivate
{
public:
    explicit HQWidgetPrivate();
    virtual ~HQWidgetPrivate();

private:
    void init();
    bool installStyle(const HStyle* style);
    void initStyle(const HStyle* style);
    void initFontStyle(const HStyle* style,const char* styleid);
protected:
    virtual void onInitStyle(const HStyle*){}
protected:
    friend class HQWidget;
    HQWidget  *q_ptr;
    HQLayout*    mLayout;
    QSharedPointer<HFrameStyle>  mFrameStyle;
    QSharedPointer<HImageStyle>  mBkgStyle;
};

#endif // HGWIDGET_P_H
