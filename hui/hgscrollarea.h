#ifndef HGSCROLLAREA_H
#define HGSCROLLAREA_H

#include "hgwidget.h"

class HGScrollBar;
class HGScrollAreaPrivate;

class H_API HGScrollArea : public HGWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HGScrollArea )
    Q_PROPERTY( Qt::ScrollBarPolicy horizontalScrollBarPolicy READ horizontalScrollBarPolicy WRITE setHorizontalScrollBarPolicy)
    Q_PROPERTY( Qt::ScrollBarPolicy verticalScrollBarPolicy READ verticalScrollBarPolicy WRITE setVerticalScrollBarPolicy)
public:

    explicit HGScrollArea(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGScrollArea();

    DECLARE_GITEM_STATIC_CREATE(HGScrollArea);
public:

    void setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy policy);
    Qt::ScrollBarPolicy horizontalScrollBarPolicy() const;

    void setVerticalScrollBarPolicy(Qt::ScrollBarPolicy policy);
    Qt::ScrollBarPolicy verticalScrollBarPolicy() const;

    QGraphicsWidget *viewport() const;
    void setViewport(QGraphicsWidget *viewport);

    HGScrollBar *verticalScrollBar() const;
    HGScrollBar *horizontalScrollBar() const;

signals:

    void viewportChanged(QGraphicsWidget *viewport);

protected:

    virtual bool event(QEvent *e);
    virtual void scrollContentsBy(qreal dx, qreal dy);

private slots:

    void verticalScrollStart();
    void verticalScroll(int);
    void verticalScrollVisible(bool);

    void horizontalScrollStart();
    void horizontalScroll(int);
    void horizontalScrollVisible(bool);
private:
    void adjustScrollBars();

protected:
    HGScrollArea(HGScrollAreaPrivate& dd,const HObjectInfo& objinfo,QGraphicsItem* parent);
};

#endif // HGSCROLLAREA_H
