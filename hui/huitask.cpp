#include "huitask.h"
#include "hstyle.h"
#include "hfactory.h"
#include "hcore.h"
#include "hgview.h"
#include "hqwidget.h"
#include "hgwidget.h"
#include "hgscenestyle.h"
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

void HuiTask::generateStyle()
{
    if (!mStyle) {
        mStyle = new HStyle();
        mFlags.isNewStyle = true;
    }
}

void HuiTask::generateChild()
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
        QWidget* widget = objCast<QWidget>();
        QMetaObject::invokeMethod(widget,"installStyle",Qt::DirectConnection,Q_ARG(const HStyle*, mStyle));
        setFlagsWithQWidget(widget);
    }
    else if(isGWidget()) {
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
            objCast<HGView>()->sceneStyle()->addGWidget(mChild->objCast<HGWidget>(),mChild->mLayoutConf);
        }
        else if(mChild->isGraphicsItem()) {
            objCast<HGView>()->sceneStyle()->addItem(mChild->objCast<QGraphicsItem>(),mChild->mLayoutConf);
        }
    }
    else {
        Q_ASSERT(0);
    }

    deleteChild();
}

void HuiTask::addLayout(HPropertyProxy* proxy,bool isUse)
{
    addWidget(proxy,isUse);
    //set layout property
}

void HuiTask::addWidget(HPropertyProxy* proxy,bool isUse)
{
    Q_UNUSED(proxy);
    if (!mChild) {
        return ;
    }
    if (mChild->isQWidget()) {
        if (isQWidget()) {
            if (mFlags.isXmlLayout) {

                if (isHQWidget()) {
                    objCast<HQWidget>()->insertWidget(mChild->objCast<QWidget>(),mChild->mLayoutConf);
                }
                else if(isHGView()) {
                    objCast<HGView>()->insertWidget(mChild->objCast<QWidget>(),mChild->mLayoutConf);
                }
                else Q_ASSERT(0);
            }
            else
            {// parant And child
                mWidgets.push_back(mChild->objCast<QWidget>());

                if (isHQWidget()) {
                    objCast<HQWidget>()->addChildWidget(mChild->objCast<QWidget>(),mChild->mLayoutConf);
                }
                else if(isHGView()) {
                    objCast<HGView>()->addChildWidget(mChild->objCast<QWidget>(),mChild->mLayoutConf);
                }
                else Q_ASSERT(0);
            }
        }
        else if(isHGWidget()) {
            if (mFlags.isXmlLayout) { // for proxywidget
                objCast<HGWidget>()->insertWidget(mChild->objCast<QWidget>(),mChild->mLayoutConf);
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
                objCast<HGWidget>()->insertGWidget(mChild->objCast<QGraphicsWidget>(),mChild->mLayoutConf);
            }
            else {// parent And child
                objCast<HGWidget>()->addChildGWidget(mChild->objCast<QGraphicsWidget>(),mChild->mLayoutConf);
            }
        }
        else Q_ASSERT(0);
    }
    execSkipProperty(mChild,proxy,isUse);
    deleteChild();
}

void HuiTask::execSkipProperty(HuiTask* task,HPropertyProxy* proxy,bool isUse)
{
    if (!task) return ;

    QObject* obj = task->qObject(); // obj maybe is NULL , QGraphicsItem is not based QObject
    QList<HIdValue>::iterator iter = task->mPropertys.begin();
    while (iter != task->mPropertys.end()) {

        if (proxy && iter->mProxy) {
            bool handler = false;

            if (task->isQWidget())
                handler = proxy->handlerQWidget(task->qWidget(),task->mObjType,iter->mId,iter->mVal.toString());

            else if(task->isGWidget())
                handler = proxy->handlerGWidget(task->gWidget(),task->mObjType,iter->mId,iter->mVal.toString());

            else if(task->isGraphicsItem()) // it is not QObject , then obj is NULL
                handler = proxy->handlerGItem(task->gItem(),task->mObjType,iter->mId,iter->mVal.toString());

            if (!handler)
                setProperty(obj, iter->mId, iter->mVal.toString(),isUse);
        }
        else{
            setProperty(obj, iter->mId, iter->mVal.toString(),isUse);
        }
        ++iter;
    }
    task->mPropertys.clear();
}

bool HuiTask::hasProperty(QObject* object, const char* key)
{
    QVariant v= object->property(key);
    return v.isValid()?v.toBool():false;
}

void HuiTask::setFlagsWithQWidget(QWidget* parent)
{
    mFlags.isQLayout = 0;
    mFlags.isScene = 0;
    mFlags.isObjHQWidget = 0;
    mFlags.isObjHGView = 0;

    if (!parent)
        return;

    if (parent->layout())
        mFlags.isQLayout = 1;

    if (hasProperty(parent,"isHQWidget")) {
        mFlags.isObjHQWidget = 1;
    }
    else if (hasProperty(parent,"isHGView")) {
        mFlags.isObjHGView = 1;

        if (HGView* view = static_cast<HGView*>(parent))
            mFlags.isScene = view->scene()?1:0;
    }
}

void HuiTask::setFlagsWithHGWidget(QGraphicsWidget* parent)
{
    mFlags.isGLayout = 0;
    mFlags.isObjHGWidget = 0;

    if (!parent)
        return;

    if (parent->layout())
        mFlags.isGLayout = 1;
    else if (hasProperty(parent,"isGLayout"))
        mFlags.isGLayout = 1;

    if (hasProperty(parent,"isHGWidget")) {
        mFlags.isObjHGWidget = 1;
    }
}

void HuiTask::setFlagsWithHGItem(QGraphicsItem* parent)
{
    mFlags.isGLayout = 0;
    mFlags.isObjHGWidget = 0;

    if (!parent)
        return;

    if (parent->isWidget()) {
        setFlagsWithHGWidget(static_cast<QGraphicsWidget*>(parent));
    }
}


bool HuiTask::setProperty(QObject* obj, const QString& id, const QString& attr,bool isUse)
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
    else if(isUse) {
        obj->setProperty(cid,attr);
        return true;
    }
    return false;
}
