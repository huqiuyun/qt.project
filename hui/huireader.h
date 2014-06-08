#ifndef HUIREADER_H
#define HUIREADER_H

#include "hbasestyle.h"
#include <QList>

class QXmlStreamReader;
class QGraphicsItem;
class QWidget;
class HGWidget;
class HGView;
class HQWidget;
class HStyle;
class HLayout;
class HuiTask;
class HPropertyProxy;
class HuiArg;
class HuiReader;
class HuiNextKey;
class HGSceneItem;
typedef void (HuiReader::*fnReaderTask)(QXmlStreamReader* reader,HuiTask *task, long* hr);
typedef void (HuiReader::*fnReaderObject)(QXmlStreamReader* reader,QObject *obj);

class H_API HuiReader
{
public:
    HuiReader(HPropertyProxy* proxy=NULL);

    bool createStyle(const QString& xml, const QString& xmlpath, HStyle* style );
    bool createStyle(const char* data, HStyle* style );

    QList<QWidget*> createWidget(const QString& xml, const QString& xmlpath, QWidget *parent);
    QList<QWidget*> createWidget(const char* data, QWidget *parent);
    //
    bool createChild(const QString& xml, const QString& xmlpath,HGWidget* parent);
    bool createChild(const char* data, HGWidget *parent);
    //
    bool createChild(const QString& xml, const QString& xmlpath, HGView *parent);
    bool createChild(const char* data, HGView *parent);
    //
    bool createChild(const QString& xml, const QString& xmlpath, HQWidget *parent);
    bool createChild(const char* data, HQWidget *parent);
private:
    bool loadXml(QByteArray& bytes, const QString& xml,const QString& xmlpath);

    bool createWithTask(HuiTask* task, const QString& xml, const QString& xmlpath);
    bool createWithTask(HuiTask* task, const char* data);

    bool startWithXmlReader(HuiTask* HuiTask, QXmlStreamReader* reader);

    /** for widget xml */
    void createWidgetWithXmlReader(QXmlStreamReader* reader,HuiTask* HuiTask, long* hr);
    bool createWidget(HuiTask* HuiTask,const HClassInfo& clsinfo, long *hr);

    /** for style xml <style></style>*/
    void styleFileLink(QXmlStreamReader* reader,HuiTask* task);
    void readStyleWithXmlReader(QXmlStreamReader* reader,HuiTask* task, long *hr);
    void createStyleWithXmlReader(QXmlStreamReader* reader,HuiTask *task, long* hr);
    void readChildStyle(QXmlStreamReader* reader,QObject* obj);

    QSharedPointer<HGSceneItem> createScene(HuiTask* task);
    void addWidgetToSceneWithXmlReader(QXmlStreamReader* reader,HuiTask* HuiTask, long *hr);

    HLayout* createLayout(HuiTask* task, HEnums::HLayoutType type);
    void layoutFileLink(QXmlStreamReader* reader,HuiTask* task);
    void readLayoutWithXmlReader(QXmlStreamReader* reader,HuiTask* HuiTask, long *hr);
    void addWidgetToLayoutWithXmlReader(QXmlStreamReader* reader,HuiTask* HuiTask, long *hr);

    typedef QMap<QString,HuiNextKey> HuiNextKeyMap;
    void readKeyWithXmlReader(QXmlStreamReader* reader, QObject* obj, const QLatin1String& endKey, const HuiNextKeyMap& next = HuiNextKeyMap());
    void readProperty(QXmlStreamReader* reader,QObject* obj,QList<HIdValue>& propertys);

    // invoke
    void readInvoke(QXmlStreamReader* reader,QObject* obj);
    void readArg(QXmlStreamReader* reader, QVector<QVariant>& args);
    void readArg(const QString& type, const QString& argValue, QVector<QVariant>& args);

private:
    HPropertyProxy* mPropertyProxy;
    const QLatin1String kXmlHui;
    const QLatin1String kXmlVersion;
    const QLatin1String kXmlLayout;
    const QLatin1String kXmlWidget;
    const QLatin1String kXmlScene;
    const QLatin1String kXmlStyle;
    const QLatin1String kXmlProperty;
    const QLatin1String kXmlObj;
    const QLatin1String kXmlClass;
    const QLatin1String kXmlId;
    const QLatin1String kXmlName;
    const QLatin1String kXmlStyleId;
    const QLatin1String kXmlFile;
    const QLatin1String kXmlLayoutConfig;
    const QLatin1String kXmlLayoutVBox;
    const QLatin1String kXmlLayoutHBox;
    const QLatin1String kXmlLayoutGrid;
    const QLatin1String kXmlLayoutAnchor;
    const QLatin1String kPrexSkip;
    const QLatin1String kPrexProxy;
    const QLatin1String kXmlInvoke;
    const QLatin1String kXmlMethod;
    const QLatin1String kXmlArg;
    const QLatin1String kXmlType;
    friend class HStyle;
};

#endif // HUIREADER_H
