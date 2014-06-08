#include "himagestyle.h"
#include "hresourcemgr.h"
#include "hstyle.h"
#include "hcore.h"
#include "hdraw.h"
#include "private/himagestyle_p.h"
#include <QPainter>


IMPLEMENT_OBJECT_STATIC_CREATE(HImageStyle)

void HImageStylePrivate::calcuTile()
{
    HDraw::cacluImageTile(mImage,mImageTile);
}

HImageStyle::HImageStyle(QObject *parent) :
    HBaseStyle(parent),
    d_ptr(new HImageStylePrivate()),
    mResMgr(HRESMGR)
{
    mObjType = USEOBJTYPE(HImageStyle);
}

HImageStyle::HImageStyle(const HObjectInfo& objinfo, QObject *parent) :
    HBaseStyle(objinfo,parent),
    d_ptr(new HImageStylePrivate()),
    mResMgr(HRESMGR)
{   
    //qDebug("HImageStyle styleid=%s",objinfo.mStyleId.data());
    mObjType = USEOBJTYPE(HImageStyle);
}

HImageStyle::~HImageStyle()
{
    delete d_ptr;
}

void HImageStyle::setImagePath(const QString& path)
{
    Q_D(HImageStyle);
    d->mImagePath = path;
    setImage(mResMgr->loadPixmap(path));
}

QString HImageStyle::imagePath() const
{
    return d_func()->mImagePath;
}

void HImageStyle::setImage(const QPixmap& image)
{
    Q_D(HImageStyle);
    d->mImage = image;
    //to do calculate tile
    d->calcuTile();
    emit typeChanged(HEnums::kChgImage);
}

QPixmap HImageStyle::image() const
{
    return d_func()->mImage;
}

QSize HImageStyle::imageSize() const
{
    Q_D(const HImageStyle);
    return d->mImage.isNull()?QSize():QSize(d->mImageTile.mWidth,d->mImageTile.mHeight);
}

void HImageStyle::setIndex(int index)
{
    d_func()->mIndex = index;
}

int HImageStyle::index() const
{
    return d_func()->mIndex;
}

void HImageStyle::setColor(const QColor& rgb)
{
    d_func()->mColor = rgb;
    emit typeChanged(HEnums::kChgColor);
}

QColor HImageStyle::color() const
{
    return d_func()->mColor;
}

void HImageStyle::setMargins(const QMargins& m)
{
    d_func()->mMargins = m;
}

QMargins HImageStyle::margins() const
{
    return d_func()->mMargins;
}

Qt::Alignment HImageStyle::alignment() const
{
    return d_func()->mAlignment;
}

void HImageStyle::setAlignment(Qt::Alignment align)
{
    d_func()->mAlignment = align;
}

bool HImageStyle::hasBrush() const
{
    return (d_func()->mBrush.style() != Qt::NoBrush);
}
QBrush HImageStyle::brush() const
{
    return d_func()->mBrush;
}

void HImageStyle::setBrush(const QBrush& brush)
{
    d_func()->mBrush = brush;
    emit typeChanged(HEnums::kChgBrush);
}

bool HImageStyle::sysTile() const
{
    return d_func()->mImageTile.mSys;
}

void HImageStyle::setSysTile(bool sys)
{
    d_func()->mImageTile.mSys = sys;
}

HImageStyle::GImageStyles HImageStyle::imageStyle() const
{
    return d_func()->mStyles;
}

void HImageStyle::setImageStyle(const HImageStyle::GImageStyles &style)
{
    Q_D(HImageStyle);
    d->mStyles = style;
}

HImageTile HImageStyle::tileImage() const
{
    return d_func()->mImageTile;
}

void HImageStyle::setImageTile(const HImageTile& t)
{
    d_func()->mImageTile = t;
}

void HImageStyle::copyTo(HBaseStyle* obj)
{
    Q_D(HImageStyle);
    HImageStyle* style = static_cast<HImageStyle*>(obj);
    if (!style) return ;

    style->setImagePath(d->mImagePath);
    style->setMargins(d->mMargins);
    style->setAlignment(d->mAlignment);
    style->setColor(d->mColor);
    style->setBrush(d->mBrush);
    style->setImageTile(d->mImageTile);
    style->setIndex(d->mIndex);
    style->setImageStyle(d->mStyles);

    HBaseStyle::copyTo(obj);
}

HBaseStyle* HImageStyle::clone()
{
    HImageStyle* style = new HImageStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}

void HImageStyle::draw(QPainter * painter, const QRect &rect)
{
    Q_D(HImageStyle);

    HDraw draw;
    if (d->mStyles.testFlag(ColorOnly) &&
            d->mColor.isValid()) {
        draw.paint(painter, rect, d->mColor, d->mMargins);
    }
    else if (d->mStyles.testFlag(BrushOnly) &&
             d->mBrush.style() != Qt::NoBrush) {
        draw.paint(painter,rect,d->mBrush,d->mMargins);
    }

    if (d->mStyles.testFlag(ImageOnly) &&
            !d->mImage.isNull()) {
        QSize si = imageSize();
        QRect rc(rect);
        if (d->mAlignment.testFlag(Qt::AlignRight)) {
            rc.setLeft(rect.right()-si.width());
        }
        else if(d->mAlignment.testFlag(Qt::AlignHCenter)) {
            rc.setLeft(rc.left()+(rect.width()-si.width())/2);
        }

        if(d->mAlignment.testFlag(Qt::AlignBottom)) {
            rc.setTop(rect.bottom()-si.height());
        }
        else if(d->mAlignment.testFlag(Qt::AlignVCenter)) {
            rc.setTop(rc.top()+(rect.height()-si.height())/2);
        }
        if (d->mAlignment.testFlag(Qt::AlignJustify)) {
            rc.setRight(rc.left()+si.width());
            rc.setBottom(rc.top()+si.height());
        }
        draw.paint(painter, rc, d->mImage, d->mMargins, d->mImageTile, d->mIndex);
    }
}

void HImageStyle::drawSizeHint(QPainter * painter, const QRect &rect)
{
    Q_D(HImageStyle);
    if (d->mStyles.testFlag(SizeHint)) {
        QPen old = painter->pen();
        painter->setPen(d->mColor);
        painter->drawRect(rect);
        painter->setPen(old);
    }
}

void HImageStyle::on_colorChanged(const QColor& rgb)
{
    colorChanged(rgb);
}

void HImageStyle::colorChanged(const QColor& rgb)
{
    Q_UNUSED(rgb);
    Q_D(HImageStyle);

    int type = 0;
    if (d->mImagePath.size()>1) {
        d->mImage = mResMgr->loadPixmap(d->mImagePath);
        d->calcuTile();
        type = HEnums::kChgImage;
    }
    if (d->mColor.isValid()) {
        type |= HEnums::kChgColor;
    }
    emit typeChanged(type);
}
