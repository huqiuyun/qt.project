#ifndef HFRAMESTYLE_H
#define HFRAMESTYLE_H

#include "hbasestyle.h"
#include <QObject>

class QResizeEvent;
class QWidget;

class H_API HFrameStyle : public HBaseStyle
{
    Q_OBJECT
    Q_PROPERTY( Qt::WindowFlags windowFlags READ windowFlags WRITE setWindowFlags )
    Q_PROPERTY( QString styleSheet READ styleSheet WRITE setStyleSheet)
    Q_PROPERTY(	HClassInfo backgroundStyle READ backgroundStyle WRITE setBackgroundStyle )
    Q_PROPERTY(	HClassInfo layoutStyle READ layoutStyle WRITE setLayoutStyle)
    Q_PROPERTY(	HClassInfo sceneStyle READ sceneStyle WRITE setSceneStyle)
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

    bool hasBackgroundStyle() const;
    void setBackgroundStyle(const HClassInfo& cls);
    HClassInfo backgroundStyle() const;

    bool hasLayoutStyle() const;
    void setLayoutStyle(const HClassInfo& cls);
    HClassInfo layoutStyle() const;

    bool hasSceneStyle() const;
    void setSceneStyle(const HClassInfo& cls);
    HClassInfo sceneStyle() const;

    void setWindow(QWidget* view);

public:
    virtual HBaseStyle* clone();
    void copyTo(HBaseStyle* obj);
    virtual void  init();
    virtual void  resizeEvent(QResizeEvent *event);
    virtual QRect calcClientRect(const QRect &frameRect) const;
    virtual bool  nativeEvent(const QByteArray & eventType, void * message, long * result);

protected:
    QWidget  *mWindow;
    Qt::WindowFlags mWinFlags;
    QString mStyleSheet;
    HClassInfo mBackgroundStyle;
    HClassInfo mLayoutStyle;
    HClassInfo mSceneStyle;
};

#endif // HFRAMESTYLE_H
