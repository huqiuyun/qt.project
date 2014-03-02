#ifndef HGWIDGET_P_H
#define HGWIDGET_P_H

#include "hbase.h"
#include "hqlayoutstyle.h"

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

protected:
    friend class HQWidget;
    HQWidget  *q_ptr;
    QSharedPointer<HFrameStyle>      mFrameStyle;
    QSharedPointer<HBackgroundStyle> mBackgroundStyle;
    QSharedPointer<HQLayoutStyle>    mLayoutStyle;
};

#endif // HGWIDGET_P_H
