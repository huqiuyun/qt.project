#include "hpropertyproxy.h"
#include "hcreator.h"
#include "hglobal.h"
#include <QWidget>
#include <QGraphicsWidget>
#include <QGraphicsItem>

#define HPROPERTY_ID_MATCH(cnstid) (id==QLatin1String(cnstid))

HPropertyProxy::HPropertyProxy()
{
}

bool HPropertyProxy::handlerQWidget(QWidget *obj, int objType, const QString& id, const QString &val)
{
    Q_UNUSED(obj);
    Q_UNUSED(objType);
    Q_UNUSED(id);
    Q_UNUSED(val);
    long hr = -1;
    if (HPROPERTY_ID_MATCH("fixedWidth")) {// int
        obj->setFixedWidth(val.toInt());
    }
    else if(HPROPERTY_ID_MATCH("fixedHeight")) {//int
        obj->setFixedHeight(val.toInt());
    }
    else if(HPROPERTY_ID_MATCH("fixedSize")) {//QSize
        obj->setFixedSize(HuiCreator::convertQVariant_QSize(val,&hr).toSize());
    }
    else if(HPROPERTY_ID_MATCH("windowAttribute")){
        HGlobal::setQWidgetAttribute(obj,val);
    }
    else
        return false;

    return true;
}

bool HPropertyProxy::handlerGWidget(QGraphicsWidget *obj, int objType, const QString& id, const QString &val)
{
    Q_UNUSED(obj);
    Q_UNUSED(objType);
    Q_UNUSED(id);
    Q_UNUSED(val);

    return false;
}

bool HPropertyProxy::handlerGItem(QGraphicsItem *obj, int objType, const QString& id, const QString &val)
{
    Q_UNUSED(obj);
    Q_UNUSED(objType);
    Q_UNUSED(id);
    Q_UNUSED(val);

    return false;
}

