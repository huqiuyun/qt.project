#include "hganimation.h"
#include "hcore.h"
#include "hstyle.h"
#include "henums.h"
#include "hfactory.h"
#include "hresourcemgr.h"
#include "private/hgwidget_p.h"

#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMovie>
#include <QBuffer>
#include <QKeyEvent>

class HGAnimationPrivate : public HGWidgetPrivate
{
    Q_DISABLE_COPY(HGAnimationPrivate)
    Q_DECLARE_PUBLIC( HGAnimation )
public:
    HGAnimationPrivate():
        HGWidgetPrivate(),
        mIsLoopPlay(true),
        mAnimate(NULL),
        mMovie(NULL)
    {
    }

    ~HGAnimationPrivate()
    {
    }

    void onInitStyle(const HStyle* style)
    {
        Q_UNUSED(style);
    }

    QPoint centerPos(const QSize& imageItemSize, const QSize& widgetSize )
    {
        int x = (widgetSize.width() - imageItemSize.width() ) / 2 ;
        int y = (widgetSize.height() - imageItemSize.height() ) / 2 ;

        return QPoint( x, y );
    }

    void resetDefaultPos()
    {
        if (mAnimate == NULL )
        {
            return;
        }
        mAnimate->setPos(1, 1);
    }

    bool				 mIsLoopPlay;
    QGraphicsPixmapItem	*mAnimate;
    QMovie				*mMovie;
    QByteArray			 mData;
    QBuffer				 mBuffer;
    QSizeF				 mImageScaleSize;
    QString              mGifFileName;
};

IMPLEMENT_GITEM_STATIC_CREATE(HGAnimation,HGAnimation)

HGAnimation::HGAnimation(const HObjectInfo& objinfo, QGraphicsItem* parent)
    :HGWidget(*(new HGAnimationPrivate()),objinfo,parent)
{
    mObjType = USEOBJTYPE(HGAnimation);

    Q_D( HGAnimation );
    d->mAnimate = new QGraphicsPixmapItem(this);
    d->mAnimate->setTransformationMode( Qt::SmoothTransformation );

    d->mMovie = new QMovie(this);
    connect(d->mMovie, SIGNAL(frameChanged(int)), this, SLOT(on_frameChanged(int)));
}

HGAnimation::~HGAnimation()
{
}

void HGAnimation::on_mousePressed()
{
    on_clicked();
}

void HGAnimation::on_mouseReleased()
{
}

void HGAnimation::on_keyPressed()
{
     on_clicked();
}

void HGAnimation::on_frameChanged ( int frameNumber )
{
    Q_UNUSED(frameNumber);
    Q_D(HGAnimation);

    if (d->mImageScaleSize.isValid())
    {
        if (QRect(0, 0, d->mImageScaleSize.width(), d->mImageScaleSize.height() ).contains(d->mMovie->currentPixmap().rect()) )
        {
            d->mAnimate->setPos( d->centerPos(d->mMovie->currentPixmap().size(), d->mImageScaleSize.toSize() ) );
            d->mAnimate->setPixmap( d->mMovie->currentPixmap() );
        }
        else
        {
            d->resetDefaultPos();
            d->mAnimate->setPixmap( d->mMovie->currentPixmap().scaled( d->mImageScaleSize.toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
        }
    }
    else
    {
        d->mAnimate->setPixmap( d->mMovie->currentPixmap() );
    }

    if (!d->mIsLoopPlay && frameNumber == d->mMovie->frameCount()-1)
    {
        d->mMovie->stop();
    }
}

QString HGAnimation::imagePath() const
{
    return d_func()->mGifFileName;
}

void HGAnimation::setImage( const QString &imageName )
{
    Q_D( HGAnimation );

    if (d->mGifFileName == imageName)
        return ;

    d->mMovie->stop();

    if (imageName.isEmpty())
    {
        d->mAnimate->setPixmap( QPixmap() );
        d->mData.clear();
        d->mBuffer.close();
        d->mMovie->setDevice( NULL );
    }
    else
    {
        d->mGifFileName = imageName;
        d->mData = HRESMGR->loadData(imageName);

        d->mBuffer.close();
        d->mBuffer.setData( d->mData );
        d->mMovie->setDevice( &d->mBuffer );
    }
}

void HGAnimation::start()
{
    Q_D( HGAnimation );
    d->mMovie->start();
}

void HGAnimation::stop()
{
    Q_D( HGAnimation );
    d->mMovie->stop();
}

void HGAnimation::setPaused(bool b)
{
    Q_D( HGAnimation );
    d->mMovie->setPaused(b);
}

void HGAnimation::on_finished()
{
    Q_D(HGAnimation);

    if (!d->mIsLoopPlay)
    {
        d->mMovie->stop();
    }
}

void HGAnimation::setPlayLoop( bool isLoop )
{
    Q_D( HGAnimation );
    d->mIsLoopPlay = isLoop;
}

bool HGAnimation::playLoop() const
{
    Q_D( const HGAnimation );
    return d->mIsLoopPlay;
}

void HGAnimation::setImageScaleSize( const QSizeF& size )
{
    d_func()->mImageScaleSize = size;
}

QSizeF HGAnimation::imageScaleSize() const
{
    return d_func()->mImageScaleSize;
}


