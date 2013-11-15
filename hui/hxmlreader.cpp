#include "hxmlreader.h"
#include <QXmlStreamReader>

class HXmlReaderPrivate
{
public:
    HXmlReaderPrivate()
        :mXmlReader(NULL)
    {
    }

    ~HXmlReaderPrivate()
    {
        clear();
    }

    void clear()
    {
        hDelete(mXmlReader);
    }

    void read(const QString& data)
    {
        hDelete(mXmlReader);
        mXmlReader = new QXmlStreamReader(data);
    }

    void read(const char* data)
    {
        hDelete(mXmlReader);
        mXmlReader = new QXmlStreamReader(data);
    }

    void read(const QByteArray& bytes)
    {
        hDelete(mXmlReader);
        mXmlReader = new QXmlStreamReader(bytes);
    }

    bool has() const
    {
        return (mXmlReader != NULL);
    }
    QString mXmlRef;
    QXmlStreamReader *mXmlReader;
};

HXmlReader::HXmlReader()
    :d_ptr(new HXmlReaderPrivate)
{
}

HXmlReader::~HXmlReader()
{
    delete d_ptr;
}

void HXmlReader::readWithString(const QString& data)
{
    Q_UNUSED(data);
    d_func()->read(data);
}

void HXmlReader::readWithData(const char* data)
{
    Q_UNUSED(data);
    d_func()->read(data);
}

void HXmlReader::readWithBytes(const QByteArray& bytes)
{
    Q_UNUSED(bytes);
    d_func()->read(bytes);
}

bool HXmlReader::atEnd() const
{
    Q_D(const HXmlReader);
    return d->has()?d->mXmlReader->atEnd():true;
}

HXmlReader::TokenType HXmlReader::readNext()
{
    Q_D(HXmlReader);
    return d->has()?(TokenType)d->mXmlReader->readNext():Invalid;
}

bool HXmlReader::readNextStartElement()
{
    Q_D(HXmlReader);
    return d->has()?d->mXmlReader->readNextStartElement():false;
}

void HXmlReader::skipCurrentElement()
{
    Q_D(HXmlReader);
    if (d->has())
        d->mXmlReader->skipCurrentElement();
}

HXmlReader::TokenType HXmlReader::tokenType() const
{
    Q_D(const HXmlReader);
    return (d->has())? (TokenType)d->mXmlReader->tokenType():Invalid;
}

QString HXmlReader::tokenString() const
{
    Q_D(const HXmlReader);
    return (d->has())? d->mXmlReader->tokenString():"Invalid";
}

void HXmlReader::setNamespaceProcessing(bool process)
{
    Q_D(HXmlReader);
    if (d->has())
        d->mXmlReader->setNamespaceProcessing(process);
}

bool HXmlReader::namespaceProcessing() const
{
    Q_D(const HXmlReader);
    return (d->has())? d->mXmlReader->namespaceProcessing() : false;
}

bool HXmlReader::isWhitespace() const
{
    Q_D(const HXmlReader);
    return (d->has())? d->mXmlReader->isWhitespace() : false;
}

bool HXmlReader::isCDATA() const
{
    Q_D(const HXmlReader);
    return (d->has())? d->mXmlReader->isCDATA() : false;
}

bool HXmlReader::isStandaloneDocument() const
{
    Q_D(const HXmlReader);
    return (d->has())? d->mXmlReader->isStandaloneDocument() : false;
}

QStringRef HXmlReader::documentVersion() const
{
    Q_D(const HXmlReader);
    return (d->has())? d->mXmlReader->documentVersion() : QStringRef(&d->mXmlRef);
}

QStringRef HXmlReader::documentEncoding() const
{
    Q_D(const HXmlReader);
    return (d->has())? d->mXmlReader->documentVersion() : QStringRef(&d->mXmlRef);
}

HXmlAttributes HXmlReader::attributes() const
{
    return HXmlAttributes();
}

QString HXmlReader::readElementText(HXmlReader::ReadElementTextBehaviour behaviour)
{
    Q_D(HXmlReader);
    return (d->has()) ? d->mXmlReader->readElementText((QXmlStreamReader::ReadElementTextBehaviour)behaviour) : "";
}

QStringRef HXmlReader::name() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->name() : QStringRef(&d->mXmlRef);
}

QStringRef HXmlReader::namespaceUri() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->namespaceUri() : QStringRef(&d->mXmlRef);
}

QStringRef HXmlReader::qualifiedName() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->qualifiedName() : QStringRef(&d->mXmlRef);
}

QStringRef HXmlReader::prefix() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->prefix() : QStringRef(&d->mXmlRef);
}

QStringRef HXmlReader::processingInstructionTarget() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->processingInstructionTarget() : QStringRef(&d->mXmlRef);
}

QStringRef HXmlReader::processingInstructionData() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->processingInstructionData() : QStringRef(&d->mXmlRef);
}

QStringRef HXmlReader::text() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->text() : QStringRef(&d->mXmlRef);
}

void HXmlReader::raiseError(const QString& message)
{
    Q_D(HXmlReader);
    if (d->has())
        d->mXmlReader->raiseError(message);
}

QString HXmlReader::errorString() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? d->mXmlReader->errorString() : "";
}

HXmlReader::Error HXmlReader::error() const
{
    Q_D(const HXmlReader);
    return (d->has()) ? (Error)d->mXmlReader->error() : NoError;
}




