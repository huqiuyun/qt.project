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
class HLayoutStyle;
class HuiTask;
class HPropertyProxy;

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
    void createWidgetWithXmlReader(HuiTask* HuiTask, QXmlStreamReader* reader, long* hr);
    bool createWidget(HuiTask* HuiTask,const HClassInfo& clsinfo, long *hr);
    void readLayoutConf(QXmlStreamReader* reader,HLayoutConf* conf);

    /** for style xml <style></style>*/
    void styleFileLink(HuiTask* task,QXmlStreamReader* reader);
    void createStyleWithXmlReader(HuiTask *task, QXmlStreamReader* reader, long* hr);
    void createObjWithXmlReader(HuiTask* task,QXmlStreamReader* reader, long *hr);

    void createSceneWithXmlReader(HuiTask* HuiTask,QXmlStreamReader* reader, long *hr);

    void layoutFileLink(HuiTask* task, QXmlStreamReader* reader);
    void createLayoutWithXmlReader(HuiTask* HuiTask,QXmlStreamReader* reader, long *hr);

    void readProperty(QXmlStreamReader* reader,QObject* obj,QList<HIdValue>& propertys);

    inline bool isUseProperty() const { return mUseProperty;}
private:
    HPropertyProxy* mPropertyProxy;
    bool mUseProperty;
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
    const QLatin1String kXmlLayoutConf;
    const QLatin1String kPrexSkip;
    const QLatin1String kPrexProxy;
    friend class HStyle;
};

#endif // HUIREADER_H
