#ifndef HUIREADER_H
#define HUIREADER_H

#include "hconfig.h"
#include <QObject>

/** .xml
 * <?xml version="1.0" encoding="UTF-8"?>
 * <ui version="1.0">
 * <css>
 *    <obj clsname="HCssBackground" id=" " />
 *    <obj clsname="HCssWidget" id="" />
 *    <obj clsname="HCssFrame" id="">
 *      <property id=""></property>
 *      <property id=""></property>
 *    </obj>
 *    <obj clsname="HCssObject" id="">
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
class QGraphicsItem;
class QWidget;

class H_API HUIReader : public QObject
{
    Q_OBJECT
public:
    explicit HUIReader(QObject *parent = 0);

public:
    HGWidget* createGWidget(const QString& xml, const QString& xmlpath, QGraphicsItem *parent);
    HGWidget* createGWidgetFromData(const char* data, QGraphicsItem *parent);

    HGView* createGView(const QString& xml,const QString& xmlpath, QWidget *parent);
    HGView* createGViewFromData(const char* data, QWidget *parent);
signals:

public slots:

};

#endif // HUIREADER_H
