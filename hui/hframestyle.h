#ifndef HFRAMESTYLE_H
#define HFRAMESTYLE_H

#include "hbase.h"
#include <QObject>

class QResizeEvent;
class HGView;

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

    void setView(HGView* view);

    void setStyleId(const QLatin1String& id);
    QLatin1String styleId() const;

public:
    virtual qreal opacity() const;
    virtual void  init();
    virtual void  resizeEvent(QResizeEvent *event);
    virtual QRect calcClientRect(const QRect &frameRect) const;
    virtual bool  isAnimationEnabled() const;

#if defined(WIN32)
    virtual bool winEvent( MSG *message, long *result );
#endif //WIN32

protected:
    QLatin1String  mStyleId;
    HGView  *mView;
};

#endif // HFRAMESTYLE_H
