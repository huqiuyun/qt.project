#ifndef HGPROXYWIDGET_P_H
#define HGPROXYWIDGET_P_H

#include "hbase.h"
#include "himagestyle.h"
#include "hgwidgetstyle.h"
class HGProxyWidget;
class HStyle;
class H_API HGProxyWidgetPrivate
{
public:
    explicit HGProxyWidgetPrivate();
    virtual ~HGProxyWidgetPrivate();

private:
    void init();
    bool installStyle(const HStyle* style);
    void initStyle(const HStyle* style);

protected:
    virtual void onInitStyle(const HStyle*){}

protected:
    friend class HGProxyWidget;
    HGProxyWidget  *q_ptr;
    QSharedPointer<HGWidgetStyle>    mWidgetStyle;
    QSharedPointer<HImageStyle>      mBkgStyle;
};

#endif // HGPROXYWIDGET_P_H
