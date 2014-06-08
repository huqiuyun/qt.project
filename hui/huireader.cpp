#include "huireader.h"
#include "hgwidget.h"
#include "hgview.h"
#include "hcore.h"
#include "hstyle.h"
#include "hfactory.h"
#include "hqwidget.h"
#include "hresourcemgr.h"
#include "hgsceneitem.h"
#include "hpropertyproxy.h"
#include "huitask.h"
#include "hcreator.h"
#include "hglayout.h"
#include "hqlayout.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QGraphicsLayoutItem>
#include <QXmlStreamReader>
#include <QMetaEnum>
#include <QDir>
#include <QMetaProperty>

class HuiNextKey
{
public:
    HuiNextKey()
    {
        task = NULL;
        fnTask = NULL;
        obj = NULL;
        fnObject = NULL;
    }
    explicit HuiNextKey(HuiTask* t,fnReaderTask fT, QObject* o, fnReaderObject fO)
    {
        task = t;
        fnTask = fT;
        obj = o;
        fnObject = fO;
    }
    HuiNextKey(const HuiNextKey& key)
    {
        *this = key;
    }
    HuiNextKey& operator = (const HuiNextKey& key)
    {
        task = key.task;
        fnTask = key.fnTask;
        obj = key.obj;
        fnObject = key.fnObject;
        return *this;
    }
    HuiTask* task;
    fnReaderTask fnTask;

    QObject* obj;
    fnReaderObject fnObject;
};

HuiReader::HuiReader(HPropertyProxy* proxy) :
    mPropertyProxy(proxy),
    kXmlHui("hui"),
    kXmlVersion("version"),
    kXmlLayout("layout"),
    kXmlWidget("widget"),
    kXmlScene("scene"),
    kXmlStyle("style"),
    kXmlProperty("property"),
    kXmlObj("obj"),
    kXmlClass("class"),
    kXmlId("id"),
    kXmlName("name"),
    kXmlStyleId("styleid"),
    kXmlFile("file"),
    kXmlLayoutConfig("ltconfig"),
    kXmlLayoutVBox("vbox"),
    kXmlLayoutHBox("hbox"),
    kXmlLayoutGrid("grid"),
    kXmlLayoutAnchor("anchor"),
    kPrexSkip("skip:"),
    kPrexProxy("proxy:"),
    kXmlInvoke("invoke"),
    kXmlMethod("method"),
    kXmlArg("arg"),
    kXmlType("type")
{
}

bool HuiReader::loadXml(QByteArray& bytes, const QString& xml,const QString& xmlpath)
{
    QString xmlfile;
    if (xmlpath.size()>1) {//Absolute path
        if (QDir::isAbsolutePath(xmlpath+xml))
            xmlfile = xmlpath + xml;
        else
            xmlfile = xml;
    }
    else {
        xmlfile = xml;
    }
    bytes = HRESMGR->loadData(xmlfile);
    return (bytes.length()<50) ? false : true;
}

bool HuiReader::createStyle(const QString& xml, const QString& xmlpath, HStyle* style )
{
    //todo push task to queue
    HuiTask task;
    task.flags().isStyle = 1;
    task.mXmlPath = xmlpath;
    task.mStyle = style;
    return createWithTask(&task,xml,xmlpath);
}

bool HuiReader::createStyle(const char* data, HStyle* style )
{
    //todo push task to queue
    HuiTask task;
    task.flags().isStyle = 1;
    task.mStyle = style;
    return createWithTask(&task,data);
}

QList<QWidget*> HuiReader::createWidget(const QString& xml, const QString& xmlpath, QWidget* parent)
{
    //todo push task to queue
    HuiTask task;

    task.flags().isQObject = 1;
    task.flags().isQWidget = 1;
    task.setFlagsWithQWidget(parent);

    task.mXmlPath = xmlpath;
    task.mObj = parent;
    task.mObjType = USEOBJTYPE(QWidget);
    if (createWithTask(&task,xml,xmlpath)) {
        //pop bask from queue
        return task.mWidgets;
    }
    return QList<QWidget*>();
}

QList<QWidget*> HuiReader::createWidget(const char* data, QWidget *parent)
{
    //todo push task to queue
    HuiTask task;

    task.flags().isQObject = 1;
    task.flags().isQWidget = 1;
    task.setFlagsWithQWidget(parent);

    task.mObj = parent;
    task.mObjType = USEOBJTYPE(QWidget);
    if (createWithTask(&task,data)) {
        return task.mWidgets;
    }
    return QList<QWidget*>();
}

bool HuiReader::createChild(const QString& xml, const QString& xmlpath, HGWidget* parent)
{
    Q_UNUSED(xml);
    Q_UNUSED(xmlpath);
    if (!parent) return false;

    //todo push task to queue
    HuiTask task;

    task.flags().isQObject = 1;
    task.flags().isGWidget = 1;
    task.setFlagsWithHGWidget(parent);

    task.mXmlPath = xmlpath;
    task.mObj = parent;
    task.mObjType = USEOBJTYPE(HGWidget);

    return createWithTask(&task,xml,xmlpath);
}

bool HuiReader::createChild(const char* data, HGWidget *parent)
{
    Q_UNUSED(data);
    if (!parent) return false;

    //todo push task to queue
    HuiTask task;

    task.flags().isQObject = 1;
    task.flags().isGWidget = 1;
    task.setFlagsWithHGWidget(parent);

    task.mObj = parent;
    task.mObjType = USEOBJTYPE(HGWidget);

    return createWithTask(&task,data);
}

bool HuiReader::createChild(const QString& xml, const QString& xmlpath, HGView* parent)
{
    if (!parent) return false;

    //todo push task to queue
    HuiTask task;
    task.flags().isQObject = 1;
    task.flags().isQWidget =  1;
    task.setFlagsWithQWidget(parent);

    task.mXmlPath = xmlpath;
    task.mObj = parent;
    task.mObjType = USEOBJTYPE(HGView);

    return createWithTask(&task,xml,xmlpath);
}

bool HuiReader::createChild(const char* data, HGView *parent)
{
    Q_UNUSED(data);
    if (!parent) return false;

    //todo push task to queue
    HuiTask task;
    task.flags().isQObject = 1;
    task.flags().isQWidget =  1;
    task.setFlagsWithQWidget(parent);

    task.mObj = parent;
    task.mObjType = USEOBJTYPE(HGView);

    return createWithTask(&task,data);
}

bool HuiReader::createWithTask(HuiTask* task, const char* data)
{
    QXmlStreamReader reader(data);
    if (reader.hasError()) {
        Q_ASSERT(0);
        return false;
    }
    return startWithXmlReader(task,&reader);
}

bool HuiReader::createWithTask(HuiTask* task, const QString& xml, const QString& xmlpath)
{
    QByteArray bytes;
    if (!loadXml(bytes, xml, xmlpath))
        return false;

    QXmlStreamReader reader(bytes);
    if (reader.hasError()) {
        Q_ASSERT(0);
        return false;
    }
    return startWithXmlReader(task,&reader);
}

/** support header: <layout>  ; <property> ; <widget> ; <style> ; <scene> */
bool HuiReader::startWithXmlReader(HuiTask* task, QXmlStreamReader* reader)
{
    long hr = -1;
    bool ok = false;
    while (!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->readNext();
        if(token == QXmlStreamReader::StartElement) {
            if (!ok)
            {
                if (reader->name() == kXmlHui) {
                    QXmlStreamAttributes attri = reader->attributes();
                    if (!attri.hasAttribute(kXmlVersion)) {
                        return false;
                    }
                    ok = true;
                }
                else{
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlStyle) {
                if (task->canCreateStyle()) {
                    readStyleWithXmlReader(reader,task,&hr);
                    task->installStyle();
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlWidget) {
                if (task->canCreateWidget()) {
                    createWidgetWithXmlReader(reader,task,&hr);
                    //to do add widget to list
                    task->addWidget(mPropertyProxy);
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlLayout) {
                if (task->canCreateLayout()) {
                    readLayoutWithXmlReader(reader,task, &hr);
                }
                else {
                    Q_ASSERT(0);
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlScene) {
                if (task->canCreateScene()) {
                    HuiNextKeyMap next;
                    next[kXmlWidget] = HuiNextKey(task,&HuiReader::addWidgetToSceneWithXmlReader,NULL,NULL);
                    QSharedPointer<HGSceneItem> scene = createScene(task);
                    readKeyWithXmlReader(reader,scene.data(), kXmlScene,next);
                }
                else {
                    Q_ASSERT(0);
                    reader->skipCurrentElement();
                }
            }
            else if(reader->name() == kXmlProperty) {
                readProperty(reader, task->qObject(), task->mPropertys);
            }
            else if(reader->name() == kXmlInvoke) {
                readInvoke(reader,task->qObject());
            }
            else { //other name
                reader->skipCurrentElement();
            }
        }
    }
    Q_ASSERT(!reader->hasError());
    return (hr==0);
}

bool HuiReader::createWidget(HuiTask* task,const HClassInfo& clsinfo, long *hr)
{
    int func = task->findFunc(clsinfo.mClsName.data());
    if (func==-1) {
        Q_ASSERT(0);
        return false;
    }
    //todo create object
    switch(func) {
    case 0: {// HQWidget , HGView OR based QWidget
        //qDebug("create QWidget classname=%s objname=%s",clsinfo.mClsName.data(),clsinfo.mObjName.data());
        HCreateParam param;
        QWidget* parent = task->qWidget();
        QWidget* widget = HFACTORY->createQWidget(clsinfo, parent, param);
        if (!param.hasError()) {
            task->createChild();
            task->mChild->mObj = widget;
            task->mChild->mObjType = param.type();
            task->mChild->flags().isQObject = 1;
            task->mChild->flags().isQWidget = 1;
            task->mChild->setFlagsWithQWidget(widget);
        }
        else{// exception
            Q_ASSERT(NULL==widget);
        }
        *hr = param.error();
        break;
    }
    case 1: {//HGWidget
        //qDebug("create HGWidget classname=%s objname=%s,styleid=%s",clsinfo.mClsName.data(),clsinfo.mObjName.data(),clsinfo.mStyleId.data());
        HCreateParam param;
        QGraphicsWidget* parent = task->gWidget();
        HGWidget* item = HFACTORY->createGWidget(clsinfo, parent, param);
        if (!param.hasError()) {
            Q_ASSERT(item->isWidget());

            item->setParent(parent);
            task->createChild();
            task->mChild->mObj = item;
            task->mChild->mObjType = param.type();
            task->mChild->flags().isQObject = 1;
            task->mChild->flags().isGWidget = 1;
            task->mChild->setFlagsWithHGWidget(item);

            *hr = param.error();
        }
        else {
            Q_ASSERT(NULL==item);
        }
        break;
    }
    case 2: {//QGraphicsItem
        //qDebug("create QGraphicsItem classname=%s objname=%s styleid=%s",clsinfo.mClsName.data(),clsinfo.mObjName.data(),clsinfo.mStyleId.data());
        HCreateParam param;
        QGraphicsItem* item = HFACTORY->createGItem(clsinfo, task->gItem(), param);
        if (!param.hasError()) {
            task->createChild();
            task->mChild->mObj = item;
            task->mChild->mObjType = param.type();
            task->mChild->flags().isQGItem = 1;
            task->mChild->setFlagsWithHGItem(item);
            *hr = param.error();
        }
        else {
            Q_ASSERT(NULL==item);
        }
        break;
    }
    case 3 :{
        //qDebug("create object classname=%s objname=%s,styleid=%s",clsinfo.mClsName.data(),clsinfo.mObjName.data(),clsinfo.mStyleId.data());
        HCreateParam param;
        QObject* obj = HFACTORY->createObject(clsinfo, task->qObject(), param);
        if (!param.hasError()) {
            task->createChild();
            task->mChild->mObj = obj;
            task->mChild->mObjType = param.type();
            task->mChild->flags().isQObject = 1;
            *hr = param.error();
        }
        else {
            Q_ASSERT(NULL==obj);
        }
        break;
    }
    default: {// other QObject not support
        break;
    }
    }
    return (task->mChild && (task->mChild->mObj != NULL));
}

void HuiReader::createWidgetWithXmlReader(QXmlStreamReader* reader,HuiTask* task, long *hr)
{
    // get class info attribute
    QXmlStreamAttributes attris = reader->attributes();
    HClassInfo clsinfo(attris.value(kXmlClass).toString(),
                       attris.value(kXmlStyleId).toString(),
                       attris.value(kXmlName).toString());
    if (!clsinfo.isValid()) {
        reader->skipCurrentElement();
        return;
    }

    if (!createWidget(task,clsinfo,hr)) {
        Q_ASSERT(0);
        reader->skipCurrentElement();
        return ;
    }

    //qDebug("HuiReader::create widget Begin");
    task->flags().isXmlWidget = 1;
    HuiTask* child = task->mChild;
    child->mStyle = task->mStyle; // can use parent's style
    reader->readNext();

    while(!reader->hasError() && !reader->atEnd()) {
        QXmlStreamReader::TokenType token = reader->tokenType();

        if (token == QXmlStreamReader::StartElement) {
            if (reader->name() == kXmlProperty) {// object property
                readProperty(reader,child->qObject(),child->mPropertys);
            }
            else if (reader->name() == kXmlLayoutConfig) {
                readKeyWithXmlReader(reader,&child->mLayoutConfig,kXmlLayoutConfig);
            }
            else if(reader->name() == kXmlInvoke) {
                readInvoke(reader,child->qObject());
            }

            else if (reader->name() == kXmlLayoutVBox) {
                HuiNextKeyMap next;
                next[kXmlLayout] = HuiNextKey(child,&HuiReader::readLayoutWithXmlReader,NULL,NULL);
                HLayout* layout = createLayout(child,HEnums::kVBox);
                readKeyWithXmlReader(reader,layout, kXmlLayoutVBox,next);
            }
            else if (reader->name() == kXmlLayoutHBox) {
                HuiNextKeyMap next;
                next[kXmlLayout] = HuiNextKey(child,&HuiReader::readLayoutWithXmlReader,NULL,NULL);
                HLayout* layout = createLayout(child,HEnums::kHBox);
                readKeyWithXmlReader(reader,layout, kXmlLayoutHBox,next);
            }
            else if (reader->name() == kXmlLayoutGrid) {
                HuiNextKeyMap next;
                next[kXmlLayout] = HuiNextKey(child,&HuiReader::readLayoutWithXmlReader,NULL,NULL);
                HLayout* layout = createLayout(child,HEnums::kGrid);
                readKeyWithXmlReader(reader,layout, kXmlLayoutGrid,next);
            }
            else if (reader->name() == kXmlLayoutAnchor) {
                HuiNextKeyMap next;
                next[kXmlLayout] = HuiNextKey(child,&HuiReader::readLayoutWithXmlReader,NULL,NULL);
                HLayout* layout = createLayout(child,HEnums::kAnchor);
                readKeyWithXmlReader(reader,layout, kXmlLayoutAnchor,next);
            }
            else if (reader->name() == kXmlStyle) {
                readStyleWithXmlReader(reader,child,hr);
                child->installStyle();
            }
            else if (reader->name() == kXmlWidget) {
                if (child->canCreateWidget()) {
                    createWidgetWithXmlReader(reader,child,hr);
                    child->addWidget(mPropertyProxy);
                }
                else {
                    Q_ASSERT(0);
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlScene) {
                if (child->canCreateScene()) {
                    HuiNextKeyMap next;
                    next[kXmlWidget] = HuiNextKey(child,&HuiReader::addWidgetToSceneWithXmlReader,NULL,NULL);
                    QSharedPointer<HGSceneItem> scene = createScene(child);
                    readKeyWithXmlReader(reader,scene.data(), kXmlScene,next);
                }
                else {
                    Q_ASSERT(0);
                    reader->skipCurrentElement();
                }
            }
            else {//other name skip
                reader->skipCurrentElement();
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlWidget) break;
        }
        reader->readNext();
    }
    task->flags().isXmlWidget = 0;
    //qDebug("HuiReader::create widget End,child property size=%d",child->mPropertys.size());
    return;
}

HLayout* HuiReader::createLayout(HuiTask* task, HEnums::HLayoutType type)
{
    if (task->isHGWidget()) {
        HGLayout* l = NULL;
        HGWidget* w = task->objCast<HGWidget>();
        if (w->layoutType() != type) {
            l = new HGLayout(w);
            l->setLayoutType(type);
            w->setLayout(l);
        }
        else
            l = w->layout();

        task->flags().isGLayout = l?1:0;
        return l;
    }
    else if(task->isHQWidget()) {
        HQLayout* l = NULL;
        HQWidget* w = task->objCast<HQWidget>();
        if (w->layoutType() != type) {
            task->flags().isQLayout = 1;
            l = new HQLayout(w);
            l->setLayoutType(type);
            w->setLayout(l);

        }
        else
            l = w->layout();

        task->flags().isQLayout = l?1:0;
        return l;
    }
    else if(task->isHGView()) {
        HQLayout* l = NULL;
        HGView* w = task->objCast<HGView>();
        if (w->layoutType() != type) {
            l = new HQLayout(w);
            l->setLayoutType(type);
            w->setLayout(l);
        }
        else
            l = w->layout();

        task->flags().isQLayout = l?1:0;
        return l;
    }
    return NULL;
}

void HuiReader::layoutFileLink(QXmlStreamReader* reader,HuiTask* task)
{// support file
    QXmlStreamAttributes attris = reader->attributes();
    if (!attris.hasAttribute(kXmlFile))
        return ;

    HuiTask::Flags flags;
    flags.isGLayout = task->flags().isGLayout;
    flags.isQLayout = task->flags().isQLayout;
    HuiTask::SaveFlags(task,flags);
    createWithTask(task,attris.value(kXmlFile).toString(),task->mXmlPath);
}

void HuiReader::readLayoutWithXmlReader(QXmlStreamReader* reader,HuiTask* task, long *hr)
{
    Q_UNUSED(hr);
    layoutFileLink(reader,task);

    //qDebug("HuiReader::createLayout Begin");
    task->flags().isXmlLayout = 1;

    HuiNextKeyMap next;
    next[kXmlStyle] = HuiNextKey(task,&HuiReader::readStyleWithXmlReader,NULL,NULL);
    next[kXmlWidget] = HuiNextKey(task,&HuiReader::addWidgetToLayoutWithXmlReader,NULL,NULL);
    readKeyWithXmlReader(reader,NULL,kXmlLayout,next);

    task->flags().isXmlLayout = 0;
    //qDebug("HuiReader::createLayout End");
}

void HuiReader::addWidgetToLayoutWithXmlReader(QXmlStreamReader* reader,HuiTask* task, long *hr)
{// only one <layout></layout>
    createWidgetWithXmlReader(reader,task,hr);
    task->addLayout(mPropertyProxy);
}

QSharedPointer<HGSceneItem> HuiReader::createScene(HuiTask* task)
{
    QSharedPointer<HGSceneItem> scene;
    HGView* view = task->objCast<HGView>();
    scene = view->sceneItem();
    if (!scene) {
      scene = QSharedPointer<HGSceneItem>(new HGSceneItem(view));
      view->setSceneItem(scene);
    }
    task->flags().isScene = 1;
    return scene;
}

void HuiReader::addWidgetToSceneWithXmlReader(QXmlStreamReader* reader,HuiTask* task, long *hr)
{
    //qDebug("HuiReader::createScene");
    task->flags().isXmlScene = 1;

    //todo try create one child widget
    createWidgetWithXmlReader(reader,task,hr);
    task->addScene();

    task->flags().isXmlScene = 0;
    return ;
}

void HuiReader::styleFileLink(QXmlStreamReader* reader,HuiTask* task)
{// support file link
    QXmlStreamAttributes attris = reader->attributes();
    if (!attris.hasAttribute(kXmlFile))
        return ;
    HuiTask::Flags flags;
    flags.isStyle = 1;
    HuiTask::SaveFlags(task,flags);
    createWithTask(task,attris.value(kXmlFile).toString(),task->mXmlPath);
}

void HuiReader::readStyleWithXmlReader(QXmlStreamReader* reader,HuiTask* task, long *hr)
{
    Q_UNUSED(hr);

    styleFileLink(reader,task);

    HuiNextKeyMap next;
    next[kXmlObj] = HuiNextKey(task,&HuiReader::createStyleWithXmlReader,NULL,NULL);
    readKeyWithXmlReader(reader,NULL,kXmlStyle,next);
}

void HuiReader::createStyleWithXmlReader(QXmlStreamReader* reader,HuiTask* task, long *hr)
{
    Q_UNUSED(hr);

    //qDebug("HuiReader::createStyle Begin");
    task->createStyle();

    QSharedPointer<HBaseStyle> style;
    QXmlStreamAttributes attr = reader->attributes();
    HClassInfo cls(attr.value(kXmlClass).toString(),
                   attr.value(kXmlStyleId).toString(),
                   attr.value(kXmlName).toString());
    style = task->style()->create(cls);
    if (style) {
        HuiNextKeyMap next;
        next[kXmlObj] = HuiNextKey(NULL,NULL,style.data(),&HuiReader::readChildStyle);
        readKeyWithXmlReader(reader,style.data(),kXmlObj,next);
    }
    else {
        reader->skipCurrentElement();
    }
    //qDebug("HuiReader::createStyle End");
    return ;
}

void HuiReader::readChildStyle(QXmlStreamReader* reader,QObject* obj)
{
    QXmlStreamAttributes attris = reader->attributes();
    QString id = attris.value(kXmlId).toString();
    HClassInfo cls(attris.value(kXmlClass).toString(),
                   attris.value(kXmlStyleId).toString(),
                   attris.value(kXmlName).toString());
    QMetaObject::invokeMethod(obj,"addChild",Q_ARG(const QString&,id),Q_ARG(const HClassInfo&, cls));
    reader->skipCurrentElement();
}

void HuiReader::readKeyWithXmlReader(QXmlStreamReader* reader,QObject* obj,const QLatin1String& endKey,
                                     const QMap<QString,HuiNextKey>& next)
{
    QList<HIdValue> style_propertys;
    reader->readNext();
    while(!reader->hasError() && !reader->atEnd()) {
        QXmlStreamReader::TokenType token = reader->tokenType();

        if (token == QXmlStreamReader::StartElement) {

            if(reader->name() == kXmlProperty) {
                readProperty(reader, obj, style_propertys);
            }
            else if(reader->name() == kXmlInvoke) {
                readInvoke(reader,obj);
            }
            else {
                HuiNextKeyMap::const_iterator iter = next.find(reader->name().toString());
                if (iter != next.end()) {

                    if(iter->fnObject && iter->obj) {
                        (this->*(iter->fnObject))(reader,iter->obj);
                    }
                    else if(iter->fnTask && iter->task) {
                        long hr = 0;
                        (this->*(iter->fnTask))(reader,iter->task,&hr);
                    }
                    else
                      reader->skipCurrentElement();
                }
                else {
                    reader->skipCurrentElement();
                }
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            if(reader->name() == endKey)
                break;
        }
        reader->readNext();
    }
    HuiTask::setProperty(obj,style_propertys);
}

void HuiReader::readProperty(QXmlStreamReader* reader, QObject* obj, QList<HIdValue>& propertys)
{
    if (!obj) {
        reader->skipCurrentElement();
        return;
    }
    QXmlStreamAttributes attris = reader->attributes();
    if(!attris.hasAttribute(kXmlId)) {
        reader->skipCurrentElement(); // skipping any child nodes
        return ;
    }
    QString id = attris.value(kXmlId).toString();
    reader->readNext();

    while(!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->tokenType();

        if(token == QXmlStreamReader::StartElement) {
            reader->skipCurrentElement();
        }
        else if (token == QXmlStreamReader::Characters) {// id , text = isWhitespace() or isCDATA()
            if (!reader->isWhitespace()) {

                bool skip = false;
                bool proxy = false;
                if ((skip = id.startsWith(kPrexSkip))) {
                    id = id.mid(kPrexSkip.size());
                }
                else if((proxy = id.startsWith(kPrexProxy))) {
                    id = id.mid(kPrexProxy.size());
                }

                if (skip||proxy) {
                    propertys.append(HIdValue(id,reader->text().toString(),proxy));
                }
                else if (!HuiTask::setProperty(obj,id,reader->text().toString())) {
                    propertys.append(HIdValue(id,reader->text().toString(),true));
                }
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlProperty)
                break;
        }
        reader->readNext();
    }
}

void HuiReader::readInvoke(QXmlStreamReader* reader,QObject* obj)
{
    if (!obj) {
        reader->skipCurrentElement();
        return;
    }
    QXmlStreamAttributes attris = reader->attributes();
    QByteArray method = attris.value(kXmlMethod).toLocal8Bit();

    QVector<QVariant> args;
    reader->readNext();
    while(!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->tokenType();

        if(token == QXmlStreamReader::StartElement) {
            if (reader->name() == kXmlArg) {
                readArg(reader,args);
            }
            else {
                reader->skipCurrentElement();
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlInvoke)
                break;
        }
        reader->readNext();
    }
    HuiTask::invoke(obj,method.data(),args);
}

void HuiReader::readArg(QXmlStreamReader* reader, QVector<QVariant>& args)
{
    QXmlStreamAttributes attris = reader->attributes(); 
    QString argType = attris.value(kXmlType).toString();
    if (argType.size()<3) {
        reader->skipCurrentElement();
        return ;
    }
    QString argValue;

    reader->readNext();
    while(!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->tokenType();

        if(token == QXmlStreamReader::StartElement) {
            reader->skipCurrentElement();
        }
        else if (token == QXmlStreamReader::Characters) {// id , text = isWhitespace() or isCDATA()
            if (!reader->isWhitespace()) {
                argValue = reader->text().toString();
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlArg)
                break;
        }
        reader->readNext();
    }  
    readArg(argType,argValue,args);
}

void HuiReader::readArg(const QString& type,const QString& argValue, QVector<QVariant>& args)
{
    long hr = -1;
    if (type == QLatin1String("string"))
        args.append(HuiCreator::convertQVariant_QString(argValue, &hr));

    else if (type == QLatin1String("color"))
        args.append(HuiCreator::convertQVariant_QColor(argValue, &hr));

    if (type == QLatin1String("brush"))
        args.append(HuiCreator::convertQVariant_QBrush(argValue, &hr));

    else if (type == QLatin1String("margins"))
        args.append(HuiCreator::convertQVariant_QMargins(argValue, &hr));

    else if (type == QLatin1String("rect"))
        args.append(HuiCreator::convertQVariant_QRect(argValue, &hr));

    else if (type == QLatin1String("rectF"))
        args.append(HuiCreator::convertQVariant_QRectF(argValue, &hr));

    else if (type == QLatin1String("point"))
        args.append(HuiCreator::convertQVariant_QPoint(argValue, &hr));

    else if (type == QLatin1String("pointF"))
        args.append(HuiCreator::convertQVariant_QPointF(argValue, &hr));

    else if (type == QLatin1String("sizeF"))
        args.append(HuiCreator::convertQVariant_QSizeF(argValue, &hr));

    else if (type == QLatin1String("size"))
        args.append(HuiCreator::convertQVariant_QSize(argValue, &hr));

    else if (type == QLatin1String("int"))
        args.append(HuiCreator::convertQVariant_int(argValue, &hr));

    else if (type == QLatin1String("qreal"))
        args.append(HuiCreator::convertQVariant_qreal(argValue, &hr));

    else if (type == QLatin1String("bool"))
        args.append(HuiCreator::convertQVariant_bool(argValue, &hr));
}


