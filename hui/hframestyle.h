#ifndef HFRAMESTYLE_H
#define HFRAMESTYLE_H

#include "hwidgetstyle.h"
#include <QObject>

class QResizeEvent;
class QWidget;
class HFrameStyle;

class IHFrameStyleHandler
{
public:
    virtual ~IHFrameStyleHandler() {}

    virtual void  resizeEvent(HFrameStyle* style,QResizeEvent *event) = 0;
    virtual bool  nativeEvent(HFrameStyle* style,const QByteArray & eventType, void * message, long * result) = 0;
};

class H_API HFrameStyle : public HWidgetStyle
{
    Q_OBJECT
public:
    explicit HFrameStyle(QObject *parent = 0);
    explicit HFrameStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    ~HFrameStyle();

    DECLARE_OBJECT_STATIC_CREATE(HFrameStyle);
public:
    void setWindow(QWidget* view);
    QWidget* window() const;

    void setFrameStyleHandler(IHFrameStyleHandler* handler);

    HBaseStyle* clone();
    void copyTo(HBaseStyle* obj);

    virtual void  init();
    virtual void  resizeEvent(QResizeEvent *event);
    virtual bool  nativeEvent(const QByteArray & eventType, void * message, long * result);

protected:
    void onSetWindowAttribute();

protected:
    QWidget* mWindow;
    IHFrameStyleHandler* mHandler;
};

#endif // HFRAMESTYLE_H
