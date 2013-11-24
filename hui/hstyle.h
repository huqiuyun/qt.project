#ifndef HSTYLE_H
#define HSTYLE_H

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

class H_API HStyle : public QObject, public HObject
{
    Q_OBJECT
public:
    explicit HStyle(QObject *parent = 0);
    ~HStyle();

    static bool isPrivate(const char* styleid);
    static std::string prex(const std::string& cls, bool& pri);
    /**
      * @param global true,then save it to share
    */
    QSharedPointer<HBaseStyle> create(const char* styleid, const char* clsname);
    /** if styleid prex is "private."*/
    QSharedPointer<HBaseStyle> itemAt(const char* styleid) const;
    bool addItem(const char* styleid, QSharedPointer<HBaseStyle> item);
    void removeItem(const char* styleid);
    void add(const HStyleMap& styles);
    int  size() const;

private:
    HStyleMap mStyle;
};

Q_DECLARE_METATYPE(const HStyle*);

#endif // HSTYLE_H
