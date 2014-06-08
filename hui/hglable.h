#ifndef HGLABLE_H
#define HGLABLE_H

#include "hgwidget.h"

class HGLablePrivate;
class H_API HGLable : public HGWidget
{
    Q_OBJECT
    Q_DISABLE_COPY( HGLable )
    Q_DECLARE_PRIVATE( HGLable )

public:
    Q_PROPERTY( QString text READ text WRITE setText )
    Q_PROPERTY( Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment )
    Q_PROPERTY( QString link WRITE setLink READ link )
    Q_PROPERTY( bool acceptCursor READ acceptCursor WRITE setAcceptCursor)
    Q_PROPERTY( QSizeF borderSize READ borderSize WRITE setBorderSize)
    Q_PROPERTY( int fontSize WRITE setFontSize READ fontSize )
    Q_PROPERTY( bool underlineOnHover WRITE setUnderlineOnHover READ underlineOnHover )
    Q_PROPERTY( bool bold WRITE setBold READ bold )

public:
    explicit HGLable(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGLable();

    DECLARE_GITEM_STATIC_CREATE(HGLable);
public:
    QString text() const;
    void setText(const QString&);

    Qt::Alignment textAlignment()const;
    void setTextAlignment(Qt::Alignment m);

    bool acceptCursor() const;
    void setAcceptCursor( bool accept );

    QSizeF borderSize() const;
    void setBorderSize(const QSizeF& s);

    void setFontSize( int size );
    int fontSize() const;

    void setBold( bool enable );
    bool bold() const;

    void setLink( const QString& url );
    QString link() const;

    void setUnderlineOnHover( bool underlineOnHover );
    bool underlineOnHover() const;

protected:
    virtual int indexOfColor() const;
    virtual void on_itemStyleChanged();
    virtual void on_mousePressed();
    virtual void on_mouseReleased();
    virtual void on_keyPressed();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // HGLABLE_H
