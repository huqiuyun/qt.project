#include "hgbutton.h"
#include "hcore.h"
#include "hstyle.h"
#include "henums.h"
#include "hfactory.h"
#include "hgroup.h"
#include "hcolorstyle.h"
#include "private/hgwidget_p.h"
#include <QCursor>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QKeyEvent>

class HGButtonPrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGButtonPrivate)
    Q_DECLARE_PUBLIC( HGButton )
public:
    HGButtonPrivate():
        HGWidgetPrivate(),
        mButtonType(HGButton::Pushable),
        mAcceptCursor(false),
        mIconSpacing(0),
        mTextSpacing(0),
        mBorderSize(10,10),
        mTextAlign(Qt::AlignCenter)
    {
        mItemStyle = HGWidget::TextOnly;
    }
    ~HGButtonPrivate()
    {
    }

    void onInitStyle(const HStyle* style)
    {
        HClassInfo iconcls = mWidgetStyle->childAt(QLatin1String("iconStyle"));
        if (iconcls.isValid()) {
            HCreateParam param;
            HImageStyle* back = static_cast<HImageStyle*>(HFACTORY->createObject(iconcls,q_ptr,param));
            mIconStyle = QSharedPointer<HImageStyle>(back);
            mIconStyle->backup(style);
        }

        HClassInfo colorcls = mWidgetStyle->childAt(QLatin1String("colorStyle"));
        if (colorcls.isValid()) {
            HCreateParam param;
            HColorStyle* back = static_cast<HColorStyle*>(HFACTORY->createObject(colorcls,q_ptr,param));
            mColorStyle = QSharedPointer<HColorStyle>(back);
            mColorStyle->backup(style);
        }
    }

    QSize iconSize() const
    {
        return mIconStyle?mIconStyle->imageSize():QSize();
    }

    bool stateChanged()
    {
        bool update = false;
        bool image = mItemStyle.testFlag(HGButton::ImageState)&&mBkgStyle.data();
        bool icon = mItemStyle.testFlag(HGButton::IconState)&&mIconStyle.data();
        bool color= mItemStyle.testFlag(HGButton::TextColorState)&&mColorStyle.data();
        if (image||icon) {
            int index = q_func()->indexOfImage();

            if (image)
                mBkgStyle->setIndex(index);

            if (icon)
                mIconStyle->setIndex(index);
            update = true;
        }
        if (color) {
            int index = q_func()->indexOfColor();
            mColorStyle->setCurrentColor(index);
        }

        if (update) q_ptr->update();

        return update;
    }

    void autoCacluSize()
    {
        if (mItemStyle.testFlag(HGButton::AutoSized)) {
            QRectF brect = boundingRect();
            q_ptr->setFixedSize(QSizeF(brect.width(),brect.height())+mBorderSize);
        }
    }

    QRectF boundingRect() const
    {
        qreal  widthText=0;
        qreal  heightText=0;
        qreal  totalWidth=0;
        qreal  totalHeight=0;
        QSizeF iconSi;

        qreal  externWidth = 0;
        qreal  externHeight = 0;

        if (mItemStyle.testFlag(HGButton::TextOnly)) {
            QFontMetrics metrics(q_ptr->font());
            widthText = metrics.width(mText);
            heightText = metrics.height();
            externWidth = mTextSpacing;
        }

        if (mItemStyle.testFlag(HGButton::IconOnly)) {
            iconSi = iconSize();
            externWidth += mIconSpacing;
        }

        if (mItemStyle.testFlag(HGButton::TextBesideIcon)) {
            externWidth = mTextSpacing+mIconSpacing;
            externHeight= 0;
            totalWidth  = widthText + iconSi.width();
            totalHeight = heightText > iconSi.height() ? heightText : iconSi.height();
        }
        else if(mItemStyle.testFlag(HGButton::TextUnderIcon)) {
            externHeight = mTextSpacing+mIconSpacing;
            externWidth = 0;
            totalWidth = widthText > iconSi.width() ? widthText : iconSi.width();
            totalHeight = heightText + iconSi.height();
        }
        else {
            totalWidth = widthText + iconSi.width();
            totalHeight = heightText + iconSi.height();
        }
        return QRectF(0, 0, totalWidth+externWidth, totalHeight+externHeight);
    }

    inline bool checkbox() const
    {
        return mButtonType == HGButton::Checkable;
    }

    inline bool radiobox() const
    {
        return mButtonType == HGButton::Radioable;
    }

    inline bool checked() const
    {
        return HEnums::testState(mState,HEnums::kStateChecked);
    }

    QColor textColor(const QColor& defColor) const
    {
       return (mColorStyle)?mColorStyle->currentColor(defColor):defColor;
    }

    QSharedPointer<HColorStyle> mColorStyle;
    QSharedPointer<HImageStyle> mIconStyle;
    HGButton::GButtonType	mButtonType;
    bool     mAcceptCursor;
    int      mIconSpacing;
    int      mTextSpacing;
    QSizeF   mBorderSize;
    Qt::Alignment mTextAlign;
    QString  mText;
    QString  mGroupId;
    QPointer<HGroup> mGroup;
};

IMPLEMENT_GITEM_STATIC_CREATE(HGButton,HGButton)

HGButton::HGButton(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGButtonPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGButton);
    setAcceptHoverEvents(true);
    setFocusPolicy(Qt::StrongFocus);
    setAcceptedMouseButtons(Qt::LeftButton);
    connect(this,SIGNAL(enabledChanged()),SLOT(on_enabledChanged()));
}

HGButton::~HGButton()
{
    _removeGroup();
}

QString HGButton::text() const
{
    return d_func()->mText;
}

void HGButton::setText(const QString& t)
{
    Q_D(HGButton);
    d->mText = t;
    d->autoCacluSize();
}

Qt::Alignment HGButton::textAlignment() const
{
    return d_func()->mTextAlign;
}

void HGButton::setTextAlignment(Qt::Alignment m)
{
    d_func()->mTextAlign = m;
}

HGButton::GButtonType HGButton::buttonType() const
{
    return d_func()->mButtonType;
}

void HGButton::setButtonType(HGButton::GButtonType type)
{
    Q_D(HGButton);
    bool rbox = d->radiobox();
    d->mButtonType = type;
    if (rbox)
    {
        _removeGroup();
    }
    else
    {//remove
        _addGroup();
    }
}

void HGButton::setIconStyle(QSharedPointer<HImageStyle> style)
{
    Q_D(HGButton);
    d->mIconStyle = style;
    d->autoCacluSize();
}

QSharedPointer<HImageStyle> HGButton::iconStyle() const
{
    return d_func()->mIconStyle;
}

bool HGButton::checked() const
{
    return d_func()->checked();
}

void HGButton::setChecked(bool isChecked)
{
    Q_D(HGButton);
    if (d->checkbox() || d->radiobox()) {
        if (isChecked) {
            if(!HEnums::testState(d->mState,HEnums::kStateChecked)) {
                d->mState |= HEnums::kStateChecked;
                d->stateChanged();
                emit stateChanged();
            }
        }
        else if(HEnums::testState(d->mState,HEnums::kStateChecked)) {
            d->mState &= ~HEnums::kStateChecked;
            d->stateChanged();
            emit stateChanged();
        }
    }
}

bool HGButton::acceptCursor() const
{
    Q_D(const HGButton);
    return d->mAcceptCursor;
}

void HGButton::setAcceptCursor( bool accept )
{
    Q_D(HGButton);
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

QSizeF HGButton::borderSize() const
{
    Q_D(const HGButton);
    return d->mBorderSize;
}

void HGButton::setBorderSize(const QSizeF& s)
{
    Q_D(HGButton);
    d->mBorderSize = s;
}

int HGButton::textSpacing() const
{
    return d_func()->mTextSpacing;
}

void HGButton::setTextSpacing(int spacing)
{
    d_func()->mTextSpacing = spacing;
}

int HGButton::iconSpacing() const
{
    return d_func()->mIconSpacing;
}

void HGButton::setIconSpacing(int spacing)
{
    d_func()->mIconSpacing = spacing;
}

QString HGButton::groupId() const
{
    return d_func()->mGroupId;
}

void HGButton::setGroupId(const QString& gid)
{
    d_func()->mGroupId = gid;
    _addGroup();
}

int HGButton::indexOfImage() const
{
    Q_D(const HGButton);
    int index = 0;
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

int HGButton::indexOfColor() const
{
    Q_D(const HGButton);

    int index = 0;
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

void HGButton::on_itemStyleChanged()
{
    Q_D(HGButton);
    d->autoCacluSize();
}

void HGButton::on_mousePressed()
{
    Q_D(HGButton);
    if (d->checkbox() || d->radiobox()) {
        setChecked(!checked());
        on_clicked();
    }
}

void HGButton::on_mouseReleased()
{
    Q_D(HGButton);
    if (!d->checkbox() && !d->radiobox())
        on_clicked();
}

void HGButton::on_keyPressed()
{
    setChecked(!checked());
    on_clicked();
}

void HGButton::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //to do draw background
    HGWidget::paint(painter,option,widget);

    Q_D(HGButton);

    QRect rc(option->rect);

    int xborder = d->mBorderSize.width()/2;
    int yborder = d->mBorderSize.height()/2;
    rc.adjust(xborder,yborder,-xborder,-yborder);

    QSize iconSi = d->iconSize();
    QRect iconrc = QRect(rc.left(),rc.top(),0,0);

    bool beside = d->mItemStyle.testFlag(TextBesideIcon);
    bool under = d->mItemStyle.testFlag(TextUnderIcon);

    if(d->mItemStyle.testFlag(IconOnly)) {

        if (under) {
            iconrc = QRect(rc.topLeft(),QSize(rc.width(),iconSi.height()));
            iconrc.adjust(0,d->mIconSpacing,0,0);
        }
        else if(beside) {
            iconrc = QRect(rc.topLeft(),QSize(iconSi.width(),rc.height()));
            iconrc.adjust(d->mIconSpacing,0,0,0);
        }
        else {//normal
            iconrc = QRect(rc.topLeft(),QSize(iconSi.width(),rc.height()));
            iconrc.adjust(d->mIconSpacing,0,0,0);
        }
        if (d->mIconStyle)
            d->mIconStyle->draw(painter,iconrc);
    }

    if(d->mItemStyle.testFlag(TextOnly)) {
        QRect textrc;
        if (under) {
            textrc=QRect(iconrc.bottomLeft(),QSize(rc.width(),rc.height()-iconSi.height()));
            textrc.adjust(0,d->mTextSpacing,0,0);
        }
        else if (beside) {
            textrc=QRect(iconrc.topRight(),QSize(rc.width()-iconSi.width(),rc.height()));
            textrc.adjust(d->mTextSpacing,0,0,0);
        }
        else{//normal
            textrc=QRect(iconrc.topRight(),QSize(rc.width()-iconSi.width(),rc.height()));
            textrc.adjust(d->mTextSpacing,0,0,0);
        }
        QPen oldpen = painter->pen();
        QFont oldfont = painter->font();
        painter->setPen(d->textColor(option->palette.text().color()));
        painter->setFont(font());
        painter->drawText(textrc, d->mTextAlign, d->mText);
        painter->setPen(oldpen);
        painter->setFont(oldfont);
    }
}

void HGButton::_addGroup()
{
    Q_D(HGButton);
    if (!d->radiobox())
        return ;

    if (d->mGroupId.size()==0)
        return ;

    if (!d->mGroup) {
        d->mGroup = parent()->findChild<HGroup*>(d->mGroupId);
    }
    if (d->mGroup)
        d->mGroup->addButton(d->mGroupId,this);
}

void HGButton::_removeGroup()
{
    Q_D(HGButton);
    if (d->mGroup)
        d->mGroup->removeButton(d->mGroupId,this);
}
