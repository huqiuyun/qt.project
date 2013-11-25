#include "hpropertyproxy.h"

HPropertyProxy::HPropertyProxy()
{
}

bool HPropertyProxy::handlerQWidget(QWidget* obj, int objType/* @see HEnums::HObjectType*/,
                                    const char* id, const QVariant& val)
{
    Q_UNUSED(obj);
    Q_UNUSED(objType);
    Q_UNUSED(id);
    Q_UNUSED(val);

    return false;
}

bool HPropertyProxy::handlerGWidget(QGraphicsWidget* obj,int objType, const char* id, const QVariant& val)
{
    Q_UNUSED(obj);
    Q_UNUSED(objType);
    Q_UNUSED(id);
    Q_UNUSED(val);

    return false;
}

bool HPropertyProxy::handlerGItem(QGraphicsItem* obj,int objType, const char* id, const QVariant& val)
{
    Q_UNUSED(obj);
    Q_UNUSED(objType);
    Q_UNUSED(id);
    Q_UNUSED(val);

    return false;
}
