#ifndef HUIREADER_H
#define HUIREADER_H

#include "hbasestyle.h"

/** .xml
 *@see lt.main.xml
*/
class HGWidget;
class HGView;
class QXmlStreamReader;
class QGraphicsItem;
class QWidget;
class HStyle;

class H_API HUIReader
{
public:
    HUIReader();

public:
    HGWidget* createGWidget(const QString& xml, QGraphicsItem *parent, const QString& xmlpath=QString());
    HGWidget* createGWidgetFromData(const char* data, QGraphicsItem *parent);
    bool createChildWithGWidget(const QString& xml,HGWidget* parent,const QString& xmlpath=QString());
    bool createChildWithGWidgetFromData(const char* data, HGView *parent);

    HGView* createGView(const QString& xml, QWidget *parent,const QString& xmlpath=QString());
    HGView* createGViewFromData(const char* data, QWidget *parent);
    bool createChildWithGView(const QString& xml, HGView *parent,const QString& xmlpath=QString());
    bool createChildWithGViewFromData(const char* data, HGView *parent);

private:
    bool loadXml(QByteArray& bytes, const QString& xml,const QString& xmlpath);

    /** for widget xml */
    void createWidgetWithXmlReader(QXmlStreamReader* reader, long* hr);

    /** for style xml */
    HStyleMap createStyleWithXmlReader(QXmlStreamReader* reader, long* hr);

    bool readerWithXmlReader(QXmlStreamReader* reader);
    void readContextWithXmlReader(QXmlStreamReader* reader, long *hr);
    void readSceneWithXmlReader(QXmlStreamReader* reader, long *hr);
    void readLayoutWithXmlReader(QXmlStreamReader* reader, long *hr);

    void readProperty(QXmlStreamReader* reader, const QString& id, QObject* item);
    void readClassInfo(QXmlStreamReader* reader, const QString& id, QObject* item);
    void setProperty(QObject* item, const QString& id, const QString& attr);

    int findFunc(const char* clsname);
    QObject* createObject(const HClassInfo& clsinfo, QObject* parent,long *hr);
    void* createGItem(const HClassInfo& clsinfo, QGraphicsItem* parent,long *hr);
    QWidget* createQWidget(const HClassInfo& clsinfo, QWidget* parent,long *hr);

    friend class HStyle;
};

#endif // HUIREADER_H
