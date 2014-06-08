#ifndef HGView_P_H
#define HGView_P_H

#include "hbase.h"
#include <QGraphicsView>

class HGView;
class HFrameStyle;
class HImageStyle;
class HQLayout;
class HGSceneItem;
class HStyle;

class H_API HGViewPrivate
{
    Q_DECLARE_PUBLIC(HGView)
public:
    HGViewPrivate();
    virtual ~HGViewPrivate();

private:
    void init();
    bool installStyle(const HStyle* style);
    void initStyle(const HStyle* style);
    void initFontStyle(const HStyle* style,const char* styleid);
protected:
    virtual void onInitStyle(const HStyle*){}
protected:
    friend class HGView;
    HGView      *q_ptr;
    HQLayout    *mLayout;
    QSharedPointer<HFrameStyle>      mFrameStyle;
    QSharedPointer<HGSceneItem>     mSceneStyle;
    QSharedPointer<HImageStyle>      mBkgStyle;
};

#endif // HGView_P_H
