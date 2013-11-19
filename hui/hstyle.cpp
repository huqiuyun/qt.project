#include "HStyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "huireader.h"
#include "hresourcemgr.h"
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

//
class HStylePrivate
{
public:
    HStyleMap mStyle;
};

//HStyle
HStyle::HStyle(QObject *parent) :
    QObject(parent),
    d_ptr(new HStylePrivate)
{
}

HStyle::~HStyle()
{
    delete d_ptr;
}

QSharedPointer<HBaseStyle> HStyle::create(const char* styleid,const char* clsname)
{
    Q_D(HStyle);
    HClassInfo cls(clsname, styleid, "");

    std::string::size_type pos = cls.mStyleId.mId.find("undefined");
    if (pos==0)
    {
        return QSharedPointer<HBaseStyle>(NULL);
    }
    const char* prex = "private.";
    std::string findid;
    pos = cls.mStyleId.mId.find(prex);
    bool pri = (pos==0);
    if (pri)
    {
        findid = cls.mStyleId.mId.substr(sizeof(char)*sizeof(prex));
    }
    else
    {
        findid = cls.mStyleId.mId;
    }

    long hr = 0;
    HStyleMap::iterator iter = d->mStyle.find(findid);
    if (iter != d->mStyle.end())
    {
        if (pri)
        {//todo clone
            HBaseStyle* obj = static_cast<HBaseStyle*>(HFACTORY->createObject(cls,this,HCreateParameter(),&hr));

            iter.value()->copyTo(obj);
            return QSharedPointer<HBaseStyle>(obj);
        }
        return iter.value();
    }
    QSharedPointer<HBaseStyle> css(static_cast<HBaseStyle*>(HFACTORY->createObject(cls,this,HCreateParameter(),&hr)));
    if (css.data() && !pri)
    {
        d->mStyle.insert(styleid,css);
    }
    return css;
}

HStyleMap HStyle::createWithFile(const QString& filename)
{
    QXmlStreamReader reader(HRESMGR->loadData(filename));
    return _createWitXmlReader(&reader);
}

HStyleMap HStyle::createWithData(const QString& data)
{
    QXmlStreamReader reader(data);
    return _createWitXmlReader(&reader);
}

HStyleMap HStyle::_createWitXmlReader(QXmlStreamReader* reader)
{
    HUIReader uiReader;
    bool ok = false;
    while(!reader->atEnd() && !reader->hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = reader->readNext();

        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        if(token != QXmlStreamReader::StartElement)
        {
            continue;
        }

        if (reader->name() == QLatin1String("hui"))
        { //
            QXmlStreamAttributes attri = reader->attributes();
            if (!attri.hasAttribute("version"))
                break;

            ok = true;
        }
        else if(ok)
        {
            if (reader->name() == QLatin1String("style"))
            {//create css objects
                long hr = -1;
                return uiReader.createStyleWithXmlReader(reader,&hr);
            }
            else
            {
                reader->skipCurrentElement();
            }
        }
    }
    return HStyleMap();
}

QSharedPointer<HBaseStyle> HStyle::itemAt(const char* styleid)
{
    Q_D(HStyle);
    HStyleMap::iterator iter = d->mStyle.find(styleid);
    if (iter != d->mStyle.end())
    {
        return iter.value();
    }
    return QSharedPointer<HBaseStyle>(NULL);
}

bool HStyle::addItem(const char* styleid, QSharedPointer<HBaseStyle> item)
{
    Q_D(HStyle);
    if (itemAt(styleid)) return false;
    d->mStyle.insert(styleid,item);
    return true;
}

void HStyle::removeItem(const char* styleid)
{
    Q_D(HStyle);
    HStyleMap::iterator iter = d->mStyle.find(styleid);
    if (iter != d->mStyle.end())
    {
        d->mStyle.erase(iter);
    }
}
