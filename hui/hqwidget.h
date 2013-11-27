#ifndef HQWIDGET_H
#define HQWIDGET_H

#include "hbase.h"
#include "henums.h"
#include <QWidget>

class HQWidgetPrivate;
class HFrameStyle;
class HBackgroundStyle;
class HQLayoutStyle;
class HStyle;
class HGWidget;

class H_API HQWidget : public QWidget, public HObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HQWidget)
    Q_PROPERTY( QSize fixedSize WRITE setFixedSize )
    Q_PROPERTY( int fixedHeight WRITE setFixedHeight )
    Q_PROPERTY( int fixedWidth WRITE setFixedWidth )
    Q_PROPERTY( QSize resize WRITE resizeEx )
    Q_PROPERTY( bool isHQWidget READ isHQWidget)
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )

public:
    explicit HQWidget(QWidget *parent = 0);
    explicit HQWidget(const HObjectInfo& objinfo, QWidget* parent = NULL);
    ~HQWidget();

    DECLARE_QWIDGET_STATIC_CREATE(HQWidget);
public:
    Q_INVOKABLE void installStyle(const HStyle* style);

    void setFrameStyle(QSharedPointer<HFrameStyle> style);
    QSharedPointer<HFrameStyle> frameStyle() const;

    void setLayoutStyle(QSharedPointer<HQLayoutStyle> style);
    QSharedPointer<HQLayoutStyle> layoutStyle() const;

    HEnums::HLayoutType layoutType() const;

    /** QGraphicsProxyWidget's parent */
    HGWidget* parentGWidget() const;

    /** add widget to owner layout */
    virtual int addWidget(QWidget* widget);
    virtual int insertWidget(QWidget* widget ,const HLayoutConf& conf);
    virtual bool removeWidget(QWidget* widget) ;

    //property
public:
    bool isHQWidget() const { return true;}
    void setFixedSize(const QSize &);
    void setFixedWidth(int w);
    void setFixedHeight(int h);
    void resizeEx(const QSize &s);

    /** the object is alignment in parent layout */
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);
protected:
    void doConstruct();
    virtual void construct(){}
    virtual void resizeEvent(QResizeEvent *event);
    virtual bool nativeEvent(const QByteArray & eventType, void * message, long * result);

signals:
    void resized();

protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    HQWidget(HQWidgetPrivate& dd,QWidget* parent);
    HQWidget(HQWidgetPrivate& dd,const HObjectInfo& objinfo,QWidget* parent);
    HQWidgetPrivate* d_ptr;
};

#endif // HQWIDGET_H
