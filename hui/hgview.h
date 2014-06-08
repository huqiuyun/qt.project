#ifndef HGView_H
#define HGView_H

#include "hbase.h"
#include "henums.h"
#include <QGraphicsView>

class HGViewPrivate;
class HFrameStyle;
class HGSceneItem;
class HImageStyle;
class HQLayout;
class HGWidget;
class QWidget;
class QGraphicsItem;
class HStyle;
class HLayoutConfig;

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
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( int indexOfBkgImage READ indexOfBkgImage WRITE setIndexOfBkgmage )
public:
    explicit HGView(const HObjectInfo& objinfo, QWidget *parent = 0);
    ~HGView();

    DECLARE_GVIEW_STATIC_CREATE(HGView);
public:
    Q_INVOKABLE void installStyle(const HStyle* style);
    Q_INVOKABLE void initFontStyle(const char* styleid,const HStyle* style=NULL);

    void setFrameStyle(QSharedPointer<HFrameStyle> style/*new object*/);
    QSharedPointer<HFrameStyle> frameStyle() const;

    void setBackgroundStyle(QSharedPointer<HImageStyle> style);
    QSharedPointer<HImageStyle> backgroundStyle() const;

    void setSceneItem(QSharedPointer<HGSceneItem> style);
    QSharedPointer<HGSceneItem> sceneItem() const;

    void setLayout(HQLayout* l);
    HQLayout* layout() const;

    // layout functions
    HEnums::HLayoutType layoutType() const;

    /** QGraphicsProxyWidget's parent */
    HGWidget* parentGWidget() const;

    /** find HGWidget from scene */
    HGWidget* rootWidget() const;
    HGWidget* widgetAt(int index) const;
    HGWidget* widgetOf(const QString& name) const;

    /** add widget to owner layout */
    virtual int  addWidget(QWidget* widget);
    virtual int  insertWidget(QWidget* widget ,const HLayoutConfig& conf);
    virtual bool removeWidget(QWidget* widget) ;

    virtual bool addChildWidget(QWidget* widget ,const HLayoutConfig& conf);
    virtual void removeChildWidget(QWidget* widget);

    //property
public:
    bool isHGView() const { return true;}
    void setFixedSize(const QSize &s);
    void setFixedHeight(int h);
    void setFixedWidth(int w);
    void resizeEx(const QSize &s);

    /** the object is alignment in parent layout */
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    void setIndexOfBkgmage(int index);
    int indexOfBkgImage() const;
    virtual QRect rectOfBackgroundImage() const;
    //HObject
protected:
    virtual void construct();
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
