#ifndef HIMAGEStyle_H
#define HIMAGEStyle_H

#include "henums.h"
#include "hbasestyle.h"
#include <QPixmap>
#include <QMargins>
#include <QPainter>

class HResourceMgr;
class HImageStylePrivate;

class H_API HImageStyle : public HBaseStyle
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HImageStyle )
public:
    enum GImageStyle
    {
        ColorOnly   = 0x01,
        BrushOnly   = 0x02,
        ImageOnly   = 0x04,
        SizeHint    = 0x08
    };

    Q_ENUMS(GImageStyle);
    Q_DECLARE_FLAGS(GImageStyles, GImageStyle);
    Q_FLAGS(GImageStyles);

    Q_PROPERTY( QMargins margins READ margins WRITE setMargins )
    Q_PROPERTY( Qt::Alignment alignment READ alignment WRITE setAlignment )
    Q_PROPERTY( QString imagePath READ imagePath WRITE setImagePath )
    Q_PROPERTY( QColor color READ color WRITE setColor )
    Q_PROPERTY( QBrush brush READ brush WRITE setBrush )
    Q_PROPERTY( bool sysTile READ sysTile WRITE setSysTile )
    Q_PROPERTY( GImageStyles imageStyle READ imageStyle WRITE setImageStyle)
public:
    explicit HImageStyle(QObject *parent = 0);
    explicit HImageStyle(const HObjectInfo& objinfo, QObject *parent = 0);
    ~HImageStyle();

    DECLARE_OBJECT_STATIC_CREATE(HImageStyle);
public:

    void setImagePath(const QString& path);
    QString imagePath() const;

    void setImage(const QPixmap& image);
    QPixmap image() const;
    QSize imageSize() const;

    void setIndex(int index);
    int index() const;

    void setColor(const QColor& rgb);
    QColor color() const;

    bool hasBrush() const;
    QBrush brush() const;
    void setBrush(const QBrush& brush);

    /** draw need margins */
    void setMargins(const QMargins& margins);
    QMargins margins() const;

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    bool sysTile() const;
    void setSysTile(bool sys);

    GImageStyles imageStyle() const;
    void setImageStyle(const GImageStyles &style);

    HImageTile tileImage() const;
    void setImageTile(const HImageTile& t);
public:
    virtual HBaseStyle* clone();
    virtual void copyTo(HBaseStyle* obj);

    virtual void draw(QPainter * painter, const QRect &rect);

    /** for layout sizeHint */
    virtual void drawSizeHint(QPainter * painter, const QRect &rect);

private slots:
    void on_colorChanged(const QColor& rgb);

protected:
    virtual void colorChanged(const QColor& rgb);

protected:
    HImageStylePrivate* d_ptr;
    HResourceMgr* mResMgr;
};

#endif // HIMAGEStyle_H
