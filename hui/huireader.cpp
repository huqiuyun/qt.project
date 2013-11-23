#include "HuiReader.h"
#include "hgwidget.h"
#include "hgview.h"
#include "hcore.h"
#include "hstyle.h"
#include "hfactory.h"
#include "hqwidget.h"
#include "hresourcemgr.h"
#include "hgscenestyle.h"
#include "hattributeproxy.h"
#include "huitask.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QGraphicsLayoutItem>
#include <QXmlStreamReader>
#include <QDir>

HuiReader::HuiReader() :
    mUseProperty(false),
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
    kXmlClsname("clsname"),
    kXmlName("name"),
    kXmlStyleId("styleid"),
    kXmlLayoutIndex("layoutIndex"),
    kXmlFile("file"),
    kXmlMain("main"),
    kPrexSkip("skip:"),
    kPrexProxy("proxy:")
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

    task.flags().isQWidget =  1;
    task.setFlagsWithQWidget(parent);

    task.mObj = parent;
    task.mObjType = USEOBJTYPE(HGView);

    return createWithTask(&task,data);
}

bool HuiReader::createWithTask(HuiTask* task, const char* data)
{
    QXmlStreamReader reader(data);
    return startWithXmlReader(task,&reader);
}

bool HuiReader::createWithTask(HuiTask* task, const QString& xml, const QString& xmlpath)
{
    QByteArray bytes;
    if (!loadXml(bytes, xml, xmlpath))
        return false;
    //
    QXmlStreamReader reader(bytes);
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
                    mUseProperty = ((attri.value("useproperty") == QLatin1String("true")));
                    ok = true;
                }
                else{
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlStyle) {
                if (task->canCreateStyle()) {
                    createStyleWithXmlReader(task,reader,&hr);
                    task->installStyle();
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlWidget) {
                if (task->canCreateWidget()) {
                    createWidgetWithXmlReader(task,reader,&hr);
                    //to do add widget to list
                    task->addWidgetToList();
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlLayout) {
                if (task->canCreateLayout()) {
                    createLayoutWithXmlReader(task,reader, &hr);
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlScene) {
                if (task->canCreateScene()) {
                    createSceneWithXmlReader(task, reader, &hr);
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else if(reader->name() == kXmlProperty) {
                readProperty(reader, task->objCast<QObject>(),task->mPropertys);
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
        HCreateParam param;
        QWidget* parent = task->parentQWidget();
        QWidget* widget = HFACTORY->createQWidget(clsinfo, parent, param);
        if (!param.hasError()) {
            task->generateChild();
            task->mChild->mObj = widget;
            task->mChild->mObjType = param.type();
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
        HCreateParam param;
        QGraphicsWidget* parent = task->parentGWidget();
        HGWidget* item = HFACTORY->createGWidget(clsinfo, parent, param);
        if (!param.hasError()) {
            Q_ASSERT(item->isWidget());

            item->setParent(parent);
            task->generateChild();
            task->mChild->mObj = item;
            task->mChild->mObjType = param.type();
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

        HCreateParam param;
        QGraphicsItem* item = HFACTORY->createGItem(clsinfo, task->parentGItem(), param);
        if (!param.hasError()) {
            task->generateChild();
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
    default: {
        break;
    }
    }
    return (task->mChild && (task->mChild->mObj != NULL));
}

/** support:
  * <widget>
  *   <scene/>
  *   <property/>
  *   <layout />
  * </widget>
*/
void HuiReader::createWidgetWithXmlReader(HuiTask* task, QXmlStreamReader* reader, long *hr)
{
    // get class info attribute
    QXmlStreamAttributes attris = reader->attributes();
    HClassInfo clsinfo(attris.value(kXmlClsname).toString(),
                       attris.value(kXmlStyleId).toString(),
                       attris.value(kXmlName).toString());
    if (!clsinfo.isValid()) {
        return;
    }
    //todo create widget
    if (!createWidget(task,clsinfo,hr)) {
        Q_ASSERT(0);
        return ;
    }
    task->flags().isXmlWidget = 1;

    HuiTask* child = task->mChild;
    child->mStyle = task->mStyle; // can use parent's style
    reader->readNext();
    do {
        QXmlStreamReader::TokenType token = reader->tokenType();
        if (token == QXmlStreamReader::StartElement) {
            if (reader->name() == kXmlProperty) {// object property
                readProperty(reader,child->qObject(),child->mPropertys);
            }
            else if (reader->name() == kXmlLayout) {
                if (child->canCreateLayout()) {
                    createLayoutWithXmlReader(child,reader,hr);
                }
                else {
                    Q_ASSERT(0);
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlStyle) {
                createStyleWithXmlReader(child,reader,hr);
                child->installStyle();
            }
            else if (reader->name() == kXmlWidget) {
                if (child->canCreateWidget()) {
                    createWidgetWithXmlReader(child,reader,hr);
                    child->addWidget(isUseProperty());
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else if (reader->name() == kXmlScene) {
                if (child->canCreateScene()) {
                    createSceneWithXmlReader(child,reader,hr);
                }
                else {
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

    }while(!reader->hasError() && !reader->atEnd());
    task->flags().isXmlWidget = 0;
    return;
}

void HuiReader::layoutFileLink(HuiTask* task,QXmlStreamReader* reader)
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

void HuiReader::createLayoutWithXmlReader(HuiTask* task,QXmlStreamReader* reader, long *hr)
{// only one <layout></layout>
    layoutFileLink(task,reader);

    task->flags().isXmlLayout = 1;
    reader->readNext();
    while (!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->tokenType();
        if(token == QXmlStreamReader::StartElement) {
            if (reader->name() == kXmlStyle) {
                createStyleWithXmlReader(task,reader,hr);
            }
            else if (reader->name() == kXmlWidget) {
                //todo try create child widget
                createWidgetWithXmlReader(task,reader,hr);
                task->addWidget(isUseProperty());
            }
            else {
                reader->skipCurrentElement();
            }
        }
        else if(token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlLayout) break;
        }
        reader->readNext();
    }
    task->flags().isXmlLayout = 0;
    return ;
}

void HuiReader::createSceneWithXmlReader(HuiTask* task,QXmlStreamReader* reader, long *hr)
{
    task->flags().isXmlScene = 1;
    QXmlStreamAttributes attris = reader->attributes();
    bool main = (attris.value(kXmlMain) == QLatin1String("true"));

    reader->readNext();
    while (!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->tokenType();
        if(token == QXmlStreamReader::StartElement) {
            if (reader->name() == kXmlWidget) {
                //todo try create child widget
                createWidgetWithXmlReader(task,reader,hr);
                task->addScene(main);
            }
            else {//other ignore
                reader->skipCurrentElement();
            }
        }
        else if(token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlScene) break;
        }
        reader->readNext();
    }
    task->flags().isXmlScene = 0;
    return ;
}

void HuiReader::styleFileLink(HuiTask* task, QXmlStreamReader* reader)
{// support file link
    QXmlStreamAttributes attris = reader->attributes();
    if (!attris.hasAttribute(kXmlFile))
        return ;
    HuiTask::Flags flags;
    flags.isStyle = 1;
    HuiTask::SaveFlags(task,flags);
    createWithTask(task,attris.value(kXmlFile).toString(),task->mXmlPath);
}

void HuiReader::createStyleWithXmlReader(HuiTask* task,QXmlStreamReader* reader, long *hr)
{
    Q_UNUSED(hr);
    styleFileLink(task,reader);
    reader->readNext();
    QSharedPointer<HBaseStyle> styleobj;
    do {
        QXmlStreamReader::TokenType token = reader->tokenType();
        if (token == QXmlStreamReader::StartElement) {
            if (reader->name() == kXmlObj) {
                /* Read attribute */
                QXmlStreamAttributes attris = reader->attributes();
                if(!attris.hasAttribute(kXmlClsname)) {
                    reader->skipCurrentElement(); // skipping any child nodes
                    reader->readNext();
                    continue;
                }
                if (!attris.hasAttribute(kXmlStyleId)) {
                    reader->skipCurrentElement(); //skipping any child nodes
                    reader->readNext();
                    continue;
                }
                // 生成
                HString styleid(attris.value(kXmlStyleId).toString());
                HString clsname(attris.value(kXmlClsname).toString());

                task->generateStyle();
                styleobj = task->style()->create(styleid.data(),clsname.data());
            }
            else if(reader->name() == kXmlProperty) {
                if (styleobj) {
                    readProperty(reader, styleobj.data(),task->mPropertys);
                }
                else {
                    reader->skipCurrentElement();
                }
            }
            else {//other skip
                reader->skipCurrentElement();
            }
        }
        else if (token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlStyle) {
                break;
            }
            else if(reader->name() == kXmlObj) {
                styleobj = QSharedPointer<HBaseStyle>(NULL);
                //next obj node
            }
            else {//end property
            }
        }
        reader->readNext();

    }while(!reader->hasError() && !reader->atEnd());

    return ;
}

void HuiReader::readProperty(QXmlStreamReader* reader, QObject* obj,QList<HIdValue>& propertys)
{
    Q_UNUSED(propertys);
    QXmlStreamAttributes attris = reader->attributes();
    if(!attris.hasAttribute(kXmlId)) {
        reader->skipCurrentElement(); // skipping any child nodes
        return ;
    }
    QString id = attris.value(kXmlId).toString();
    reader->readNext();

    while(!reader->atEnd() && !reader->hasError()) {
        QXmlStreamReader::TokenType token = reader->tokenType();
        if (token == QXmlStreamReader::EndElement) {
            if (reader->name() == kXmlProperty)
                break;
        }
        else if(token == QXmlStreamReader::StartElement) {
            if (reader->name() == kXmlClass) {// <property> <class clsname="" name="" styleid=""/></property>
                QXmlStreamAttributes attris = reader->attributes();
                HClassInfo cls(attris.value(kXmlClsname).toString(),
                               attris.value(kXmlStyleId).toString(),
                               attris.value(kXmlName).toString());
                obj->setProperty(id.toLatin1(),cls.toQVariant());
                reader->skipCurrentElement();
            }
            else {// <property> <XXXX /> </property>
                reader->skipCurrentElement();
            }
        }
        else if (token == QXmlStreamReader::Characters) {// id , text = isWhitespace() or isCDATA()
            if (!reader->isWhitespace()) {
                QString val = reader->text().toString();
                if (id.startsWith(kPrexSkip)) {
                    propertys.append(HIdValue(id.mid(kPrexSkip.size()),val));
                }
                else {
                    HuiTask::setProperty(obj,id,val,isUseProperty());
                }
            }
        }
        else {// other token skipping,not need
        }
        reader->readNext();
    }
}


