#ifndef HUIREADER_H
#define HUIREADER_H

#include "hbasestyle.h"

/** .xml
 * <?xml version="1.0" encoding="UTF-8"?>
 * <ui version="1.0">
 * <css>
 *    <obj clsname="HCssBackground" name="" styleid=" " />
 *    <obj clsname="HCssWidget" name="" styleid="" />
 *    <obj clsname="HCssFrame" name="" styleid="">
 *      <property id=""></property>
 *      <property id=""></property>
 *    </obj>
 *    <obj clsname="HCssObject" name="" styleid="">
 *      <property id=""></property>
 *      <property id=""></property>
 *    </obj>
 * </css>
 *
 * <widget clsname="" name="" styleid="${styleid}">
 *   <css>
 *     <obj clsname="" id="${styleid}" />
 *   </css>
 *   <property key=value key=value />
 *   <widget clsname="" name="" styleid="${styleid}"/>
 *   <widget clsname="" name="" styleid="${styleid}"/>
 *
 *   <object clsname="" name="" styleid="${styleid}"/>
 *   <object clsname="" name="" styleid="${styleid}"/>
 * </widget>
 *
 * </ui>
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

    void createWidgetWithXmlReader(QXmlStreamReader* reader, long* hr);

    /** for style xml */
    HStyleMap createStyleWithXmlReader(QXmlStreamReader* reader, long* hr);

    void readProperty(QXmlStreamReader* reader, const QString& id, QObject* item);
    void readClassInfo(QXmlStreamReader* reader, const QString& id, QObject* item);
    void setProperty(QObject* item, const QString& id, const QString& attr);

    friend class HStyle;
};

#endif // HUIREADER_H
