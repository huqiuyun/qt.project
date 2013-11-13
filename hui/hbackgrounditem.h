#ifndef HBACKGROUNDITEM_H
#define HBACKGROUNDITEM_H

#include "hbase.h"
#include <QPixmap>
#include <QMargins>
#include <QPainter>

class HResourceMgr;
class HCssBackground;
class HCssObject;
class HBackgroundItemPrivate;

class H_API HBackgroundItem : public QObject, public HObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HBackgroundItem )
    Q_DISABLE_COPY( HBackgroundItem )
public:
    explicit HBackgroundItem(const HObjectInfo& objinfo, QObject *parent = 0);
    virtual ~HBackgroundItem();

    DECLARE_OBJECT_STATIC_CREATE(HBackgroundItem);
public:
    void setStyleId(const QLatin1String& styleid);
    QLatin1String styleId() const;

    bool setCss(QSharedPointer<HCssObject> obj);

    void setImagePath(const QString& path);
    QString imagePath() const;

    void setImage(const QPixmap& image);
    QPixmap image() const;

    void setColor(const QColor& rgb);
    QColor color() const;

    /** draw need margins */
    void setMargins(const QMargins& margins);
    QMargins margins() const;

    void setComposeMode(QPainter::CompositionMode composeMode);
    QPainter::CompositionMode composeMode()const;

    virtual void setColorizePolicy(qy::HColorizeFlag flag);
    qy::HColorizeFlag colorizePolicy() const;
protected:
    HCssBackground* css()  const;
public:
    virtual void draw(QPainter * painter, const QRect &rect);
    virtual void drawColor(QPainter* painter,const QRect& rect);

signals:
    /** @param type = 0, unk
     *              = 1, image change;
     *              = 2, color change;
     *              = 4, magrins change;
     *              = 8, composeMode change;
     *
    */
    void backgroundChanged(int type);

private slots:
    void on_colorChanged(const QColor& rgb);
    void on_cssStyle_changed(const QString &id);

protected:
    virtual void colorChanged(const QColor& rgb);

protected:
    HBackgroundItemPrivate* d_ptr;
    QPixmap mImage;
    HResourceMgr* mResMgr;
};

#endif // HBACKGROUNDITEM_H
