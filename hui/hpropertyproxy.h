#ifndef HPROXYPROXY_H
#define HPROXYPROXY_H

#include "hconfig.h"
#include <QVariant>
class QGraphicsWidget;
class QWidget;
class QGraphicsItem;

class H_API HPropertyProxy
{
public:
    explicit HPropertyProxy();

    virtual bool handlerQWidget(QWidget* obj, int objType/* @see HEnums::HObjectType*/,const QString& id, const QString& val);
    virtual bool handlerGWidget(QGraphicsWidget* obj,int objType, const QString& id, const QString& val);
    virtual bool handlerGItem(QGraphicsItem* obj,int objType, const QString& id, const QString& val);

protected:
    bool handlerDefQWidget(QWidget *obj, int objType, const QString& id, const QString &val);
    bool handlerDefGWidget(QGraphicsWidget *obj, int objType, const QString& id, const QString &val);
    bool handlerDefGItem(QGraphicsItem *obj, int objType, const QString& id, const QString &val);
};

#endif // HPROXYPROXY_H
