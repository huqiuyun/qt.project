#include "hbackgrounditem.h"
#include "hresourcemgr.h"
#include "hcssstyle.h"
#include "hcore.h"
#include <QPainter>


class HBackgroundItemPrivate
{
public:
    HBackgroundItemPrivate(const QLatin1String& styleid) :
        mStyleId(styleid)
    {
    }
    QSharedPointer<HCssObject> mCss;
    QLatin1String mStyleId;
};

IMPLEMENT_OBJECT_STATIC_CREATE(HBackgroundItem)
HBackgroundItem::HBackgroundItem(const HObjectInfo& objinfo, QObject *parent) :
    QObject(parent),
    d_ptr(new HBackgroundItemPrivate(objinfo.mStyleId)),
    mResMgr(HRESMGR)
{
    d_ptr->mCss =
            QSharedPointer<HCssObject>(HCSSSTYLE->create(HCssStyle::idCheck(objinfo.mStyleId,QLatin1String("backgroundId")),"HCssBackground"));
    if (objinfo.mObjName.size()>1) setObjectName(objinfo.mObjName);
}

HBackgroundItem::~HBackgroundItem()
{
    delete d_ptr;
}

void HBackgroundItem::setStyleId(const QLatin1String& id)
{
    d_func()->mStyleId = id;
}

QLatin1String HBackgroundItem::styleId() const
{
    Q_D(const HBackgroundItem);
    return d->mStyleId;
}

HCssBackground* HBackgroundItem::css() const
{
    return static_cast<HCssBackground*>(d_func()->mCss.data());
}

bool HBackgroundItem::setCss(QSharedPointer<HCssObject> obj)
{
    HCssBackground* css = static_cast<HCssBackground*>(obj.data());
    if (!css)
    {
        return false;
    }
    d_func()->mCss = obj;
    return true;
}

void HBackgroundItem::setImagePath(const QString& path)
{
    css()->setImagePath(path);
    mImage = mResMgr->loadPixmap(css()->imagePath());
    emit backgroundChanged(0);
}

QString HBackgroundItem::imagePath() const
{
    return css()->imagePath();
}

void HBackgroundItem::setImage(const QPixmap& image)
{
    mImage = image;
    emit backgroundChanged(0);
}

 QPixmap HBackgroundItem::image() const
 {
     return mImage;
 }

void HBackgroundItem::setColor(const QColor& rgb)
{
    css()->setColor(rgb);
    emit backgroundChanged(1);
}

QColor HBackgroundItem::color() const
{
    return css()->color();
}

void HBackgroundItem::setMargins(const QMargins& m)
{
    css()->setMargins(m);
}

QMargins HBackgroundItem::margins() const
{
    return css()->margins();
}

void HBackgroundItem::setColorizePolicy(qy::HColorizeFlag flag)
{
    css()->setColorizePolicy(flag);
}

qy::HColorizeFlag HBackgroundItem::colorizePolicy() const
{
    return css()->colorizePolicy();
}

/**
    @brief 设置混合模式
    默认的混合模式为：QPainter::CompositionMode_SourceOver
*/
void HBackgroundItem::setComposeMode(QPainter::CompositionMode composeMode)
{
    css()->setComposeMode(composeMode);
}

QPainter::CompositionMode HBackgroundItem::composeMode() const
{
    return css()->composeMode();
}

void HBackgroundItem::draw(QPainter * painter, const QRect &rect)
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

void HBackgroundItem::drawColor(QPainter* painter,const QRect& rect)
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);
    QColor color = css()->color();
    if (!color.isValid()) return ;
    painter->fillRect(rect,color);
}

void HBackgroundItem::on_colorChanged(const QColor& rgb)
{
    colorChanged(rgb);
}

void HBackgroundItem::colorChanged(const QColor& rgb)
{
    Q_UNUSED(rgb);

    int type = 0;
    if (!mImage.isNull())
    {
        if (mResMgr->colorizeWithPixmap(mImage))
        {
            type = 1;
        }
    }
    else if (css()->imagePathLength()>0)
    {
        mImage = mResMgr->loadPixmap(css()->imagePath());
        type = 1;
    }
    QColor color = css()->color();
    if (color.isValid())
    {
        css()->setColorized(mResMgr->colorizeWithColor(color));
        type |=2;
    }
    emit backgroundChanged(type);
}

void HBackgroundItem::on_cssStyle_changed(const QString &id)
{
    Q_UNUSED(id);
}
