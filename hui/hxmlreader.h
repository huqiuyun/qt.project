#ifndef HXMLREADER_H
#define HXMLREADER_H

#include "hconfig.h"
#include "hxmlattributes.h"
#include <QString>

class HXmlReaderPrivate;
/**
 * a sample xml reader , only wrapper QXmlStreamReader
*/
class H_API HXmlReader
{
    Q_DECLARE_PRIVATE( HXmlReader )
public:
    enum TokenType
    {
        NoToken = 0,
        Invalid,
        StartDocument,
        EndDocument,
        StartElement,
        EndElement,
        Characters,
        Comment,
        DTD,
        EntityReference,
        ProcessingInstruction
    };

    enum ReadElementTextBehaviour
    {
        ErrorOnUnexpectedElement,
        IncludeChildElements,
        SkipChildElements
    };

    enum Error
    {
        NoError,
        UnexpectedElementError,
        CustomError,
        NotWellFormedError,
        PrematureEndOfDocumentError
    };

    explicit HXmlReader();
    ~HXmlReader();

public:
    void readWithString(const QString& data);
    void readWithData(const char* data);
    void readWithBytes(const QByteArray& bytes);

    bool atEnd() const;
    TokenType readNext();

    bool readNextStartElement();
    void skipCurrentElement();

    TokenType tokenType() const;
    QString tokenString() const;

    void setNamespaceProcessing(bool);
    bool namespaceProcessing() const;

    inline bool isStartDocument() const { return tokenType() == StartDocument; }
    inline bool isEndDocument() const { return tokenType() == EndDocument; }
    inline bool isStartElement() const { return tokenType() == StartElement; }
    inline bool isEndElement() const { return tokenType() == EndElement; }
    inline bool isCharacters() const { return tokenType() == Characters; }
    bool isWhitespace() const;
    bool isCDATA() const;
    inline bool isComment() const { return tokenType() == Comment; }
    inline bool isDTD() const { return tokenType() == DTD; }
    inline bool isEntityReference() const { return tokenType() == EntityReference; }
    inline bool isProcessingInstruction() const { return tokenType() == ProcessingInstruction; }

    bool isStandaloneDocument() const;
    QStringRef documentVersion() const;
    QStringRef documentEncoding() const;

    HXmlAttributes attributes() const;

    QString readElementText(ReadElementTextBehaviour behaviour = ErrorOnUnexpectedElement);

    QStringRef name() const;
    QStringRef namespaceUri() const;
    QStringRef qualifiedName() const;
    QStringRef prefix() const;

    QStringRef processingInstructionTarget() const;
    QStringRef processingInstructionData() const;

    QStringRef text() const;

    void raiseError(const QString& message = QString());
    QString errorString() const;
    Error error() const;

    inline bool hasError() const { return error() != NoError; }
private:
    HXmlReaderPrivate* d_ptr;
};

#endif // HXMLREADER_H
