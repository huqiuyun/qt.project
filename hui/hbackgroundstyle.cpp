#include "HBackgroundStyle.h"
#include "hresourcemgr.h"
#include "hstyle.h"
#include "hcore.h"
#include "private/hbackgroundstyle_p.h"
#include <QPainter>


IMPLEMENT_OBJECT_STATIC_CREATE(HBackgroundStyle)

HBackgroundStyle::HBackgroundStyle(QObject *parent) :
    HBaseStyle(parent),
    d_ptr(new HBackgroundStylePrivate()),
    mResMgr(HRESMGR)
{
}

HBackgroundStyle::HBackgroundStyle(const HObjectInfo& objinfo, QObject *parent) :
    HBaseStyle(objinfo,parent),
    d_ptr(new HBackgroundStylePrivate()),
    mResMgr(HRESMGR)
{
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
    mImage = image;
    emit backgroundChanged(0);
}

 QPixmap HBackgroundStyle::image() const
 {
     return mImage;
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

void HBackgroundStyle::copyTo(HBaseStyle* obj)
{
    HBackgroundStyle* style = static_cast<HBackgroundStyle*>(obj);
    if (!style) return ;

    style->setImagePath(imagePath());
    style->setMargins(margins());
    style->setAlignment(alignment());
    style->setColor(color());
    style->setColorized(colorized());
    style->setBackgroundBrush(backgroundBrush());

    HBaseStyle::copyTo(obj);
}

HBaseStyle* HBackgroundStyle::clone()
{
    HBackgroundStyle* style = new HBackgroundStyle(mObjinfo,parent());
    copyTo(style);

    return style;
}

void HBackgroundStyle::draw(QPainter * painter, const QRect &rect)
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);

    //draw
    if(mImage.isNull())
    {
        drawColor(painter,rect);
        return ;
    }
}

void HBackgroundStyle::drawColor(QPainter* painter,const QRect& rect)
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);
    Q_D(HBackgroundStyle);

    if (!d->mColor.isValid()) return ;
    painter->fillRect(rect,d->mColor);
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
    if (!mImage.isNull())
    {
        if (mResMgr->colorizeWithPixmap(mImage))
        {
            type = 1;
        }
    }
    else if (d->mImagePath.size()>1)
    {
        mImage = mResMgr->loadPixmap(d->mImagePath);
        type = 1;
    }
    if (d->mColor.isValid())
    {
        setColorized(mResMgr->colorizeWithColor(d->mColor));
        type |= 2;
    }
    emit backgroundChanged(type);
}
