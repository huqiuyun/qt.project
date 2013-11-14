#ifndef HCSSSTYLE_H
#define HCSSSTYLE_H

#include "hbase.h"
#include "hguid.h"
#include <QMargins>
#include <QObject>
#include <QVariant>
#include <QMap>
#include <QPainter>

class HCssStyle;
class HXmlReader;

class H_API HCssObject : public QObject , public HObject
{
    Q_OBJECT
public:
    explicit HCssObject(const HObjectInfo& objinfo,QObject* parent= 0);
    virtual ~HCssObject(){}

    DECLARE_OBJECT_STATIC_CREATE(HCssObject);
public:
    void setStyleId(const QLatin1String& styleid);
    QLatin1String styleId() const;

    QVariant data(const QString& id) const;
    void setData(const QString& id, const QVariant& var);

    virtual void copyTo(HCssObject* obj);

signals:
    void styleChanged(const QLatin1String& styleid,int cssKey);

protected:
    typedef QMap<QString,QVariant> DataMap;
    HObjectInfo       mObjinfo;
    DataMap           mDatas;
};

// css for HGView
class H_API HCssFrame : public HCssObject
{
public:
    explicit HCssFrame(const HObjectInfo& objinfo,QObject* parent= 0);

    DECLARE_OBJECT_STATIC_CREATE(HCssFrame);
public:
    void setFrameStyle(const HClassInfo& cls);
    HClassInfo frameStyle() const;

    void setClientWidget(const HClassInfo& cls);
    HClassInfo clientWidget() const;

    bool hasStyleSheet() const;
    void setStyleSheet(const QString& sheet);
    QString styleSheet() const;

    void setWindowFlags(Qt::WindowFlags flags);
    Qt::WindowFlags windowFlags() const;

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set alignment in parent layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    // next layout functions
    qy::HLayoutType layoutType() const;
    void setLayout(qy::HLayoutType type);

    /** set per child item space in owner layout */
    void setSpacing(int s);
    int spacing() const;

    virtual void copyTo(HCssObject* obj);
protected:
    qy::HLayoutType mLayoutType;
    QMargins mMargins;
    Qt::Alignment mAlignment;
    Qt::WindowFlags mWinFlags;
    int mSpacing;
    /** for HGraphicsView to do create HFrameStyle object */
    HClassInfo  mFrameStyle;
    HClassInfo  mClientWidget;
    QString mStyleSheet;
};

/** css for HBakcgroundItem object */
class H_API HCssBackground : public HCssObject
{
public:
    explicit HCssBackground(const HObjectInfo& objinfo,QObject* parent= 0);

    DECLARE_OBJECT_STATIC_CREATE(HCssBackground);
public:
    void setColorizePolicy(qy::HColorizeFlag flag);
    qy::HColorizeFlag colorizePolicy() const;

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set alignment in parent layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    void setComposeMode(QPainter::CompositionMode composeMode);
    QPainter::CompositionMode composeMode() const;

    void setImagePath(const QString& path);
    QString imagePath() const;
    int imagePathLength() const;

    /** orig color */
    void setColor(const QColor& rgb);
    QColor color() const;
    void setColorized(const QColor& rgb);
    QColor colorized() const;

    virtual void copyTo(HCssObject* obj);
protected:
    qy::HColorizeFlag mColorizeFlag;
    QMargins  mMargins;
    Qt::Alignment mAlignment;
    QPainter::CompositionMode mComposeMode;
    QColor   mColor;
    QColor   mColorized;
    QString  mImagePath;
};

/** css for HWidget object */
class H_API HCssWidget : public HCssObject
{
public:
    explicit HCssWidget(const HObjectInfo& objinfo,QObject* parent = 0);

    DECLARE_OBJECT_STATIC_CREATE(HCssWidget);
public:
    void setDragPolicy(qy::HDragFlag flag );
    qy::HDragFlag dragPolicy() const;

    // next layout functions

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set alignment in parent layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    qy::HLayoutType layoutType() const;
    void setLayout(qy::HLayoutType type);

    HAnchor anchor() const;
    void setAnchor(const HAnchor& a);

    /** set per child item space in owner layout */
    void setSpacing(int s);
    int spacing() const;

    void setBackgroundItem(const HClassInfo& cls);
    HClassInfo backgroundItem() const;

    bool hasStyleSheet() const;
    void setStyleSheet(const QString& sheet);
    QString styleSheet() const;

    virtual void copyTo(HCssObject* obj);
protected:
    qy::HDragFlag mDragFlag;
    qy::HLayoutType mLayoutType;
    QMargins mMargins;
    Qt::Alignment mAlignment;
    QString mStyleSheet;
    HAnchor mAnchor;
    int mSpacing;
    HClassInfo mBackgroundItem;
};

class HCssStylePrivate;
class H_API HCssStyle : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( HCssStyle )
    Q_DISABLE_COPY( HCssStyle )
public:
    explicit HCssStyle(QObject *parent = 0);
    ~HCssStyle();

    /**
      * @param global true,then save it to share
    */
    QSharedPointer<HCssObject> create(const QLatin1String& styleid, const char* clsname, bool global=true);
    /**
      * @param xml @see huireader.h
    */
    QSharedPointer<HCssObject> createWithFile(const QString& file,const QLatin1String& styleid, const char* clsname, bool global=true);
    QSharedPointer<HCssObject> createWithData(const QString& data,const QLatin1String& styleid, const char* clsname, bool global=true);
    QSharedPointer<HCssObject> createWithXmlReader(const HXmlReader* reader,const QLatin1String& styleid, const char* clsname, bool global=true);

    QSharedPointer<HCssObject> itemAt(const QLatin1String& styleid);
    bool addItem(const QLatin1String& styleid, QSharedPointer<HCssObject> item);
    void removeItem(const QLatin1String& styleid);

    static const QLatin1String& idCheck(const QLatin1String& id, const QLatin1String& def);
    static bool idSetCompare(QLatin1String& id, const QLatin1String& newId);

signals:
    void styleChanged(const QLatin1String& styleid,int cssKey);

public slots:

private:
    HCssStylePrivate* d_ptr;
};

#endif // HCSSSTYLE_H
