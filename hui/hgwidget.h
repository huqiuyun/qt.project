#ifndef HGWIDGET_H
#define HGWIDGET_H

#include "hbase.h"
#include "henums.h"
#include <QMargins>
#include <QGraphicsWidget>

class HGWidgetPrivate;
class HImageStyle;
class HGLayout;
class HLayoutConfig;
class HGWidgetStyle;
class HStyle;
class HGProxyWidget;
class QGraphicsLayoutItem;
class QWidget;

class H_API HGWidget : public QGraphicsWidget, public HObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HGWidget)
    Q_DECLARE_PRIVATE(HGWidget)

public:
    enum ItemStyle
    {
        GUnk                 = 0,
        IconOnly             = 0x0001,
        TextOnly             = 0x0002,
        ImageState           = 0x0004, //状态变化时,引起image图索引变化
        IconState            = 0x0008, //状态变化时,引起icon图索引变化
        TextBesideIcon       = 0x0013, // |IconOnly|TextOnly
        TextUnderIcon        = 0x0023, // |IconOnly|TextOnly
        TextColorState       = 0x0040, //状态变化时,引起文字颜色变化
        KeyEnterClicked      = 0x0080,
        KeyReturnClicked     = 0x0100,
        KeySpaceClicked      = 0x0200,
        KeyClicked           = KeyEnterClicked|KeyReturnClicked|KeySpaceClicked,
        AutoSized            = 0x2000  //根据文本自动计算尺寸
    };

    Q_ENUMS(ItemStyle)
    Q_DECLARE_FLAGS(ItemStyles, ItemStyle)
    Q_FLAGS(ItemStyles)

    Q_PROPERTY( ItemStyles itemStyle READ itemStyle WRITE setItemStyle)
    Q_PROPERTY( int height READ height WRITE setHeight )
    Q_PROPERTY( int width READ width WRITE setWidth )
    Q_PROPERTY( QSizeF fixedSize READ fixedSize WRITE setFixedSize )
    Q_PROPERTY( int fixedHeight READ fixedHeight WRITE setFixedHeight )
    Q_PROPERTY( int fixedWidth READ fixedWidth WRITE setFixedWidth )
    Q_PROPERTY( bool isHGWidget READ isHGWidget)
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( int indexOfBkgImage READ indexOfBkgImage WRITE setIndexOfBkgmage )
    Q_PROPERTY( int openGItemFlag WRITE openGItemFlag)
    Q_PROPERTY( int closeGItemFlag WRITE closeGItemFlag)
    Q_PROPERTY( Qt::MouseButtons acceptedMouseButtons READ acceptedMouseButtons WRITE setAcceptedMouseButtons)
    Q_PROPERTY( bool acceptHoverEvents READ acceptHoverEvents WRITE setAcceptHoverEvents)
    Q_PROPERTY( bool acceptTouchEvents READ acceptTouchEvents WRITE setAcceptTouchEvents)
    Q_PROPERTY( QString toolTip READ toolTip WRITE setToolTip)
    Q_PROPERTY( QString statisticsId READ statisticsId WRITE setStatisticsId)

public:
    explicit HGWidget(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGWidget();

    DECLARE_GITEM_STATIC_CREATE(HGWidget);
public:
    bool isHGWidget() const { return true; }

    void setWidgetStyle(QSharedPointer<HGWidgetStyle> style);
    QSharedPointer<HGWidgetStyle> widgetStyle() const;

    void setBackgroundStyle(QSharedPointer<HImageStyle> style);
    QSharedPointer<HImageStyle> backgroundStyle() const;

    void setLayout(HGLayout* l);
    HGLayout* layout() const;

    HEnums::HLayoutType layoutType() const;

    Q_INVOKABLE virtual void installStyle(const HStyle* style);
    Q_INVOKABLE virtual void initFontStyle(const char* styleid,const HStyle* style=NULL);
    Q_INVOKABLE virtual void initialize();

    /** add item to owner layout */
    virtual int  addGItem(QGraphicsLayoutItem* item);
    virtual int  insertGItem(QGraphicsLayoutItem* item, const HLayoutConfig& conf);
    virtual bool removeGItem(QGraphicsLayoutItem* item);

    virtual int  addGWidget(QGraphicsWidget* item);
    virtual int  insertGWidget(QGraphicsWidget* item, const HLayoutConfig& conf);
    virtual bool removeGWidget(QGraphicsWidget* item);

    /** add widget to owner layout */
    virtual int  addWidget(QWidget* widget);
    virtual int  insertWidget(QWidget* widget ,const HLayoutConfig& conf);
    virtual bool removeWidget(QWidget* widget);

    virtual bool addChildGWidget(QGraphicsWidget* item, const HLayoutConfig& conf);
    virtual void removeChildGWidget(QGraphicsWidget* item);

    /** find QWidget from proxy widget */
    QWidget* qwidgetOf(const QString& name);
    template<class T>
    T findWidget(const QString& name) {
        return qobject_cast<T>(qwidgetOf(name));
    }
    // property
public:
    ItemStyles itemStyle() const;
    void setItemStyle(const ItemStyles &style);

    int height() const;
    void setHeight(int h);

    int width() const;
    void setWidth(int w);

    void setFixedSize(const QSizeF &s);
    QSizeF fixedSize() const;

    void setFixedHeight(int h);
    int fixedHeight() const;

    int fixedWidth() const;
    void setFixedWidth(int w);

    void setIndexOfBkgmage(int index);
    int indexOfBkgImage() const;

    void setToolTip(const QString& tip);
    QString toolTip() const;

    void openGItemFlag(int flag);
    void closeGItemFlag(int flag);

    void setStatisticsId(const QString& id);
    QString statisticsId() const;

    Qt::MouseButtons acceptedMouseButtons() const;
    void setAcceptedMouseButtons(Qt::MouseButtons buttons);
    bool acceptHoverEvents() const;
    void setAcceptHoverEvents(bool enabled);
    bool acceptTouchEvents() const;
    void setAcceptTouchEvents(bool enabled);

    /** the object is alignment in parent layout */
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

signals:
    void clicked();
    void pressed(const QPointF &point);
    void released(const QPointF &point);

    void hoverEnter(const QPointF &point);
    void hoverLeave(const QPointF &point);

    void focusIn();
    void focusOut();

    void stateChanged();

protected:
    virtual void construct();
    virtual HGProxyWidget* createProxyWidget(const HClassInfo& info);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void resizeEvent(QGraphicsSceneResizeEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mousePressEvent (QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);
    void keyPressEvent(QKeyEvent*);
protected slots:
    virtual void on_itemStyleChanged();
    virtual void on_mousePressed();
    virtual void on_mouseReleased();
    virtual void on_keyPressed();
    virtual void on_enabledChanged();
    virtual void on_clicked();
protected:
    template<class OBJ> friend OBJ* hDoConstructT(OBJ *);
    HGWidget(HGWidgetPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent);
    HGWidgetPrivate* d_ptr;
};

#endif // HGWIDGET_H
