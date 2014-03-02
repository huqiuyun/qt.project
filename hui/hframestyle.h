#ifndef HFRAMESTYLE_H
#define HFRAMESTYLE_H

#include "hwidgetstyle.h"
#include <QObject>

class QResizeEvent;
class QWidget;

class H_API HFrameStyle : public HWidgetStyle
{
    Q_OBJECT
    Q_PROPERTY( Qt::WindowFlags windowFlags READ windowFlags WRITE setWindowFlags )
    Q_PROPERTY( QString styleSheet READ styleSheet WRITE setStyleSheet)
    Q_PROPERTY(	HClassInfo sceneStyle READ sceneStyle WRITE setSceneStyle)
    Q_PROPERTY(	QString windowAttribute READ windowAttribute WRITE setWindowAttribute)
public:
    explicit HFrameStyle(QObject *parent = 0);
    explicit HFrameStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    ~HFrameStyle();

    DECLARE_OBJECT_STATIC_CREATE(HFrameStyle);
public:
    void setWindowFlags(Qt::WindowFlags flags);
    Qt::WindowFlags windowFlags() const;

    bool hasStyleSheet() const;
    void setStyleSheet(const QString& sheet);
    QString styleSheet() const;

    bool hasSceneStyle() const;
    void setSceneStyle(const HClassInfo& cls);
    HClassInfo sceneStyle() const;

    QString windowAttribute() const;
    void setWindowAttribute(const QString& a);

    void setWindow(QWidget* view);

public:
    HBaseStyle* clone();
    void copyTo(HBaseStyle* obj);
    virtual void  init();
    virtual void  resizeEvent(QResizeEvent *event);
    virtual QRect calcClientRect(const QRect &frameRect) const;
    virtual bool  nativeEvent(const QByteArray & eventType, void * message, long * result);

private:
    void _setWindowAttribute();
protected:
    QWidget  *mWindow;
    Qt::WindowFlags mWinFlags;
    HClassInfo mSceneStyle;
    QString mStyleSheet;
    QString mWindowAttribute; // "int:0|int:1" @see QWidget::setAttribute
};

#endif // HFRAMESTYLE_H
