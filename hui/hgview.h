#ifndef HGView_H
#define HGView_H

#include "hbase.h"
#include <QGraphicsView>

class HGViewPrivate;
class HFrameStyle;
class HGWidget;
class HCssFrame;
class HCssObject;
class HBackgroundItem;

class H_API HGView : public QGraphicsView, public HObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HGView )
    Q_DISABLE_COPY( HGView )
public:
    explicit HGView(QWidget *parent = 0);
    explicit HGView(const HObjectInfo& objinfo, QWidget *parent = 0);
    ~HGView();

    DECLARE_GVIEW_STATIC_CREATE(HGView);
public:
    bool setCss(QSharedPointer<HCssObject> obj);

    void setFrameStyle(HFrameStyle* style/*new object*/);
    HFrameStyle* frameStyle() const;

    HGWidget* clientWidget() const;

    // next layout functions
    qy::HLayoutType layoutType() const;
    void setLayout(qy::HLayoutType type);

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set alignment in parent layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    /** set per child item space in owner layout */
    void setSpacing(int s);

protected:
    HCssFrame* css()  const;

    //HObject
protected:
    void doConstruct();

protected:
    virtual void construct(){}
    virtual void resizeEvent(QResizeEvent *event);
    virtual bool nativeEvent(const QByteArray & eventType, void * message, long * result);
signals:
    void resized();

public slots:

private:
    friend class HFrameStyle;
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    HGViewPrivate* d_ptr;
};

#endif // HGView_H
