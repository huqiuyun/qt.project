#ifndef HGWIDGET_P_H
#define HGWIDGET_P_H

#include "hbase.h"
#include "hbackgroundstyle.h"
#include "hglayoutstyle.h"
#include "hgwidgetstyle.h"
class HGWidget;
class HStyle;
class H_API HGWidgetPrivate
{
public:
    explicit HGWidgetPrivate();
    virtual ~HGWidgetPrivate();

private:
    void init();
    bool installStyle(const HStyle* style);
    void initStyle(const HStyle* style);

protected:
    friend class HGWidget;
    HGWidget  *q_ptr;
    QSharedPointer<HGWidgetStyle>    mWidgetStyle;
    QSharedPointer<HBackgroundStyle> mBackgroundStyle;
    QSharedPointer<HGLayoutStyle>    mLayoutStyle;
};

#endif // HGWIDGET_P_H
