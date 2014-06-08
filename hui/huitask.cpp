#include "huitask.h"
#include "hstyle.h"
#include "hfactory.h"
#include "hcore.h"
#include "hgview.h"
#include "hqwidget.h"
#include "hgwidget.h"
#include "hgsceneitem.h"
#include "hpropertyproxy.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QGraphicsLayoutItem>
#include <QXmlStreamReader>
#include <QMetaProperty>

HuiTask::HuiTask():
    mObj(NULL),
    mObjType(USEOBJTYPE(Unk)),
    mParent(NULL),
    mChild(NULL),
    mStyle(NULL)
{
}

HuiTask::~HuiTask()
{
    deleteStyle();
}

void HuiTask::createStyle()
{
    if (!mStyle) {
        mStyle = new HStyle();
        mFlags.isNewStyle = true;
    }
}

void HuiTask::createChild()
{
    mChild = new HuiTask();
    mChild->mParent = this;
}

void HuiTask::deleteChild()
{
    HuiTask* child = mChild;
    while (child)
    {
        HuiTask* next = child->mChild;
        hDelete(child);
        child = next;
    }
    mChild = NULL;
}

int HuiTask::findFunc(const char* clsname)
{
    int func = -1;
    if (HFACTORY->isQWidget(clsname)) {
        func = canQWidget()?0:-1;
    }
    else if (HFACTORY->isGWidget(clsname)) {
        func = canGWidget()?1:-1;
    }
    else if (HFACTORY->isGItem(clsname)) {
        func = canGItem()?2:-1;
    }
    else if (HFACTORY->isObject(clsname)) {
        func = canQObject()?3:-1;
    }
    return func;
}

QGraphicsItem* HuiTask::gItem()
{
    return (isGraphicsItem()||isGWidget()) ? objCast<QGraphicsItem>():NULL;
}

QWidget* HuiTask::qWidget()
{
    return (isQWidget()) ? objCast<QWidget>():NULL;
}

QGraphicsWidget* HuiTask::gWidget()
{
    return (isGWidget()) ?objCast<QGraphicsWidget>():NULL;
}

QObject* HuiTask::qObject()
{
    return (isGraphicsItem())?NULL:objCast<QObject>();
}

HStyle* HuiTask::style() const
{
    return mStyle;
}

void HuiTask::installStyle()
{
    if (!mStyle) return;
    if (mStyle->size()<=0)
    {
        return;
    }

    if (isQWidget()) {
        //qDebug("HuiTask::installStyle qwidget");
        QWidget* widget = objCast<QWidget>();
        QMetaObject::invokeMethod(widget,"installStyle",Qt::DirectConnection,Q_ARG(const HStyle*, mStyle));
        setFlagsWithQWidget(widget);
    }
    else if(isGWidget()) {
        //qDebug("HuiTask::installStyle gwidget");
        QGraphicsWidget* widget = objCast<QGraphicsWidget>();
        QMetaObject::invokeMethod(widget,"installStyle",Qt::DirectConnection,Q_ARG(const HStyle*, mStyle));
        setFlagsWithHGWidget(widget);
    }
    return;
}

void HuiTask::deleteStyle()
{
    if (mFlags.isNewStyle) {
        hDelete(mStyle);
        mFlags.isNewStyle = 0;
    }
}

void HuiTask::addScene()
{
    if (!mChild) {
        return ;
    }

    if (isHGView()) {
        if(mChild->isHGWidget()) {
            objCast<HGView>()->sceneItem()->addGWidget(mChild->objCast<HGWidget>(),mChild->mLayoutConfig);
        }
        else if(mChild->isGraphicsItem()) {
            objCast<HGView>()->sceneItem()->addItem(mChild->objCast<QGraphicsItem>(),mChild->mLayoutConfig);
        }
    }
    else {
        Q_ASSERT(0);
    }

    deleteChild();
}

void HuiTask::addLayout(HPropertyProxy* proxy)
{
    addWidget(proxy);
    //set layout property
}

void HuiTask::addWidget(HPropertyProxy* proxy)
{
    Q_UNUSED(proxy);
    if (!mChild) {
        return ;
    }
    mChild->mLayoutConfig.setStyle(mStyle);
    if (mChild->isQWidget()) {
        if (isQWidget()) {
            if (mFlags.isXmlLayout) {

                if (isHQWidget()) {
                    objCast<HQWidget>()->insertWidget(mChild->objCast<QWidget>(),mChild->mLayoutConfig);
                }
                else if(isHGView()) {
                    objCast<HGView>()->insertWidget(mChild->objCast<QWidget>(),mChild->mLayoutConfig);
                }
                else Q_ASSERT(0);
            }
            else
            {// parant And child
                mWidgets.push_back(mChild->objCast<QWidget>());

                if (isHQWidget()) {
                    objCast<HQWidget>()->addChildWidget(mChild->objCast<QWidget>(),mChild->mLayoutConfig);
                }
                else if(isHGView()) {
                    objCast<HGView>()->addChildWidget(mChild->objCast<QWidget>(),mChild->mLayoutConfig);
                }
                else Q_ASSERT(0);
            }
        }
        else if(isHGWidget()) {
            if (mFlags.isXmlLayout) { // for proxywidget
                objCast<HGWidget>()->insertWidget(mChild->objCast<QWidget>(),mChild->mLayoutConfig);
            }
            else {//exception
                Q_ASSERT(0);
            }
        }
        else{// not support
        }
    }
    else if(mChild->isGWidget()) {
        if (isHGWidget()) {
            if (mFlags.isXmlLayout) {
                objCast<HGWidget>()->insertGWidget(mChild->objCast<QGraphicsWidget>(),mChild->mLayoutConfig);
            }
            else {// parent And child
                objCast<HGWidget>()->addChildGWidget(mChild->objCast<QGraphicsWidget>(),mChild->mLayoutConfig);
            }
        }
        else Q_ASSERT(0);
    }
    setProperty(mChild,proxy);
    deleteChild();
}

void HuiTask::setProperty(HuiTask* task,HPropertyProxy* proxy)
{
    if (!task) return ;

    QObject* obj = task->qObject(); // obj maybe is NULL , QGraphicsItem is not based QObject
    QList<HIdValue>::const_iterator iter = task->mPropertys.constBegin();
    while (iter != task->mPropertys.constEnd()) {

        if (proxy && iter->mProxy) {

            bool handler = false;

            if (task->isQWidget())
                handler = proxy->handlerQWidget(task->qWidget(),task->mObjType,iter->mId,iter->mVal.toString());

            else if(task->isGraphicsItem()) {// it is not QObject , then obj is NULL

                handler = proxy->handlerGItem(task->gItem(),task->mObjType,iter->mId,iter->mVal.toString());

                if(task->isGWidget())
                    handler = proxy->handlerGWidget(task->gWidget(),task->mObjType,iter->mId,iter->mVal.toString());
            }
            if (!handler) {
                setProperty(obj, iter->mId, iter->mVal.toString());
            }
        }
        else{
            setProperty(obj, iter->mId, iter->mVal.toString());
        }
        ++iter;
    }
    task->mPropertys.clear();
}

void HuiTask::setProperty(QObject* obj, const QList<HIdValue>& propertys)
{
    if (!obj)
        return ;

    QList<HIdValue>::const_iterator iter = propertys.constBegin();
    while (iter != propertys.constEnd()) {
        setProperty(obj, iter->mId, iter->mVal.toString());
        ++iter;
    }
}

bool HuiTask::hasProperty(QObject* object, const char* key)
{
    QVariant v = object->property(key);
    return v.isValid()?v.toBool():false;
}

void HuiTask::setFlagsWithQWidget(QWidget* parent)
{
    mFlags.isQLayout = 0;
    mFlags.isScene = 0;
    mFlags.isHQWidget = 0;
    mFlags.isHGView = 0;

    if (!parent)
        return;

    if (parent->layout())
        mFlags.isQLayout = 1;

    if (hasProperty(parent,"isHQWidget")) {
        mFlags.isHQWidget = 1;
    }
    else if (hasProperty(parent,"isHGView")) {
        mFlags.isHGView = 1;
        if (HGView* view = static_cast<HGView*>(parent))
            mFlags.isScene = view->scene()?1:0;
    }
}

void HuiTask::setFlagsWithHGWidget(QGraphicsWidget* parent)
{
    mFlags.isGLayout = 0;
    mFlags.isHGWidget = 0;

    if (!parent)
        return;

    if (parent->layout())
        mFlags.isGLayout = 1;
    else if (hasProperty(parent,"isGLayout"))
        mFlags.isGLayout = 1;

    if (hasProperty(parent,"isHGWidget")) {
        mFlags.isHGWidget = 1;
    }
}

void HuiTask::setFlagsWithHGItem(QGraphicsItem* parent)
{
    mFlags.isGLayout = 0;
    mFlags.isHGWidget = 0;

    if (!parent)
        return;

    if (parent->isWidget()) {
        setFlagsWithHGWidget(static_cast<QGraphicsWidget*>(parent));
    }
}


bool HuiTask::setProperty(QObject* obj, const QString& id, const QString& attr)
{
    if (!obj) return false;

    QByteArray cid = id.toLatin1();
    int idx = obj->metaObject()->indexOfProperty(cid.constData());
    if(-1 != idx) {
        QMetaProperty prop = obj->metaObject()->property(idx);
        int type_id = prop.type();
        if(type_id == QVariant::UserType) {
            type_id = prop.userType();
        }
        //qDebug("HuiTask::set Property=%s,type_id=%d",cid.constData(),type_id);
        long hr = -1;
        QVariant var = HFACTORY->convertString(type_id, attr, &hr);
        if (0==hr) {
            obj->setProperty(cid,var);
        }
        else {
            obj->setProperty(cid,HFACTORY->convertString(0, attr, &hr));
        }
        return true;
    }
    return false;
}

bool HuiTask::invoke(QObject* obj, const char* method,const QVector<QVariant>& args)
{
    if (!obj)
        return false;

    const int kMaxArgCount = 9;
    int argCount = args.size();

    //qDebug("invoke arg count=%d",argCount);
    if (argCount>kMaxArgCount)
        argCount = kMaxArgCount;

    QGenericReturnArgument retVal;
    QGenericArgument val[kMaxArgCount];
    for(int i=0; i < argCount;i++){
        QVariant a = args[i];
        int type = a.type();
        //qDebug("invoke type =%d",type);
        switch(type)
        {
        case QVariant::Point:
            val[i] = Q_ARG(QPoint,a.toPoint());
            break;

        case QVariant::PointF:
            val[i] = Q_ARG(QPointF,a.toPointF());
            break;

        case QVariant::Rect:
            val[i] = Q_ARG(QRect,a.toRect());
            break;

        case QVariant::RectF:
            val[i] = Q_ARG(QRectF,a.toRectF());
            break;

        case QVariant::Size:
            val[i] = Q_ARG(QSize,a.toSize());
            break;

        case QVariant::SizeF:
            val[i] = Q_ARG(QSizeF,a.toSizeF());
            break;

        case QVariant::Color: {
            QColor c = a.value<QColor>();
            //qDebug("invoke arg color=%d,%d,%d",c.red(),c.green(),c.blue());
            val[i] = Q_ARG(QColor,c);
        }
            break;

        case QVariant::Brush:
            val[i] = Q_ARG(QBrush,a.value<QBrush>());
            break;

        case QVariant::Int:
            //qDebug("invoke arg int=%d",a.toInt());
            val[i] = Q_ARG(int,a.toInt());
            break;

        case QVariant::Double:
            val[i] = Q_ARG(qreal,a.toReal());
            break;

        case QVariant::Bool:
            val[i] = Q_ARG(bool,a.toBool());
            break;
        }
    }
    return QMetaObject::invokeMethod(obj,method,retVal,val[0],val[1],val[2],val[3],val[4],val[5],val[6],val[7],val[8]);
}

