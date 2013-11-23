#include "huitask.h"
#include "hstyle.h"
#include "hfactory.h"
#include "hcore.h"
#include "hgview.h"
#include "hqwidget.h"
#include "hgwidget.h"
#include "hgscenestyle.h"
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
    Q_ASSERT(mStyle==NULL);
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

QGraphicsItem* HuiTask::parentGItem()
{
    return (isGraphicsItem()||isGWidget()) ? objCast<QGraphicsItem>():NULL;
}

QWidget* HuiTask::parentQWidget()
{
    return (isQWidget()) ? objCast<QWidget>():NULL;
}

QGraphicsWidget* HuiTask::parentGWidget()
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
        deleteStyle();
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
    deleteStyle();
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

void HuiTask::addWidget()
{
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
    deleteChild();
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

