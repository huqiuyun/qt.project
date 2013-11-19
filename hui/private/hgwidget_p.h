#ifndef HGWIDGET_P_H
#define HGWIDGET_P_H

#include "hbase.h"
#include "hbackgroundstyle.h"
#include "hglayoutstyle.h"
#include "hgwidgetstyle.h"
class HGWidget;

class H_API HGWidgetPrivate
{
public:
    explicit HGWidgetPrivate(const char* styleid);
    virtual ~HGWidgetPrivate();

private:
    void init();
    void initStyle(HGWidgetStyle* style);

protected:
    friend class HGWidget;
    HGWidget  *q_ptr;
    QSharedPointer<HGWidgetStyle>    mGWidgetStyle;
    QSharedPointer<HBackgroundStyle> mBackgroundStyle;
    QSharedPointer<HGLayoutStyle>    mLayoutStyle;
    HString  mStyleId;
};

#endif // HGWIDGET_P_H
