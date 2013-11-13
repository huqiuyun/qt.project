#ifndef HGView_P_H
#define HGView_P_H

#include "hconfig.h"
#include <QGraphicsView>

class QGraphicsScene;
class HGView;
class HGWidget;
class HFrameStyle;
class HBackgroundItem;
class HCssObject;

class H_API HGViewPrivate
{
    Q_DECLARE_PUBLIC(HGView)
public:
    HGViewPrivate(const QLatin1String& styleid);
    virtual ~HGViewPrivate();

private:
    void initScene();

protected:
    friend class HGView;
    HGView            *q_ptr;
    QGraphicsScene    *mScene;
    HGWidget          *mWidget; // for client regin
    HFrameStyle       *mFrameStyle;
    QSharedPointer<HCssObject> mCss;
    QLatin1String mStyleId;
};

#endif // HGView_P_H
