#ifndef HGWIDGET_P_H
#define HGWIDGET_P_H

#include "hbase.h"
#include "hcssstyle.h"

class HGWidget;
class HBackgroundItem;

class H_API HGWidgetPrivate
{
public:
    explicit HGWidgetPrivate(const QLatin1String& styleid);
    virtual ~HGWidgetPrivate();

private:
    void init();
protected:
    friend class HGWidget;
    HGWidget* q_ptr;
    QSharedPointer<HBackgroundItem> mBackground;
    QSharedPointer<HCssObject>  mCss;
    QLatin1String  mStyleId;
};

#endif // HGWIDGET_P_H
