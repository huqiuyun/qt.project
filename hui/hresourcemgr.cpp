#include "hresourcemgr.h"

HResourceMgr::HResourceMgr(QObject *parent) :
    QObject(parent)
{
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

QPixmap HResourceMgr::loadPath(const QString &path)
{
    Q_UNUSED(path);

    return QPixmap();
}
