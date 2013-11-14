#ifndef HFRAMESTYLE_H
#define HFRAMESTYLE_H

#include "hbase.h"
#include <QObject>

class QResizeEvent;
class HGView;
class HCssFrame;

class H_API HFrameStyle : public QObject, public HObject
{
    Q_OBJECT
    Q_DISABLE_COPY(HFrameStyle)
public:
    explicit HFrameStyle(QObject *parent = 0);
    explicit HFrameStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    virtual ~HFrameStyle();

    DECLARE_OBJECT_STATIC_CREATE(HFrameStyle);
public:
    void setStyleId(const QLatin1String& id);
    QLatin1String styleId() const;

protected:
    HCssFrame* css() const;

private:
    void setView(HGView* view);

public:
    virtual qreal opacity() const;
    virtual void  init();
    virtual void  resizeEvent(QResizeEvent *event);
    virtual QRect calcClientRect(const QRect &frameRect) const;
    virtual bool  isAnimationEnabled() const;
    virtual bool  nativeEvent(const QByteArray & eventType, void * message, long * result);
protected:
    friend class HGView;
    friend class HGViewPrivate;
    QLatin1String  mStyleId;
    HGView  *mView;
};

#endif // HFRAMESTYLE_H
