#ifndef HREMgr_H
#define HResourceMgr_H

#include "hconfig.h"
#include <QPixmap>

class H_API HResourceMgr : public QObject
{
    Q_OBJECT
public:
    explicit HResourceMgr(QObject *parent = 0);

    QPixmap loadPath(const QString& path);
    bool colorizeWithPixmap(QPixmap& pixmap);
    bool colorizeWithColor(const QColor& color);
signals:
    void colorChanged(const QColor& rgb);

public slots:

};

#endif // HResourceMgr_H
