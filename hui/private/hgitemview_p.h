#ifndef HGWIDGET_P_H
#define HGWIDGET_P_H

#include "hbase.h"
#include "himagestyle.h"
#include "hglayoutstyle.h"
#include "hgwidgetstyle.h"
#include "hgwidget.h"

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

    void initFontStyle(const HStyle* style,const char* styleid);

protected:
    virtual void onInitStyle(const HStyle*){}
    virtual bool stateChanged() { return false;}
protected:
    friend class HGWidget;
    HGWidget* q_ptr;
    QSharedPointer<HGWidgetStyle>    mWidgetStyle;
    QSharedPointer<HImageStyle>      mBkgStyle;
    QSharedPointer<HGLayoutStyle>    mLayoutStyle;
    HGWidget::GStyles mGStyle;
    int  mState;       //@see HEnums::HWidgetState
    QString mStatisticsId;
};

#endif // HGWIDGET_P_H
