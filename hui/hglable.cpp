#include "hglable.h"
#include "hcore.h"
#include "hstyle.h"
#include "henums.h"
#include "hfactory.h"
#include "hcolorstyle.h"
#include "private/hgwidget_p.h"
#include <QCursor>
#include <QMargins>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QKeyEvent>

class HGLablePrivate: public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGLablePrivate)
    Q_DECLARE_PUBLIC( HGLable )
public:
    HGLablePrivate():
        HGWidgetPrivate(),
        mUnderline(false),
        mAcceptCursor(false),
        mBorderSize(10,10),
        mTextAlign(Qt::AlignLeft|Qt::AlignVCenter)
    {
    }

    void onInitStyle(const HStyle* style)
    {
        HClassInfo colorcls = mWidgetStyle->childAt(QLatin1String("colorStyle"));
        if (colorcls.isValid()) {
            HCreateParam param;
            HColorStyle* back = static_cast<HColorStyle*>(HFACTORY->createObject(colorcls,q_ptr,param));
            mColorStyle = QSharedPointer<HColorStyle>(back);
            mColorStyle->backup(style);
        }
    }

    bool stateChanged()
    {
        bool update=false;
        bool color = mItemStyle.testFlag(HGLable::TextColorState)&&mColorStyle.data();
        if (color) {
            int index = q_func()->indexOfColor();
            mColorStyle->setCurrentColor(index);

            update = true;
        }
        if (update)
            q_ptr->update();

        return update;
    }

    bool autoCacluSize()
    {
        if (mItemStyle.testFlag(HGLable::AutoSized)) {
            QRectF brect = boundingRect();
            q_ptr->setFixedSize(QSizeF(brect.width(),brect.height())+mBorderSize);
            return true;
        }
        return false;
    }

    QRectF boundingRect() const
    {
        qreal  widthText=0;
        qreal  heightText=0;

        QFontMetrics metrics(q_ptr->font());
        widthText = metrics.width(mText);
        heightText = metrics.height();

        return QRectF(0, 0, widthText, heightText);
    }

    QColor textColor(const QColor& defColor) const
    {
       return (mColorStyle)?mColorStyle->currentColor(defColor):defColor;
    }

    QSharedPointer<HColorStyle> mColorStyle;
    bool   mUnderline;
    bool   mAcceptCursor;
    QSizeF mBorderSize;
    Qt::Alignment mTextAlign;
    QString  mText;
    QString  mLinkUrl;
};

IMPLEMENT_GITEM_STATIC_CREATE(HGLable,HGLable)
HGLable::HGLable(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGLablePrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGLable);
    connect(this,SIGNAL(enabledChanged()),SLOT(on_enabledChanged()));
}

HGLable::~HGLable()
{
}

QString HGLable::text() const
{
    return d_func()->mText;
}

void HGLable::setText(const QString& t)
{
    Q_D(HGLable);
    d->mText = t;
    d->autoCacluSize();
}

Qt::Alignment HGLable::textAlignment() const
{
    return d_func()->mTextAlign;
}

void HGLable::setTextAlignment(Qt::Alignment m)
{
    d_func()->mTextAlign = m;
}

bool HGLable::acceptCursor() const
{
    Q_D(const HGLable);
    return d->mAcceptCursor;
}

void HGLable::setAcceptCursor( bool accept )
{
    Q_D(HGLable);
    d->mAcceptCursor = accept;
    if (accept)
    {
        setCursor(Qt::PointingHandCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

QSizeF HGLable::borderSize() const
{
    Q_D(const HGLable);
    return d->mBorderSize;
}

void HGLable::setBorderSize(const QSizeF& s)
{
    Q_D(HGLable);
    d->mBorderSize = s;
}

void HGLable::setFontSize( int size )
{
    QFont f  = font();
    f.setPixelSize(size);
    setFont(f);
    if (!d_func()->autoCacluSize())
        update();
}

int HGLable::fontSize() const
{
    return font().pixelSize();
}

void HGLable::setBold( bool enable )
{
    QFont f = font();
    f.setBold(enable);
    setFont(f);
    if (!d_func()->autoCacluSize())
        update();
}

bool HGLable::bold() const
{
    return font().bold();
}

void HGLable::setLink( const QString& url )
{
    d_func()->mLinkUrl = url;
}

QString HGLable::link() const
{
    return d_func()->mLinkUrl;
}

void HGLable::setUnderlineOnHover( bool under )
{
    d_func()->mUnderline = under;
}

bool HGLable::underlineOnHover() const
{
    return d_func()->mUnderline;
}

int HGLable::indexOfColor() const
{
    int index = 0;
    Q_D(const HGLable);
    if (HEnums::testState(d->mState,HEnums::kStateDisable)) {
        index = 4;
    }
    else {
        if (HEnums::testState(d->mState,HEnums::kStateFoucs))
            index = 3;

        if (HEnums::testState(d->mState,HEnums::kStateOver))
            index = 1;

        if (HEnums::testState(d->mState,HEnums::kStatePressed)&&
                HEnums::testState(d->mState,HEnums::kStateOver))
            index = 2;
    }
    return index;
}

void HGLable::on_itemStyleChanged()
{
    d_func()->autoCacluSize();
}

void HGLable::on_mousePressed()
{
}

void HGLable::on_mouseReleased()
{
    on_clicked();
}

void HGLable::on_keyPressed()
{
    on_clicked();
}

void HGLable::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //to do draw background
    HGWidget::paint(painter,option,widget);

    Q_D(HGLable);

    QRect rc(option->rect);

    int xborder = d->mBorderSize.width()/2;
    int yborder = d->mBorderSize.height()/2;
    rc.adjust(xborder,yborder,-xborder,-yborder);

    QPen oldpen = painter->pen();
    QFont oldfont = painter->font();
    QColor color = d->textColor(option->palette.text().color());
    painter->setPen(color);
    painter->setFont(font());
    painter->drawText(rc, d->mTextAlign, d->mText);
    painter->setPen(oldpen);
    painter->setFont(oldfont);
}
