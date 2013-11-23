#ifndef HuiReader_H
#define HuiReader_H

#include "hbasestyle.h"
#include <QList>

/** .xml
 *@see main.xml
*/
class QXmlStreamReader;
class QGraphicsItem;
class QWidget;
class HGWidget;
class HGView;
class HQWidget;
class HStyle;
class HLayoutStyle;
class HuiTask;
class HAttributeProxy;

class H_API HuiReader
{
public:
    HuiReader(HAttributeProxy* attriProxy = NULL);

public:
    bool createStyle(const QString& xml, const QString& xmlpath, HStyle* style );
    bool createStyle(const char* data, HStyle* style );

    HQWidgetList createWidget(const QString& xml, const QString& xmlpath, QWidget *parent);
    HQWidgetList createWidget(const char* data, QWidget *parent);
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

    /** for style xml <style></style>*/
    void createStyleWithXmlReader(HuiTask *task, QXmlStreamReader* reader, long* hr);

    void createSceneWithXmlReader(HuiTask* HuiTask,QXmlStreamReader* reader, long *hr);
    void createLayoutWithXmlReader(HuiTask* HuiTask,QXmlStreamReader* reader, long *hr);

    void readProperty(QXmlStreamReader* reader,QObject* obj, int objType);
    void readClassInfo(QXmlStreamReader* reader, const QString& id, QObject* obj);
    void setProperty(QObject* obj, int objType, const QString& id, const QString& attr);

    inline bool isUseProperty() const { return mUseProperty;}
private:
    HAttributeProxy* mAttriProxy;
    bool mUseProperty;
    const QLatin1String kXmlHui;
    const QLatin1String kXmlVersion;
    const QLatin1String kXmlLayout;
    const QLatin1String kXmlWidget;
    const QLatin1String kXmlScene;
    const QLatin1String kXmlStyle;
    const QLatin1String kXmlProperty;
    const QLatin1String kXmlObj;
    const QLatin1String kXmlClassinfo;
    const QString kXmlId;
    const QString kXmlClsname;
    const QString kXmlName;
    const QString kXmlStyleId;
    const QString kXmlLayoutIndex;
    const QString kXmlFile;
    const QString kXmlMain;
    friend class HStyle;
};

#endif // HuiReader_H
