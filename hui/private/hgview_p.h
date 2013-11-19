#ifndef HGView_P_H
#define HGView_P_H

#include "hbase.h"
#include <QGraphicsView>

class HGView;
class HFrameStyle;
class HBackgroundStyle;
class HQLayoutStyle;
class HGSceneStyle;

class H_API HGViewPrivate
{
    Q_DECLARE_PUBLIC(HGView)
public:
    HGViewPrivate(const char* styleid);
    virtual ~HGViewPrivate();

private:
    void init();
    void initStyle(HFrameStyle* style);
protected:
    friend class HGView;
    HGView            *q_ptr;
    QSharedPointer<HFrameStyle>      mFrameStyle;
    QSharedPointer<HGSceneStyle>     mSceneStyle;
    QSharedPointer<HBackgroundStyle> mBackgroundStyle;
    QSharedPointer<HQLayoutStyle> mLayoutStyle;
    HString            mStyleId;
};

#endif // HGView_P_H
