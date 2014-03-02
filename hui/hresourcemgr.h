#ifndef HRESOURCEMGR_H
#define HRESOURCEMGR_H

#include "hbase.h"
#include <QPixmap>
#include <QByteArray>

class HResourceHandler;
class HResourceMgrPrivate;
class H_API HResourceMgr : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( HResourceMgr )
    Q_DECLARE_PRIVATE( HResourceMgr )
public:
    explicit HResourceMgr(QObject *parent = 0);
    ~HResourceMgr();

    void addHandler(HResourceHandler* handler);
    void removeHandler(HResourceHandler* handler);

    QPixmap loadPixmap(const QString& path);
    QByteArray loadData(const QString& path);

    bool colorizeWithPixmap(QPixmap& pixmap);
    bool colorizeWithColor(const QColor& color);

    bool findImageTile(qint64 key,HImageTile* tile);
    void addImageTile(qint64 key,const HImageTile& tile);
    void removeImageTile(qint64 key);
signals:
    void colorChanged(const QColor& rgb);

private:
    HResourceMgrPrivate* d_ptr;
};

#endif // HRESOURCEMGR_H
