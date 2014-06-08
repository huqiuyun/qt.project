#ifndef HGANIMATION_H
#define HGANIMATION_H

#include "hgwidget.h"

class HGAnimationPrivate;

class H_API HGAnimation : public HGWidget
{
    Q_OBJECT
    Q_DISABLE_COPY( HGAnimation )
    Q_DECLARE_PRIVATE( HGAnimation )

    Q_PROPERTY(QString imagePath READ imagePath WRITE setImage)
    Q_PROPERTY(bool playLoop READ playLoop WRITE setPlayLoop)
    Q_PROPERTY(QSizeF imageScaleSize READ imageScaleSize WRITE setImageScaleSize)
public:
    explicit HGAnimation(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGAnimation();

    DECLARE_GITEM_STATIC_CREATE(HGAnimation);

public:
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void setPaused(bool b);

    void setImage( const QString &imageName );
    QString imagePath() const;

    bool playLoop() const;
    void setPlayLoop( bool isLoop );

    void setImageScaleSize( const QSizeF& size );
    QSizeF imageScaleSize( ) const;

private slots:
    void on_frameChanged ( int frameNumber );
    void on_finished();

protected:
    virtual void on_mousePressed();
    virtual void on_mouseReleased();
    virtual void on_keyPressed();
};

#endif // HGANIMATION_H
