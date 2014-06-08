#ifndef HGBUTTON_H
#define HGBUTTON_H

#include "hgwidget.h"

class HGButtonPrivate;
class HFontStyle;
class HImageStyle;

class H_API HGButton : public HGWidget
{
    Q_OBJECT
    Q_DISABLE_COPY( HGButton )
    Q_DECLARE_PRIVATE( HGButton )

public:
    enum GButtonType
    {
        Pushable             = 0x0000, //push button
        Checkable            = 0x0001, //check button
        Radioable            = 0x0002 //radio button
    };

    Q_ENUMS(GButtonType)

    Q_PROPERTY( QString text READ text WRITE setText )
    Q_PROPERTY( Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment )
    Q_PROPERTY( GButtonType buttonType READ buttonType WRITE setButtonType)
    Q_PROPERTY( bool checked READ checked WRITE setChecked)
    Q_PROPERTY( bool acceptCursor READ acceptCursor WRITE setAcceptCursor)
    Q_PROPERTY( QSizeF borderSize READ borderSize WRITE setBorderSize)
    Q_PROPERTY( int textSpacing READ textSpacing WRITE setTextSpacing)
    Q_PROPERTY( int iconSpacing READ iconSpacing WRITE setIconSpacing)
    Q_PROPERTY( QString groupId READ groupId WRITE setGroupId)
public:
    explicit HGButton(const HObjectInfo& objinfo, QGraphicsItem* parent = NULL);
    ~HGButton();

    DECLARE_GITEM_STATIC_CREATE(HGButton);
public:
    QString text() const;
    void setText(const QString&);

    Qt::Alignment textAlignment()const;
    void setTextAlignment(Qt::Alignment m);

    GButtonType buttonType() const;
    void setButtonType(GButtonType type);

    //for checkbox OR radiobox
    bool checked() const;
    void setChecked(bool isChecked);

    bool acceptCursor() const;
    void setAcceptCursor( bool accept );

    QSizeF borderSize() const;
    void setBorderSize(const QSizeF& s);

    int textSpacing() const;
    void setTextSpacing(int spacing);

    int iconSpacing() const;
    void setIconSpacing(int spacing);

    QString groupId() const;
    void setGroupId(const QString& );

    void setIconStyle(QSharedPointer<HImageStyle> style);
    QSharedPointer<HImageStyle> iconStyle() const;

protected:
    virtual int indexOfImage() const;
    virtual int indexOfColor() const;
    virtual void on_itemStyleChanged();
    virtual void on_mousePressed();
    virtual void on_mouseReleased();
    virtual void on_keyPressed();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
private:
    // for radio button
    void _addGroup();
    void _removeGroup();
};

#endif // HGBUTTON_H
