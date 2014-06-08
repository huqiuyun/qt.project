#include "hgscrollbar.h"
#include "hglobal.h"
#include "hcore.h"
#include "hstyle.h"
#include "henums.h"
#include "hfactory.h"
#include "himagestyle.h"
#include "private/hgwidget_p.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QTimer>

enum ArrowAction
{
    AActionUnk = 0,
    AActionLeft=1,
    AActionRight=2
};

typedef struct tagHSCROLLBAR
{
    Qt::Orientation	barType; //Qt::Horizontal / Qt::Vertical
    HGScrollBar::GScrollFlags scrollFlags; //flags
    HSCROLLINFO     scrollInfo; //positional data (range, position, page size etc)

    bool		    scrollVisible; //if this scrollbar visible
    int			    scrollSize; //parallel size (height of horz, width of vert)
    int             arrowSize; //arrow size (width of a horizontal, height of a vertical)
    int             oneStep;

    int			    minSliderSize;
    int             maxSliderSize;
    //
    bool            sliderTracking;
    int             sliderTrackingPos;
    QPointF         pressPos;
    //
    bool            mouseInArrow;
    ArrowAction     arrowAction;

    QRectF          leftArrow;
    QRectF          leftWorking;
    QRectF          slider;
    QRectF          rightWorking;
    QRectF          rightArrow;
    int             workingSize;

}HSCROLLBAR;

class HGScrollBarPrivate  : public HGWidgetPrivate
{
    Q_DECLARE_PUBLIC(HGScrollBar)
public:
    HGScrollBarPrivate(Qt::Orientation barType,HGScrollBar *q)
        :q_ptr(q)
    {
        mBar.barType = barType;
        mBar.oneStep = 8;
        mBar.minSliderSize = 10;
        mBar.maxSliderSize = 10000;
        mBar.sliderTracking = false;
        mBar.scrollSize = 8;
        mBar.arrowSize = 8;
        mBar.mouseInArrow = false;
        mBar.arrowAction = AActionUnk;
        mBar.scrollVisible = false;
        mBar.workingSize = 0;
        mBar.scrollFlags |= HGScrollBar::SliderTracking;
        mBar.scrollFlags |= HGScrollBar::WorkingClicked;
        mBar.scrollFlags |= HGScrollBar::HasArrow;
        memset(&mBar.scrollInfo,0,sizeof(HSCROLLINFO));
    }

    void onInitStyle(const HStyle* style)
    {
        Q_UNUSED(style);

        HClassInfo cls1 = mWidgetStyle->childAt(QLatin1String("sliderStyle"));
        if (cls1.isValid()) {
            HCreateParam param;
            HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(cls1,q_ptr,param));
            mSliderStyle = QSharedPointer<HImageStyle>(back);
            mSliderStyle->backup(style);
        }

        HClassInfo cls2 = mWidgetStyle->childAt(QLatin1String("leftArrowStyle"));
        if (cls2.isValid()) {
            HCreateParam param;
            HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(cls2,q_ptr,param));
            mLeftArrowStyle = QSharedPointer<HImageStyle>(back);
            mLeftArrowStyle->backup(style);
        }


        HClassInfo cls3 = mWidgetStyle->childAt(QLatin1String("rightArrowStyle"));
        if (cls3.isValid()) {
            HCreateParam param;
            HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(cls3,q_ptr,param));
            mRightArrowStyle = QSharedPointer<HImageStyle>(back);
            mRightArrowStyle->backup(style);
        }

        HClassInfo cls4 = mWidgetStyle->childAt(QLatin1String("leftWorkingStyle"));
        if (cls4.isValid()) {
            HCreateParam param;
            HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(cls4,q_ptr,param));
            mLeftWorkingStyle = QSharedPointer<HImageStyle>(back);
            mLeftWorkingStyle->backup(style);
        }

        HClassInfo cls5 = mWidgetStyle->childAt(QLatin1String("rightWorkingStyle"));
        if (cls5.isValid()) {
            HCreateParam param;
            HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(cls5,q_ptr,param));
            mRightWorkingStyle = QSharedPointer<HImageStyle>(back);
            mRightWorkingStyle->backup(style);
        }
    }

    int barType() const
    {
        return mBar.barType;
    }

    void updateScroll(const QRectF& rc, bool fRedraw)
    {
        QRectF rotateRc(rc);
        rotateRectWithVertical(&mBar,&rotateRc);

        int butsize = 0;
        int workingsize = 0;
        int sliderpos = 0;
        int slidersize = 0;
        calcScrollSize(&mBar, &rotateRc, butsize,workingsize, slidersize, sliderpos);

        mBar.workingSize = workingsize;
        mBar.leftArrow = QRectF(rotateRc.left(), 0, butsize, mBar.scrollSize);

        int leftWidth = sliderpos-(butsize+rotateRc.left());
        mBar.leftWorking = QRectF(mBar.leftArrow.right(), 0, leftWidth, mBar.scrollSize);

        mBar.slider = QRectF(sliderpos, 0, slidersize, mBar.scrollSize);

        int rightWidth = workingsize - (mBar.leftWorking.width() + mBar.slider.width());
        mBar.rightWorking = QRectF(mBar.slider.right(), 0, rightWidth, mBar.scrollSize);

        mBar.rightArrow = QRectF(mBar.rightWorking.right(), 0, butsize, mBar.scrollSize);

        rotateRectWithVertical(&mBar, &mBar.leftArrow);
        rotateRectWithVertical(&mBar, &mBar.leftWorking);
        rotateRectWithVertical(&mBar, &mBar.slider);
        rotateRectWithVertical(&mBar, &mBar.rightWorking);
        rotateRectWithVertical(&mBar, &mBar.rightArrow);

        if (fRedraw) q_ptr->update();
    }

    void mouseInArrow(const QPointF& pos)
    {
        if (mBar.arrowAction==AActionLeft) {
           bool in = mBar.mouseInArrow;
           mBar.mouseInArrow = mBar.leftArrow.contains(pos);
           if (in != mBar.mouseInArrow) {
                // change state ?
           }
        }
        else if(mBar.arrowAction==AActionRight) {
            bool in = mBar.mouseInArrow;
            mBar.mouseInArrow = mBar.rightArrow.contains(pos);
            if (in != mBar.mouseInArrow) {
                 // change state ?
            }
        }
    }

    void startAction(ArrowAction action)
    {
        if (mBar.arrowAction != action) {
            mBar.mouseInArrow = true;
            mBar.arrowAction = action;
            mAActionTimer.start(100);
        }
    }

    void  stopAction()
    {
        mAActionTimer.stop();
        mBar.arrowAction = AActionUnk;
    }

    void setScrollPos(int df)
    {
        q_ptr->setScrollPos(q_ptr->scrollPos() + df,true);
        emit q_ptr->sliderPositionChange(mBar.scrollInfo.nPos);
    }

    //	swap the rectangle's x coords with its y coords
    static void rotateRect(QRectF *rect)
    {
        qreal temp = rect->left();
        rect->setLeft(rect->top());
        rect->setTop(temp);

        temp = rect->right();
        rect->setRight(rect->bottom());
        rect->setBottom(temp);
    }

    //	swap the coords if the scrollbar is a Qt::Vertical
    static void rotateRectWithVertical(HSCROLLBAR *sb, QRectF *rect)
    {
        if(sb->barType == Qt::Vertical)
            rotateRect(rect);
    }

    //	Calculate if the HSCROLLINFO members produce
    //  an enabled or disabled scrollbar
    static bool isScrollInfoActive(HSCROLLINFO *si)
    {
        if((si->nPage > si->nMax || si->nMax <= si->nMin || si->nMax == 0))
            return false;

        return true;
    }

    //	Return if the specified scrollbar is enabled or not
    static bool isScrollbarActive(HSCROLLBAR *sb)
    {
        if (sb->scrollFlags.testFlag(HGScrollBar::DisableBoth))
            return false;

        return isScrollInfoActive(&sb->scrollInfo);
    }

    //	Return the size in pixels for the specified scrollbar metric,
    //  for the specified scrollbar
    static int arrowSize(HSCROLLBAR *sbar)
    {
        if (!sbar->scrollFlags.testFlag(HGScrollBar::HasArrow))
            return 0;

        return sbar->arrowSize;
    }

    //	Work out the scrollbar width/height for either type of scrollbar (Qt::Horizontal/Qt::Vertical)
    //	rect - coords of the scrollbar.
    //	store results into *slidersize and *sliderpos
    static void calcScrollSize(HSCROLLBAR *sbar,
                              const QRectF *rect,
                              int& butsize, int &workingsize,
                              int &slidersize, int &sliderpos)
    {
        HSCROLLINFO *si = &sbar->scrollInfo;

        int siMaxMin = si->nMax - si->nMin + 1;
        int scrollsize = rect->width();
        int startcoord = rect->left();

        //work out the width (for a horizontal) or the height (for a vertical)
        //of a standard scrollbar button
        butsize = arrowSize(sbar);
        workingsize = scrollsize - butsize * 2;

        if (siMaxMin > 0) {

            // Work out the scrollbar slider SIZE
            if(si->nPage > 0 && !sbar->scrollFlags.testFlag(HGScrollBar::SliderAlwaysOff)) {
                slidersize = HGlobal::mulDiv(si->nPage, workingsize, siMaxMin);
                if(slidersize < sbar->minSliderSize)
                    slidersize = sbar->minSliderSize;

                if(slidersize > sbar->maxSliderSize)
                    slidersize = sbar->maxSliderSize;
            }
            else
                slidersize = 0;

            // Work out the scrollbar slider position
            int pagesize = qMax(1, si->nPage);
            sliderpos =  HGlobal::mulDiv(si->nPos, workingsize-slidersize, siMaxMin - pagesize);

            if(sliderpos < 0)
                sliderpos = 0;

            if(sliderpos >= workingsize-slidersize)
                sliderpos = workingsize-slidersize;
        }
        sliderpos += startcoord + butsize;
    }

    HGScrollBar *q_ptr;
    QSharedPointer<HImageStyle> mSliderStyle;
    QSharedPointer<HImageStyle> mLeftArrowStyle;
    QSharedPointer<HImageStyle> mRightArrowStyle;
    QSharedPointer<HImageStyle> mLeftWorkingStyle;
    QSharedPointer<HImageStyle> mRightWorkingStyle;
    HSCROLLBAR mBar;

    QTimer mAActionTimer;
};

HGScrollBar::HGScrollBar(Qt::Orientation barType,const HObjectInfo& objinfo,QGraphicsItem *parent)
    : HGWidget(*(new HGScrollBarPrivate(barType,this)),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGScrollBar);
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    setContentsMargins(0, 0, 0, 0);

    Q_D(HGScrollBar);
    QObject::connect(&d->mAActionTimer,SIGNAL(timeout()),this,SLOT(on_arrowAction()));
}

HGScrollBar::~HGScrollBar()
{
}

void HGScrollBar::setMinSliderSize(int size)
{
     HSCROLLBAR *sbar = &(d_func()->mBar);
     sbar->minSliderSize = size;
}

int HGScrollBar::minSliderSize() const
{
     return d_func()->mBar.minSliderSize;
}

void HGScrollBar::setMaxSliderSize(int size)
{
     HSCROLLBAR *sbar = &(d_func()->mBar);
     sbar->maxSliderSize = size;
}

int HGScrollBar::maxSliderSize() const
{
     return d_func()->mBar.maxSliderSize;
}

void HGScrollBar::setScrollSize(int size)
{
    HSCROLLBAR *sbar = &(d_func()->mBar);
    sbar->scrollSize = size;
}

int HGScrollBar::scrollSize() const
{
    return d_func()->mBar.scrollSize;
}

void HGScrollBar::setArrowSize(int size)
{
    HSCROLLBAR *sbar = &(d_func()->mBar);
    sbar->arrowSize = size;
}

int HGScrollBar::arrowSize() const
{
    return d_func()->mBar.arrowSize;
}

void HGScrollBar::setScrollFlag(const HGScrollBar::GScrollFlags& flags)
{
    d_func()->mBar.scrollFlags = flags;
}

HGScrollBar::GScrollFlags HGScrollBar::scrollFlag() const
{
    return d_func()->mBar.scrollFlags;
}

bool HGScrollBar::isScrollVisible() const
{
    return d_func()->mBar.scrollVisible;
}

void HGScrollBar::setOneStep(int step)
{
    d_func()->mBar.oneStep = step;
}

int HGScrollBar::oneStep() const
{
    return d_func()->mBar.oneStep;
}

int  HGScrollBar::setScrollInfo (HSCROLLINFO* lpsi, bool fRedraw)
{
    HSCROLLINFO *mysi = &(d_func()->mBar.scrollInfo);
    HSCROLLBAR *sbar = &(d_func()->mBar);

    if(!lpsi)
        return mysi->nPos;

    if (lpsi->fMask & SIF_RANGE) {
        mysi->nMin = lpsi->nMin;
        mysi->nMax = lpsi->nMax;
    }

    //The nPage member must specify a value from 0 to nMax - nMin +1.
    if (lpsi->fMask & SIF_PAGE) {
        int t = mysi->nMax - mysi->nMin + 1;
        mysi->nPage = qMin(qMax(0, lpsi->nPage), t);
    }

    //The nPos member must specify a value between nMin and nMax - max(nPage - 1, 0).
    if (lpsi->fMask & SIF_POS) {
        mysi->nPos = qMax(lpsi->nPos, mysi->nMin);
        mysi->nPos = qMin(mysi->nPos, mysi->nMax - qMax(mysi->nPage - 1, 0));
    }

    bool scrollvisible = true;
    if ((mysi->nPage > mysi->nMax) ||
            (mysi->nPage == mysi->nMax && mysi->nMax == 0) ||
            (mysi->nMax <= mysi->nMin))
        scrollvisible = false;

    if(scrollvisible != sbar->scrollVisible) {
        sbar->scrollVisible = scrollvisible;
        emit scrollVisible(scrollvisible);
    }

    d_func()->updateScroll(rect(),fRedraw);

    return mysi->nPos;
}

bool HGScrollBar::scrollInfo (HSCROLLINFO* lpsi)
{
    HSCROLLINFO *mysi = &(d_func()->mBar.scrollInfo);
    bool copied = false;

    if(!lpsi)
        return false;

    if(lpsi->fMask & SIF_PAGE) {
        lpsi->nPage = mysi->nPage;
        copied = true;
    }

    if(lpsi->fMask & SIF_POS) {
        lpsi->nPos = mysi->nPos;
        copied = true;
    }

    if(lpsi->fMask & SIF_TRACKPOS) {
        lpsi->nTrackPos = mysi->nTrackPos;
        copied = true;
    }

    if(lpsi->fMask & SIF_RANGE) {
        lpsi->nMin = mysi->nMin;
        lpsi->nMax = mysi->nMax;
        copied = true;
    }
    return copied;
}

int  HGScrollBar::setScrollPos(int nPos, bool fRedraw)
{
    HSCROLLINFO* mysi = &(d_func()->mBar.scrollInfo);

    int oldpos = mysi->nPos;
    mysi->nPos = qMax(nPos, mysi->nMin);
    mysi->nPos = qMin(mysi->nPos, mysi->nMax - qMax(mysi->nPage - 1, 0));

    if (oldpos != mysi->nPos)
        d_func()->updateScroll(rect(),fRedraw);

    return oldpos;
}

int  HGScrollBar::scrollPos(void) const
{
    return d_func()->mBar.scrollInfo.nPos;
}

bool HGScrollBar::scrollRange(int* min, int* max)
{
    if(!min || !max)
        return false;

    HSCROLLINFO* mysi = &(d_func()->mBar.scrollInfo);
    *min = mysi->nMin;
    *max = mysi->nMax;

    return true;
}

void HGScrollBar::setScrollRange(int min, int max, bool fRedraw)
{
    HSCROLLINFO si;
    si.fMask = SIF_RANGE;
    si.nMin = min;
    si.nMax = max;
    setScrollInfo(&si,fRedraw);
}

void HGScrollBar::setScrollPage(int page,bool fRedraw)
{
    HSCROLLINFO si;
    si.fMask = SIF_PAGE;
    si.nPage = page;
    setScrollInfo(&si,fRedraw);
}

bool HGScrollBar::isSliderTracking(void) const
{
    return d_func()->mBar.sliderTracking;
}

QRectF HGScrollBar::leftWorkingRect() const
{
    return d_func()->mBar.leftWorking;
}

QRectF HGScrollBar::sliderRect() const
{
    return d_func()->mBar.slider;
}

QRectF HGScrollBar::rightWorkingRect() const
{
    return d_func()->mBar.rightWorking;
}

int HGScrollBar::workingSize() const
{
    return d_func()->mBar.workingSize;
}

void HGScrollBar::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    // draw background
    HGWidget::paint(painter,option,widget);

    Q_D(HGScrollBar);
    if (d->mLeftArrowStyle)
        d->mLeftArrowStyle->draw(painter,d->mBar.leftArrow.toRect());

    if (d->mLeftWorkingStyle)
        d->mLeftWorkingStyle->draw(painter,d->mBar.leftWorking.toRect());

    if (d->mSliderStyle)
        d->mSliderStyle->draw(painter,d->mBar.slider.toRect());

    if (d->mRightWorkingStyle)
        d->mRightWorkingStyle->draw(painter,d->mBar.rightWorking.toRect());

    if (d->mRightArrowStyle)
        d->mRightArrowStyle->draw(painter,d->mBar.rightArrow.toRect());
}

QSizeF HGScrollBar::sizeHint(Qt::SizeHint which,const QSizeF &constraint) const
{
    Q_D(const HGScrollBar);
    QSizeF s;
    if (d->barType() == Qt::Horizontal)
        s = QSizeF(-1, d->mBar.scrollSize);
    else
        s = QSizeF(d->mBar.scrollSize, -1);

    switch (which)
    {
    case Qt::MinimumSize:
        return s;

    case Qt::MaximumSize:
        return s;

    default:
        return HGWidget::sizeHint(which, constraint);
    }
}

void HGScrollBar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGScrollBar);

    HSCROLLBAR *sbar = &(d->mBar);
    if (sbar->slider.contains(event->pos())) {
        if (sbar->scrollFlags.testFlag(SliderTracking)) {
            sbar->sliderTracking = true;
            sbar->sliderTrackingPos = sbar->scrollInfo.nPos;
            sbar->pressPos = event->pos();
        }
        emit sliderPressed();
        return;
    }

    if (sbar->scrollFlags.testFlag(HasArrow)) {
        if(sbar->leftArrow.contains(event->pos())) {
            d->setScrollPos(-1);
            d->startAction(AActionLeft);
            return;
        }
        else if(sbar->rightArrow.contains(event->pos())) {
            d->setScrollPos(1);
            d->startAction(AActionRight);
            return;
        }
    }

    if(sbar->scrollFlags.testFlag(WorkingClicked)) {
        if(sbar->leftWorking.contains(event->pos())) {
            d->setScrollPos(-sbar->oneStep);
            return;
        }
        else if(sbar->rightWorking.contains(event->pos())) {
            d->setScrollPos(sbar->oneStep);
            return;
        }
    }
}

void HGScrollBar::on_arrowAction()
{
    Q_D(HGScrollBar);
    if (d->mBar.arrowAction==AActionLeft) {
        if (d->mBar.mouseInArrow)
            d->setScrollPos(-1);
    }
    else if(d->mBar.arrowAction==AActionRight) {
        if (d->mBar.mouseInArrow)
            d->setScrollPos(1);
    }
}

void HGScrollBar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    Q_D(HGScrollBar);
    HSCROLLBAR *sbar = &(d->mBar);
    sbar->sliderTracking = false;
    d->stopAction();
}

void HGScrollBar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGScrollBar);

    HSCROLLBAR *sbar = &(d->mBar);
    if (!sbar->sliderTracking) {
        d->mouseInArrow(event->pos());
    }
    else {
        int pos = 0;
        int range = (sbar->scrollInfo.nMax - sbar->scrollInfo.nMin) - sbar->scrollInfo.nPage + 1;
        if (d->barType() == Qt::Horizontal) {
            int df = event->pos().x() - sbar->pressPos.x();
            pos = HGlobal::mulDiv(df,range,sbar->workingSize-sbar->slider.width());
        }
        else {
            int df = event->pos().y() - sbar->pressPos.y();
            pos = HGlobal::mulDiv(df,range,sbar->workingSize-sbar->slider.height());
        }
        sbar->scrollInfo.nTrackPos = sbar->sliderTrackingPos + pos;
        setScrollPos(sbar->scrollInfo.nTrackPos,true);
        emit sliderPositionChange(sbar->scrollInfo.nPos);
    }
}

void HGScrollBar::wheelEvent(QGraphicsSceneWheelEvent * event)
{
    HGWidget::wheelEvent(event);

    Q_D(HGScrollBar);
    if (event->delta()<= -120) {
        d->setScrollPos(d->mBar.oneStep);
    }
    else if(event->delta() >= 120) {
        d->setScrollPos(-d->mBar.oneStep);
    }
}

void HGScrollBar::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    HGWidget::hoverEnterEvent(event);
}

void HGScrollBar::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    HGWidget::hoverLeaveEvent(event);
    d_func()->mouseInArrow(event->pos());
}

void HGScrollBar::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    HGWidget::resizeEvent(event);

    Q_D(HGScrollBar);
    d->updateScroll(rect(),false);
}
