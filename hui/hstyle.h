#ifndef HStyle_H
#define HStyle_H

#include "hbasestyle.h"
#include "henums.h"
#include "hguid.h"
#include <QMargins>
#include <QObject>
#include <QVariant>
#include <QMap>
#include <QPainter>
#include <QBrush>
#include <QSizePolicy>

class HStyle;
class QXmlStreamReader;

class HStylePrivate;
class H_API HStyle : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HStyle )
    Q_DISABLE_COPY( HStyle )
public:
    explicit HStyle(QObject *parent = 0);
    ~HStyle();

    /**
      * @param global true,then save it to share
    */
    QSharedPointer<HBaseStyle> create(const char* styleid, const char* clsname);
    /**
      * @param xml @see huireader.h
    */
    HStyleMap createWithFile(const QString& filename);
    HStyleMap createWithData(const QString& data);
    HStyleMap createWitXmlReader(QXmlStreamReader* reader);

    QSharedPointer<HBaseStyle> itemAt(const char* styleid);
    bool addItem(const char* styleid, QSharedPointer<HBaseStyle> item);
    void removeItem(const char* styleid);

private:
    HStyleMap _createWitXmlReader(QXmlStreamReader* reader);

private:
    HStylePrivate* d_ptr;
};

#endif // HStyle_H
