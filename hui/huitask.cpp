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

void HuiTask::addScene(bool& main)
{
    Q_UNUSED(main);
    if (!mChild) {
        return ;
    }
    if(mChild->isHGWidget()) {
        if (isHGView()) {
            HGView* widget = objCast<HGView>();
            widget->sceneStyle()->addGWidget(mChild->objCast<HGWidget>(),main);
        }
        else {
            Q_ASSERT(0);
        }
    }
    else if(mChild->isGraphicsItem()){
        if (isHGView()) {
            HGView* widget = objCast<HGView>();
            widget->sceneStyle()->addItem(mChild->objCast<QGraphicsItem>());
        }
        else {
            Q_ASSERT(0);
        }
    }
    main = false;
    deleteChild();
}

void HuiTask::addWidget(HPropertyProxy* proxy,bool isUse)
{
    Q_UNUSED(proxy);
    if (!mChild) {
        return ;
    }
    //add new widget to layout
    if (mChild->isQWidget()) {
        if (isHQWidget()) {
            HQWidget* widget = objCast<HQWidget>();

            if (mFlags.isXmlLayout)
                widget->addWidget(mChild->objCast<QWidget>());
        }
        else if(isHGView()) {
            HGView* widget = objCast<HGView>();
            if (mFlags.isXmlLayout)
                widget->addWidget(mChild->objCast<QWidget>());
        }
        else if(isHGWidget()) {
            HGWidget* widget = objCast<HGWidget>();
            if (mFlags.isXmlLayout) {
                widget->addWidget(mChild->objCast<QWidget>());
            }
            else {
                //exception
            }
        }
        else{// not support
        }
    }
    else if(mChild->isGWidget()) {
        if (isHGWidget()) {
            HGWidget* widget = objCast<HGWidget>();
            if (mFlags.isXmlLayout)
                widget->addGWidget(mChild->objCast<QGraphicsWidget>());
        }
    }
    execSkipProperty(mChild,proxy,isUse);
    deleteChild();
}

void HuiTask::execSkipProperty(HuiTask* task,HPropertyProxy* proxy,bool isUse)
{
    if (!task) return ;
    if (QObject* obj = task->qObject())
    {// set property
        QList<HIdValue>::iterator iter = task->mPropertys.begin();
        while (iter != task->mPropertys.end()) {
            if (proxy && iter->mProxy) {
                bool handler = false;

                if (task->isQWidget())
                    handler = proxy->handlerQWidget(task->qWidget(),task->mObjType,iter->mId,iter->mVal.toString());

                else if(task->isGWidget())
                    handler = proxy->handlerGWidget(task->gWidget(),task->mObjType,iter->mId,iter->mVal.toString());

                else if(task->isGraphicsItem())
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
}

void HuiTask::addWidgetToList()
{
    if (!mChild) {
        return ;
    }

    if (isQWidget())
    {
        if (mChild->isQWidget()) {
            mWidgets.push_back(mChild->objCast<QWidget>());
        }
        else {
            //exception
            Q_ASSERT(0);
        }
    }
    else if (isHGWidget()) {
        // not support ?
    }
    //
    deleteChild();
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


void HuiTask::setProperty(QObject* obj, const QString& id, const QString& attr,bool isUse)
{
    if (!obj) return;

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
        return;
    }
    if(isUse)
        obj->setProperty(cid,attr);
}
