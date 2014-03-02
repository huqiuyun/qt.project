#include "HBackgroundStyle.h"
#include "hresourcemgr.h"
#include "hstyle.h"
#include "hcore.h"
#include "hdraw.h"
#include "private/hbackgroundstyle_p.h"
#include <QPainter>


IMPLEMENT_OBJECT_STATIC_CREATE(HBackgroundStyle)

void HBackgroundStylePrivate::calcuTile()
{
    HDraw::cacluImageTile(mImage,mImageTile);
}

HBackgroundStyle::HBackgroundStyle(QObject *parent) :
    HBaseStyle(parent),
    d_ptr(new HBackgroundStylePrivate()),
    mResMgr(HRESMGR)
{
    mObjType = USEOBJTYPE(HBackgroundStyle);
}

HBackgroundStyle::HBackgroundStyle(const HObjectInfo& objinfo, QObject *parent) :
    HBaseStyle(objinfo,parent),
    d_ptr(new HBackgroundStylePrivate()),
    mResMgr(HRESMGR)
{   
    mObjType = USEOBJTYPE(HBackgroundStyle);
}

HBackgroundStyle::~HBackgroundStyle()
{
    delete d_ptr;
}

void HBackgroundStyle::setImagePath(const QString& path)
{
    Q_D(HBackgroundStyle);
    d->mImagePath = path;
    setImage(mResMgr->loadPixmap(path));
}

QString HBackgroundStyle::imagePath() const
{
    return d_func()->mImagePath;
}

void HBackgroundStyle::setImage(const QPixmap& image)
{
    Q_D(HBackgroundStyle);
    d->mImage = image;
    //to do calculate tile
    d->calcuTile();
    emit backgroundChanged(0);
}

 QPixmap HBackgroundStyle::image() const
 {
     return d_func()->mImage;
 }

void HBackgroundStyle::setColor(const QColor& rgb)
{
    d_func()->mColor = rgb;
    emit backgroundChanged(1);
}

QColor HBackgroundStyle::color() const
{
    return d_func()->mColor;
}

void HBackgroundStyle::setColorized(const QColor& rgb)
{
    d_func()->mColorized = rgb;
}

QColor HBackgroundStyle::colorized() const
{
    return d_func()->mColorized;
}

void HBackgroundStyle::setMargins(const QMargins& m)
{
    d_func()->mMargins = m;
}

QMargins HBackgroundStyle::margins() const
{
    return d_func()->mMargins;
}

Qt::Alignment HBackgroundStyle::alignment() const
{
    return d_func()->mAlignment;
}

void HBackgroundStyle::setAlignment(Qt::Alignment align)
{
    d_func()->mAlignment = align;
}

bool HBackgroundStyle::hasBackgroundBrush() const
{
    return (d_func()->mBackgroundBrush.style() != Qt::NoBrush);
}
QBrush HBackgroundStyle::backgroundBrush() const
{
    return d_func()->mBackgroundBrush;
}

void HBackgroundStyle::setBackgroundBrush(const QBrush& brush)
{
    d_func()->mBackgroundBrush = brush;
}


bool HBackgroundStyle::sysTile() const
{
    return d_func()->mImageTile.mSys;
}

void HBackgroundStyle::setSysTile(bool sys)
{
    d_func()->mImageTile.mSys = sys;
}

HImageTile HBackgroundStyle::tileImage() const
{
    return d_func()->mImageTile;
}

void HBackgroundStyle::setImageTile(const HImageTile& t)
{
    d_func()->mImageTile = t;
}

void HBackgroundStyle::copyTo(HBaseStyle* obj)
{
    Q_D(HBackgroundStyle);
    HBackgroundStyle* style = static_cast<HBackgroundStyle*>(obj);
    if (!style) return ;

    style->setImagePath(d->mImagePath);
    style->setMargins(d->mMargins);
    style->setAlignment(d->mAlignment);
    style->setColor(d->mColor);
    style->setColorized(d->mColorized);
    style->setBackgroundBrush(d->mBackgroundBrush);
    style->setImageTile(d->mImageTile);

    HBaseStyle::copyTo(obj);
}

HBaseStyle* HBackgroundStyle::clone()
{
    HBackgroundStyle* style = new HBackgroundStyle(HObjectInfo(styleId(),""),parent());
    copyTo(style);

    return style;
}

void HBackgroundStyle::draw(QPainter * painter, const QRect &rect, int index)
{
    drawColor(painter,rect,index);
    drawImage(painter,rect,index);
}

void HBackgroundStyle::drawColor(QPainter* painter,const QRect& rect, int index)
{
    Q_UNUSED(index);
    Q_D(HBackgroundStyle);

    if (d->mColor.isValid()) {
        HDraw draw;
        draw.paint(painter, rect, d->mColorized.isValid()?d->mColorized:d->mColor, d->mMargins);
    }
}

void HBackgroundStyle::drawImage(QPainter* painter,const QRect& rect, int index)
{
    Q_D(HBackgroundStyle);
    if (!d->mImage.isNull()) {
        HDraw draw;
        draw.paint(painter, rect, d->mImage, d->mMargins, d->mImageTile, index);
    }
}

void HBackgroundStyle::on_colorChanged(const QColor& rgb)
{
    colorChanged(rgb);
}

void HBackgroundStyle::colorChanged(const QColor& rgb)
{
    Q_UNUSED(rgb);
    Q_D(HBackgroundStyle);

    int type = 0;
    if (!d->mImage.isNull()) {
        if (mResMgr->colorizeWithPixmap(d->mImage)) {
            type = 1;
        }
    }
    else if (d->mImagePath.size()>1) {
        d->mImage = mResMgr->loadPixmap(d->mImagePath);
        d->calcuTile();
        type = 1;
    }
    if (d->mColor.isValid()) {
        setColorized(mResMgr->colorizeWithColor(d->mColor));
        type |= 2;
    }
    emit backgroundChanged(type);
}
