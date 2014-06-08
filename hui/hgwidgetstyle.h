#ifndef HGWIDGETSTYLE_H
#define HGWIDGETSTYLE_H

#include "hwidgetstyle.h"

class QGraphicsWidget;

class H_API HGWidgetStyle : public HWidgetStyle
{
    Q_OBJECT
    Q_PROPERTY(QMargins windowFrameMargins READ windowFrameMargins WRITE setWindowFrameMargins)
    Q_PROPERTY(QMargins contentsMargins READ contentsMargins WRITE setContentsMargins)
public:
    explicit HGWidgetStyle(QObject *parent = 0);
    explicit HGWidgetStyle(const HObjectInfo& objinfo, QObject *parent = 0);

    DECLARE_OBJECT_STATIC_CREATE(HGWidgetStyle);
public:
    void setWidget(QGraphicsWidget* widget);

    virtual void init();

    HBaseStyle* clone();
    void copyTo(HBaseStyle* obj);
    //property
public:
    QMargins windowFrameMargins() const;
    void setWindowFrameMargins(const QMargins& m);

    QMargins contentsMargins() const;
    void setContentsMargins(const QMargins& m);
protected:
    void onSetWindowAttribute();

protected:
    QGraphicsWidget *mWidget;
    QMargins mFrameMargins; //setWindowFrameMargins
    QMargins mContentsMargins;//setContentsMargins
};

#endif // HGWIDGETSTYLE_H
