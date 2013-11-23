#ifndef HGView_H
#define HGView_H

#include "hbase.h"
#include "henums.h"
#include <QGraphicsView>

class HGViewPrivate;
class HFrameStyle;
class HGSceneStyle;
class HBackgroundStyle;
class HQLayoutStyle;
class HGWidget;
class QGraphicsItem;
class HStyle;

class H_API HGView : public QGraphicsView, public HObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HGView )
    Q_DISABLE_COPY( HGView )
public:
    Q_PROPERTY( QSize fixedSize WRITE setFixedSize )
    Q_PROPERTY( int fixedHeight WRITE setFixedHeight )
    Q_PROPERTY( int fixedWidth WRITE setFixedWidth )
    Q_PROPERTY( QSize resize WRITE resizeEx )
    Q_PROPERTY( bool isHGView READ isHGView)
public:
    explicit HGView(QWidget *parent = 0);
    explicit HGView(const HObjectInfo& objinfo, QWidget *parent = 0);
    ~HGView();

    DECLARE_GVIEW_STATIC_CREATE(HGView);
public:
    Q_INVOKABLE void installStyle(const HStyle* style);

    bool hasFrameStyle() const;
    void setFrameStyle(QSharedPointer<HFrameStyle> style/*new object*/);
    QSharedPointer<HFrameStyle> frameStyle() const;

    bool hasSceneStyle() const;
    void setSceneStyle(QSharedPointer<HGSceneStyle> style);
    QSharedPointer<HGSceneStyle> sceneStyle() const;

    bool hasBackgroundStyle() const;
    void setBackgroundStyle(QSharedPointer<HBackgroundStyle> style);
    QSharedPointer<HBackgroundStyle> backgroundStyle() const;

    bool hasLayoutStyle() const;
    void setLayoutStyle(QSharedPointer<HQLayoutStyle> style);
    QSharedPointer<HQLayoutStyle> layoutStyle() const;

    // layout functions
    HEnums::HLayoutType layoutType() const;

    /** add widget to owner layout */
    virtual int  addWidget(QWidget* widget);
    virtual int  insertWidget(QWidget* widget ,const HLayoutIndex& index);
    virtual bool removeWidget(QWidget* widget) ;

    //property
public:
    bool isHGView() const { return true;}
    void setFixedSize(const QSize &s);
    void setFixedHeight(int h);
    void setFixedWidth(int w);
    void resizeEx(const QSize &s);

    //HObject
protected:
    void doConstruct();

protected:
    virtual void construct(){}
    virtual void resizeEvent(QResizeEvent *event);
    virtual bool nativeEvent(const QByteArray & eventType, void * message, long * result);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
signals:
    void resized();

public slots:

private:
    friend class HFrameStyle;
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    HGViewPrivate* d_ptr;
};

#endif // HGView_H
