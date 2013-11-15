#include "huireader.h"
#include "hgwidget.h"
#include "hgview.h"
#include "hxmlreader.h"
#include "hcore.h"
#include "hresourcemgr.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QDir>

HUIReader::HUIReader()
{
}


bool HUIReader::loadXml(QByteArray& bytes, const QString& xml,const QString& xmlpath)
{
    QString xmlfile;
    if (xmlpath.size()>1 )
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

    HXmlReader reader;

    reader.readWithBytes(bytes);
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
    return NULL;
}

HGView* HUIReader::createGViewFromData(const char* data, QWidget *parent)
{
    Q_UNUSED(data);
    Q_UNUSED(parent);
    return NULL;
}


bool HUIReader::createChildWithGView(const QString& xml,HGView* parent,const QString& xmlpath)
{
    Q_UNUSED(xml);
    Q_UNUSED(xmlpath);
    if (!parent) return false;

    return false;
}

bool HUIReader::createChildWithGViewFromData(const char* data, HGView *parent)
{
    Q_UNUSED(data);
    if (!parent) return false;

    return false;
}
