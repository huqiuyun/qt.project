#include "huireader.h"
#include "hgwidget.h"
#include "hgview.h"
#include "hcore.h"
#include "hstyle.h"
#include "hfactory.h"
#include "hresourcemgr.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QXmlStreamReader>
#include <QMetaProperty>
#include <QDir>

HUIReader::HUIReader()
{
}


bool HUIReader::loadXml(QByteArray& bytes, const QString& xml,const QString& xmlpath)
{
    QString xmlfile;
    if (xmlpath.size()>1)
    {//Absolute path
        if (QDir::isAbsolutePath(xmlpath+xml))
            xmlfile = xmlpath + xml;
        else
            xmlfile = xml;
    }
    else
    {
        xmlfile = xml;
    }
    bytes = HRESMGR->loadData(xmlfile);
    return (bytes.length()<50) ? false : true;
}

HGWidget* HUIReader::createGWidget(const QString& xml, QGraphicsItem* parent,const QString& xmlpath)
{
    Q_UNUSED(xml);
    Q_UNUSED(xmlpath);
    Q_UNUSED(parent);

    QByteArray bytes;
    if (!loadXml(bytes , xml,xmlpath)) return NULL;

    QXmlStreamReader reader(bytes);

    Q_UNUSED(reader);
    return NULL;
}

HGWidget* HUIReader::createGWidgetFromData(const char* data, QGraphicsItem *parent)
{
    Q_UNUSED(data);
    Q_UNUSED(parent);
    return NULL;
}

bool HUIReader::createChildWithGWidget(const QString& xml,HGWidget* parent,const QString& xmlpath)
{
    Q_UNUSED(xml);
    Q_UNUSED(xmlpath);
    if (!parent) return false;
    //

    return false;
}

bool HUIReader::createChildWithGWidgetFromData(const char* data, HGView *parent)
{
    Q_UNUSED(data);
    if (!parent) return false;

    return false;
}

HGView* HUIReader::createGView(const QString& xml,QWidget* parent,const QString& xmlpath)
{
    Q_UNUSED(xml);
    Q_UNUSED(xmlpath);
    Q_UNUSED(parent);

    QByteArray bytes;
    if (!loadXml(bytes , xml,xmlpath)) return NULL;

    QXmlStreamReader reader(bytes);

    Q_UNUSED(reader);
    return NULL;
}

HGView* HUIReader::createGViewFromData(const char* data, QWidget *parent)
{
    Q_UNUSED(data);
    Q_UNUSED(parent);
    return NULL;
}

bool HUIReader::createChildWithGView(const QString& xml, HGView* parent,const QString& xmlpath)
{
    Q_UNUSED(parent);
    Q_UNUSED(xml);
    Q_UNUSED(xmlpath);

    if (!parent) return false;

    QByteArray bytes;
    if (!loadXml(bytes , xml, xmlpath)) return false;

    QXmlStreamReader reader(bytes);

    long hr = -1;
    bool ok = false;
    while(!reader.atEnd() && !reader.hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = reader.readNext();

        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if(token == QXmlStreamReader::StartElement)
        {
           if (reader.name() == QLatin1String("ui"))
           { //
               QXmlStreamAttributes attri = reader.attributes();
               if (!attri.hasAttribute("version"))
               {
                   return false;
               }
               ok = true;
           }
           else if(ok)
           {
               if (reader.name() == QLatin1String("style"))
               {//create css objects
                   createStyleWithXmlReader(&reader,&hr);
               }
               else if (reader.name() == QLatin1String("widget"))
               {//
                   createWidgetWithXmlReader(&reader,&hr);
               }
           }
        }
    }
    return hr;
}

bool HUIReader::createChildWithGViewFromData(const char* data, HGView *parent)
{
    Q_UNUSED(data);
    if (!parent) return false;

    return false;
}

void HUIReader::createWidgetWithXmlReader(QXmlStreamReader* reader, long *hr)
{
    Q_UNUSED(reader);
    *hr = -1;

    // read from xml reader, and create css object
    QXmlStreamReader::TokenType token = reader->tokenType();
    if (token != QXmlStreamReader::StartElement ||
        reader->name() != QLatin1String("widget"))
    {
        return ;
    }

    // get class info attribute
    QXmlStreamAttributes attris = reader->attributes();
    HClassInfo clsinfo(attris.value("clsname").toString(), attris.value("styleid").toString(),attris.value("name").toString());
    if (!clsinfo.isValid())
    {
        return;
    }
    //todo create widget

    reader->readNext();
    do
    {
        token = reader->tokenType();
        if ( token == QXmlStreamReader::StartElement)
        {
            if (reader->name() == QLatin1String("layout"))
            {

            }
            else if(reader->name() == QLatin1String("scene"))
            {

            }
            else if(reader->name() == QLatin1String("property"))
            {
            }
        }
        else if (token == QXmlStreamReader::EndElement)
        {
            if (reader->name() == QLatin1String("widget"))
            {

            }
            else if(reader->name() == QLatin1String("layout"))
            {

            }
            else if (reader->name() == QLatin1String("scene"))
            {

            }
            else
            {//end property
            }
        }
        reader->readNext();

    }while(!reader->hasError() && !reader->atEnd());

    *hr = reader->error();
    return;
}


HStyleMap HUIReader::createStyleWithXmlReader(QXmlStreamReader* reader, long *hr)
{
    Q_UNUSED(reader);
    HStyleMap stylemap;

    // read from xml reader, and create css object
    QXmlStreamReader::TokenType token = reader->tokenType();
    if (token != QXmlStreamReader::StartElement ||
        reader->name() != QLatin1String("style"))
    {
        return stylemap;
    }
    reader->readNext();

    QSharedPointer<HBaseStyle> styleobj;
    do
    {
        token = reader->tokenType();
        if ( token == QXmlStreamReader::StartElement)
        {
            if (reader->name() == QLatin1String("obj"))
            {
                /* Read attribute */
                QXmlStreamAttributes attris = reader->attributes();
                if(!attris.hasAttribute("clsname"))
                {
                    reader->skipCurrentElement(); // skipping any child nodes
                    reader->readNext();
                    continue;
                }
                if (!attris.hasAttribute("styleid"))
                {
                    reader->skipCurrentElement(); //skipping any child nodes
                    reader->readNext();
                    continue;
                }
                // 生成
                HString styleid(attris.value("styleid").toString());
                HString clsname(attris.value("clsname").toString());
                styleobj = HSTYLE->create(styleid.data(),clsname.data());
                if (styleobj)
                {
                    stylemap.insert(styleid,styleobj);
                    //to do read property nodes
                }
            }
            else if(reader->name() == QLatin1String("property"))
            {
                if (!styleobj)
                {
                    reader->skipCurrentElement();
                    reader->readNext();
                    continue;
                }

                QXmlStreamAttributes attris = reader->attributes();
                if(!attris.hasAttribute("id"))
                {
                    reader->skipCurrentElement(); // skipping any child nodes
                    reader->readNext();
                    continue;
                }
                readProperty(reader, attris.value("id").toString(), styleobj.data());
            }
        }
        else if (token == QXmlStreamReader::EndElement)
        {
            if (reader->name() == QLatin1String("style"))
            {
                break;
            }
            else if(reader->name() == QLatin1String("obj"))
            {
                styleobj = QSharedPointer<HBaseStyle>(NULL);
                //next obj node
            }
            else
            {//end property
            }
        }
        reader->readNext();

    }while(!reader->hasError() && !reader->atEnd());

    *hr = reader->error();

    return stylemap;
}

void HUIReader::readProperty(QXmlStreamReader* reader, const QString& id, QObject* item)
{
    Q_UNUSED(id);
    reader->readNext();

    while(!reader->atEnd() && !reader->hasError())
    {
        QXmlStreamReader::TokenType token = reader->tokenType();
        if (token == QXmlStreamReader::EndElement)
        {
            if (reader->name() == QLatin1String("property")) break;
        }
        else if(token == QXmlStreamReader::StartElement)
        {
            if (reader->name() == QLatin1String("classinfo"))
            {// read attribute
                readClassInfo(reader,id,item);
            }
        }
        else if (token == QXmlStreamReader::Characters)
        {// id , text = isWhitespace() or isCDATA()
            if (!reader->isWhitespace())
                setProperty(item,id,reader->text().toString());
        }
        else
        {// other token skipping,not need
        }
        reader->readNext();
    }
}

void HUIReader::readClassInfo(QXmlStreamReader* reader, const QString& id, QObject* item)
{
    while(!reader->atEnd() && !reader->hasError())
    {
        QXmlStreamReader::TokenType token = reader->tokenType();
        if (token == QXmlStreamReader::EndElement)
        {
            if (reader->name() == QLatin1String("classinfo")) break;
        }
        else if(token == QXmlStreamReader::StartElement)
        {
            QXmlStreamAttributes attris = reader->attributes();
            HClassInfo cls(attris.value("clsname").toString(),attris.value("styleid").toString(),attris.value("name").toString());
            item->setProperty(id.toLatin1(),classInfo2QVariant(cls));
        }
        reader->readNext();
    }
}

void HUIReader::setProperty(QObject* item, const QString& id, const QString& attr)
{
    QByteArray cid = id.toLatin1();
    const char* testid = cid.data();
    Q_UNUSED(testid);

    int idx = item->metaObject()->indexOfProperty(cid.constData());
    if(-1 != idx)
    {
        QMetaProperty prop = item->metaObject()->property(idx);
        int type_id = prop.type();
        if(type_id == QVariant::UserType)
        {
            type_id = prop.userType();
        }
        long hr = -1;
        QVariant var = HFACTORY->convertString(type_id, attr, &hr);
        if (0==hr)
        {
            item->setProperty(cid,var);
        }
        else
        {
            item->setProperty(cid,HFACTORY->convertString(0, attr, &hr));
        }
    }
    else
    {
        item->setProperty(cid,attr);
    }
}

