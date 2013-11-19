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
    void setFrameStyle(QSharedPointer<HFrameStyle> style/*new object*/);
    QSharedPointer<HFrameStyle> frameStyle() const;

    void setSceneStyle(QSharedPointer<HGSceneStyle> style);
    QSharedPointer<HGSceneStyle> sceneStyle() const;

    void setBackgroundStyle(QSharedPointer<HBackgroundStyle> style);
    QSharedPointer<HBackgroundStyle> backgroundStyle() const;

    void setLayoutStyle(QSharedPointer<HQLayoutStyle> style);
    QSharedPointer<HQLayoutStyle> layoutStyle() const;

    // next layout functions
    HEnums::HLayoutType layoutType() const;

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
