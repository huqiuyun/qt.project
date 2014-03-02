#include "hresourcemgr.h"
#include "hresourcehandler.h"
#include <QList>

typedef QList<HResourceHandler*> RES_HANDLERS;
typedef QMap<qint64,HImageTile> TILEMap;
class HResourceMgrPrivate
{
public:
    HResourceMgrPrivate()
    {
    }

    ~HResourceMgrPrivate()
    {
        RES_HANDLERS::iterator iter = mHandlers.begin();
        while (iter != mHandlers.end()) {
            delete (*iter);
            ++iter;
        }
        mHandlers.clear();
        mTiles.clear();
    }
    RES_HANDLERS mHandlers;
    TILEMap mTiles;
};

HResourceMgr::HResourceMgr(QObject *parent) :
    QObject(parent),
    d_ptr(new HResourceMgrPrivate)
{
    addHandler( new HQtHandler()); //path = :/
    addHandler( new HPluginHandler()); // path = ?{pluginid}/
    addHandler( new HDefaultHandler());// path =
    addHandler( new HAbsoluteHandler());//
}

HResourceMgr::~HResourceMgr()
{
    hDelete(d_ptr);
}

void HResourceMgr::addHandler(HResourceHandler* handler)
{
    Q_D(HResourceMgr);
    RES_HANDLERS::iterator iter = d->mHandlers.begin();
    while (iter != d->mHandlers.end()) {
        if (*iter == handler) return;
        ++iter;
    }
    d->mHandlers.push_back(handler);
}

void HResourceMgr::removeHandler(HResourceHandler* handler)
{
    Q_D(HResourceMgr);
    RES_HANDLERS::iterator iter = d->mHandlers.begin();
    while (iter != d->mHandlers.end()) {
        if (*iter == handler) {
            d->mHandlers.erase(iter);
            return;
        }
        ++iter;
    }
}

 bool HResourceMgr::colorizeWithPixmap(QPixmap& pixmap)
 {
     Q_UNUSED(pixmap);
     return false;
 }

 bool HResourceMgr::colorizeWithColor(const QColor& color)
 {
     Q_UNUSED(color);
     return false;
 }

QPixmap HResourceMgr::loadPixmap(const QString &path)
{
    Q_D(HResourceMgr);
    QPixmap pixmap;
    QString trimmedPath = path.trimmed();
    RES_HANDLERS::iterator iter = d->mHandlers.begin();
    while (iter != d->mHandlers.end()) {
        if ((*iter)->loadImage(trimmedPath, pixmap)) {
            break;
        }
        ++iter;
    }
    return pixmap;
}

QByteArray HResourceMgr::loadData(const QString& path)
{
    Q_D(HResourceMgr);

    QByteArray bytes;
    QString trimmedPath = path.trimmed();
    RES_HANDLERS::iterator iter = d->mHandlers.begin();
    while (iter != d->mHandlers.end()) {
        if ((*iter)->loadData(trimmedPath, bytes)) {
            break;
        }
        ++iter;
    }
    return bytes;
}

bool HResourceMgr::findImageTile(qint64 key,HImageTile* tile)
{
    Q_D(HResourceMgr);
    TILEMap::iterator iter = d->mTiles.find(key);
    if (iter != d->mTiles.end()) {
        if (tile)
            *tile = iter.value();
        return true;
    }
    return false;
}

void HResourceMgr::addImageTile(qint64 key,const HImageTile& tile)
{
    Q_D(HResourceMgr);
    d->mTiles[key] = tile;
}

void HResourceMgr::removeImageTile(qint64 key)
{
    Q_D(HResourceMgr);
    d->mTiles.remove(key);
}

