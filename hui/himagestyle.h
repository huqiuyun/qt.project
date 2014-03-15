#ifndef HBackgroundStyle_H
#define HBackgroundStyle_H

#include "henums.h"
#include "hbasestyle.h"
#include <QPixmap>
#include <QMargins>
#include <QPainter>

class HResourceMgr;
class HBackgroundStylePrivate;

class H_API HBackgroundStyle : public HBaseStyle
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HBackgroundStyle )

    Q_PROPERTY( QMargins margins READ margins WRITE setMargins )
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( QString imagePath READ imagePath WRITE setImagePath )
    Q_PROPERTY( QColor color READ color WRITE setColor )
    Q_PROPERTY( QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush )
    Q_PROPERTY( bool sysTile READ sysTile WRITE setSysTile )

public:
    explicit HBackgroundStyle(QObject *parent = 0);
    explicit HBackgroundStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    ~HBackgroundStyle();

    DECLARE_OBJECT_STATIC_CREATE(HBackgroundStyle);
public:

    void setImagePath(const QString& path);
    QString imagePath() const;

    void setImage(const QPixmap& image);
    QPixmap image() const;

    void setColor(const QColor& rgb);
    QColor color() const;
    void setColorized(const QColor& rgb);
    QColor colorized() const;

    /** draw need margins */
    void setMargins(const QMargins& margins);
    QMargins margins() const;

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    bool hasBackgroundBrush() const;
    QBrush backgroundBrush() const;
    void setBackgroundBrush(const QBrush& brush);

    bool sysTile() const;
    void setSysTile(bool sys);
    HImageTile tileImage() const;
    void setImageTile(const HImageTile& t);
public:
    virtual HBaseStyle* clone();
    virtual void copyTo(HBaseStyle* obj);
    virtual void draw(QPainter * painter, const QRect &rect, int index);
    virtual void drawColor(QPainter* painter,const QRect& rect, int index);
    virtual void drawImage(QPainter* painter,const QRect& rect, int index);

signals:
    /** @param type = 0, unk
     *              = 1, image change;
     *              = 2, color change;
     *              = 4, magrins change;
     *
    */
    void backgroundChanged(int type);

private slots:
    void on_colorChanged(const QColor& rgb);

protected:
    virtual void colorChanged(const QColor& rgb);

protected:
    HBackgroundStylePrivate* d_ptr;
    HResourceMgr* mResMgr;
};

#endif // HBackgroundStyle_H
