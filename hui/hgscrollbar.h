#ifndef HGSCROLLBAR_H
#define HGSCROLLBAR_H

#include "hgwidget.h"

#ifndef WIN32

#define SIF_UNK       0x00
#define SIF_PAGE      0x01
#define SIF_POS       0x02
#define SIF_TRACKPOS  0x04
#define SIF_RANGE     0x08

typedef struct tagHSCROLLINFO
{
    unsigned int    cbSize;
    unsigned int    fMask; //for SIF_XX
    int             nMin;  // = 0
    int             nMax;  //counts of all item
    int             nPage; //counts of visible item
    int             nPos;
    int             nTrackPos;
}HSCROLLINFO;

#else

typedef SCROLLINFO HSCROLLINFO;

#endif

class HGScrollBarPrivate;
class H_API HGScrollBar : public HGWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGScrollBar)
public:
    enum GScrollFlag
    {
        DisableBoth          = 0x0001,
        SliderAlwaysOff      = 0x0002,
        SliderTracking       = 0x0004,
        HasArrow             = 0x0008,
        WorkingClicked       = 0x0010
    };
    Q_ENUMS(GScrollFlag)
    Q_DECLARE_FLAGS(GScrollFlags, GScrollFlag)
    Q_FLAGS(GScrollFlags)

    Q_PROPERTY( GScrollFlags scrollFlag READ scrollFlag WRITE setScrollFlag)
    Q_PROPERTY( int minSliderSize READ minSliderSize WRITE setMinSliderSize)
    Q_PROPERTY( int maxSliderSize READ maxSliderSize WRITE setMaxSliderSize)
    Q_PROPERTY( int scrollSize READ scrollSize WRITE setScrollSize)
    Q_PROPERTY( int arrowSize READ arrowSize WRITE setArrowSize)
    Q_PROPERTY( int oneStep READ oneStep WRITE setOneStep)

public:
    HGScrollBar(Qt::Orientation barType,const HObjectInfo& objinfo, QGraphicsItem *parent=0);
    virtual ~HGScrollBar();

public:

    void setScrollFlag(const GScrollFlags& flags);
    GScrollFlags scrollFlag() const;

    void setMinSliderSize(int size);
    int  minSliderSize() const;

    void setMaxSliderSize(int size);
    int  maxSliderSize() const;

    /**parallel size (height of horz, width of vert)*/
    void setScrollSize(int size);
    int  scrollSize() const;

    void setArrowSize(int size);
    int  arrowSize() const;

    void setOneStep(int step);
    int oneStep() const;

    int  setScrollInfo (HSCROLLINFO* si, bool fRedraw);
    bool scrollInfo (HSCROLLINFO* si);

    Q_INVOKABLE int  setScrollPos(int nPos, bool fRedraw);
    Q_INVOKABLE int  scrollPos(void) const;

    Q_INVOKABLE void setScrollRange(int min, int max, bool fRedraw);
    Q_INVOKABLE bool scrollRange(int* min, int* max);

    Q_INVOKABLE void setScrollPage(int page,bool fRedraw);

    bool isSliderTracking(void) const;
    bool isScrollVisible() const;

protected:
    QRectF  leftWorkingRect() const;
    QRectF  sliderRect() const;
    QRectF  rightWorkingRect() const;
    int     workingSize() const;

signals:
    void sliderPressed();
    void sliderPositionChange(int position);
    void scrollVisible(bool);

private slots:
    void on_arrowAction();

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QSizeF sizeHint(Qt::SizeHint which,const QSizeF &constraint = QSizeF()) const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    friend class HGScrollBarPrivate;
};

#endif // HGSCROLLBAR_H
