#include "huireader.h"
#include <QWidget>
#include "hgwidget.h"
#include "hgview.h"
#include "hxmlreader.h"
#include <QGraphicsItem>

HUIReader::HUIReader(QObject *parent) :
    QObject(parent)
{
}

HGWidget* HUIReader::createGWidget(const QString& xml, const QString& xmlpath,QGraphicsItem* parent)
{
    Q_UNUSED(xml);
    Q_UNUSED(xmlpath);
    Q_UNUSED(parent);
    return NULL;
}

HGWidget* HUIReader::createGWidgetFromData(const char* data, QGraphicsItem *parent)
{
    Q_UNUSED(data);
    Q_UNUSED(parent);
    return NULL;
}

HGView* HUIReader::createGView(const QString& xml,const QString& xmlpath,QWidget* parent)
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
