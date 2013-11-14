#include "hcssstyle.h"
#include "hcore.h"
#include "hfactory.h"
#include "hxmlreader.h"

//HcssObject
IMPLEMENT_OBJECT_STATIC_CREATE(HCssObject)
HCssObject::HCssObject(const HObjectInfo& objinfo,QObject *parent) :
    QObject(parent),
    mObjinfo(objinfo)
{
}

void HCssObject::setStyleId(const QLatin1String& styleid)
{
    mObjinfo.mStyleId = styleid;
}

QLatin1String HCssObject::styleId() const
{
    return mObjinfo.mStyleId;
}

QVariant HCssObject::data(const QString& id) const
{
    DataMap::const_iterator iter = mDatas.constFind(id);
    if (iter != mDatas.constEnd())
    {
        return iter.value();
    }
    return QVariant();
}

void HCssObject::setData(const QString& id, const QVariant& var)
{
    mDatas.insert(id,var);
}

void HCssObject::copyTo(HCssObject* obj)
{
    Q_UNUSED(obj);
}

//HCssFrame
IMPLEMENT_OBJECT_STATIC_CREATE(HCssFrame)
HCssFrame::HCssFrame(const HObjectInfo& objinfo,QObject* parent) :
    HCssObject(objinfo,parent)
{
    mFrameStyle.mClsName = QLatin1String("HFrameStyle");
    mFrameStyle.mStyleId = QLatin1String("framestyleId");

    mClientWidget.mClsName = QLatin1String("HGWidget");
    mClientWidget.mObjName = QLatin1String("rootWidget");
    mClientWidget.mStyleId = QLatin1String("clientId");

    mAlignment = Qt::AlignCenter;
    mWinFlags = Qt::Window;
    mStyleSheet = QLatin1String("QGraphicsView { border-style: none; background: transparent}");
}

void HCssFrame::setFrameStyle(const HClassInfo& cls)
{
    mFrameStyle = cls;
}

HClassInfo HCssFrame::frameStyle() const
{
    return mFrameStyle;
}

void HCssFrame::setClientWidget(const HClassInfo& cls)
{
    mClientWidget = cls;
}

HClassInfo HCssFrame::clientWidget() const
{
    return mClientWidget;
}

void HCssFrame::setStyleSheet(const QString& sheet)
{
    mStyleSheet = sheet;
}

bool HCssFrame::hasStyleSheet() const
{
    return (mStyleSheet.size()>1);
}


QString HCssFrame::styleSheet() const
{//"QGraphicsView { border-style: none; background: transparent}"
    return mStyleSheet;
}

void HCssFrame::setWindowFlags(Qt::WindowFlags flags)
{
    mWinFlags = flags;
}

Qt::WindowFlags HCssFrame::windowFlags() const
{
    return mWinFlags;
}

// next layout functions
qy::HLayoutType HCssFrame::layoutType() const
{
    return mLayoutType;
}

void HCssFrame::setLayout(qy::HLayoutType type)
{
    mLayoutType = type;
}

/** set per child item space in owner layout */
void HCssFrame::setSpacing(int s)
{
    mSpacing = s;
}

int HCssFrame::spacing() const
{
    return mSpacing;
}

/** set margins for all child item in layout */
void HCssFrame::setMargins(const QMargins& m)
{
    mMargins = m;
}

QMargins HCssFrame::margins() const
{
   return mMargins;
}

/** set alignment in parent layout*/
Qt::Alignment HCssFrame::alignment() const
{
    return mAlignment;
}

void HCssFrame::setAlignment(Qt::Alignment align)
{
    mAlignment = align;
}

void HCssFrame::copyTo(HCssObject* obj)
{
    HCssFrame* newcss = static_cast<HCssFrame*>(obj);
    Q_UNUSED(newcss);
}

//HCssBackground
IMPLEMENT_OBJECT_STATIC_CREATE(HCssBackground)
HCssBackground::HCssBackground(const HObjectInfo& objinfo,QObject* parent) :
    HCssObject(objinfo,parent)
{
    mColorizeFlag = qy::kFollowParent;
    mAlignment = Qt::AlignCenter;
}

void HCssBackground::setColorizePolicy(qy::HColorizeFlag flag)
{
    mColorizeFlag = flag;
}

qy::HColorizeFlag HCssBackground::colorizePolicy() const
{
    return mColorizeFlag;
}

/** set margins for all child item in layout */
void HCssBackground::setMargins(const QMargins& m)
{
    mMargins = m;
}

QMargins HCssBackground::margins() const
{
   return mMargins;
}

/** set alignment in parent layout*/
Qt::Alignment HCssBackground::alignment() const
{
    return mAlignment;
}

void HCssBackground::setAlignment(Qt::Alignment align)
{
    mAlignment = align;
}

void HCssBackground::setImagePath(const QString& path)
{
    mImagePath = path;
}

QString HCssBackground::imagePath() const
{
    return mImagePath;
}

int HCssBackground::imagePathLength() const
{
    return mImagePath.length();
}

void HCssBackground::setColor(const QColor& rgb)
{
    mColor = rgb;
}

QColor HCssBackground::color() const
{
    return mColor;
}

void HCssBackground::setColorized(const QColor& rgb)
{
    mColorized = rgb;
}

QColor HCssBackground::colorized() const
{
    return mColorized;
}

void HCssBackground::setComposeMode(QPainter::CompositionMode composeMode)
{
    mComposeMode = composeMode;
}

QPainter::CompositionMode HCssBackground::composeMode() const
{
    return mComposeMode;
}

void HCssBackground::copyTo(HCssObject* obj)
{
    HCssBackground* newcss = static_cast<HCssBackground*>(obj);
    Q_UNUSED(newcss);
}
//HCssWidget
IMPLEMENT_OBJECT_STATIC_CREATE(HCssWidget)
HCssWidget::HCssWidget(const HObjectInfo& objinfo,QObject* parent) :
    HCssObject(objinfo,parent)
{
    mLayoutType = qy::kNone;
    mDragFlag = qy::kDragWindow;
    mSpacing = 0;
    mAlignment = Qt::AlignCenter;
    mBackgroundItem.mClsName = QLatin1String("HBackgroundItem");
}

/** set margins for all child item in layout */
void HCssWidget::setMargins(const QMargins& m)
{
    mMargins = m;
}

QMargins HCssWidget::margins() const
{
   return mMargins;
}

/** set alignment in parent layout*/
Qt::Alignment HCssWidget::alignment() const
{
    return mAlignment;
}

void HCssWidget::setAlignment(Qt::Alignment align)
{
    mAlignment = align;
}

void HCssWidget::setDragPolicy(qy::HDragFlag flag )
{
    mDragFlag = flag;
}

qy::HDragFlag HCssWidget::dragPolicy() const
{
    return mDragFlag;
}

// next layout functions
qy::HLayoutType HCssWidget::layoutType() const
{
    return mLayoutType;
}

void HCssWidget::setLayout(qy::HLayoutType type)
{
    mLayoutType = type;
}

HAnchor HCssWidget::anchor() const
{
    return mAnchor;
}

void HCssWidget::setAnchor(const HAnchor& a)
{
    mAnchor = a;
}

/** set per child item space in owner layout */
void HCssWidget::setSpacing(int s)
{
    mSpacing = s;
}

int HCssWidget::spacing() const
{
    return mSpacing;
}

void HCssWidget::setBackgroundItem(const HClassInfo& cls)
{
    mBackgroundItem = cls;
}

HClassInfo HCssWidget::backgroundItem() const
{
    return mBackgroundItem;
}

bool HCssWidget::hasStyleSheet() const
{
    return (mStyleSheet.size() > 1);
}

void HCssWidget::setStyleSheet(const QString& sheet)
{
    mStyleSheet = sheet;
}

QString HCssWidget::styleSheet() const
{
    return mStyleSheet;
}

void HCssWidget::copyTo(HCssObject* obj)
{
    HCssWidget* newcss = static_cast<HCssWidget*>(obj);
    Q_UNUSED(newcss);
}
//
typedef QMap<QLatin1String, QSharedPointer<HCssObject> > HCssMap;
class HCssStylePrivate
{
public:
    HCssMap mCss;
};

//HCssStyle
HCssStyle::HCssStyle(QObject *parent) :
    QObject(parent),
    d_ptr(new HCssStylePrivate)
{
}

HCssStyle::~HCssStyle()
{
    delete d_ptr;
}

QSharedPointer<HCssObject> HCssStyle::create(const QLatin1String& styleid,const char* clsname,bool global)
{
    Q_D(HCssStyle);
    HClassInfo cls(clsname,styleid.data(), clsname);

    HCssMap::iterator iter = d->mCss.find(styleid);
    if (iter != d->mCss.end())
    {
        if (!global)
        {//todo clone
            long hr = 0;
            HCssObject* obj = static_cast<HCssObject*>(HFACTORY->createObject(cls,this,HCreateParameter(),&hr));
            if (obj)
            {
                iter.value()->copyTo(obj);
            }
            return QSharedPointer<HCssObject>(obj);
        }
        return iter.value();
    }

    long hr = 0;
    QObject *obj = HFACTORY->createObject(cls,this,HCreateParameter(),&hr);
    if (!obj) return QSharedPointer<HCssObject>(NULL);

    QSharedPointer<HCssObject> css(static_cast<HCssObject*>(obj));
    if (!css.data() && global)
    {
        QObject::connect(obj,
                         SIGNAL(styleChanged(const QLatin1String&,int)),
                         this,
                         SIGNAL(styleChanged(const QLatin1String&,int)));
        d->mCss.insert(styleid,css);
    }
    return css;
}

QSharedPointer<HCssObject> HCssStyle::createWithFile(const QString& file,
                                                     const QLatin1String& styleid,
                                                     const char* clsname, bool global)
{
    Q_UNUSED(styleid);
    Q_UNUSED(clsname);
    Q_UNUSED(file);
    Q_UNUSED(global);
    // read from xml file, and create css object

    return QSharedPointer<HCssObject>(NULL);
}

QSharedPointer<HCssObject> HCssStyle::createWithData(const QString& data,
                                                     const QLatin1String& styleid,
                                                     const char* clsname, bool global)
{
    Q_UNUSED(styleid);
    Q_UNUSED(clsname);
    Q_UNUSED(data);
    Q_UNUSED(global);
    // read from xml data, and create css object

    return QSharedPointer<HCssObject>(NULL);
}

QSharedPointer<HCssObject> HCssStyle::createWithXmlReader(const HXmlReader* reader,
                                                          const QLatin1String& styleid,
                                                          const char* clsname, bool global)
{
    Q_UNUSED(styleid);
    Q_UNUSED(clsname);
    Q_UNUSED(reader);
    Q_UNUSED(global);
    // read from xml reader, and create css object

    return QSharedPointer<HCssObject>(NULL);
}


QSharedPointer<HCssObject> HCssStyle::itemAt(const QLatin1String& styleid)
{
    Q_D(HCssStyle);
    HCssMap::iterator iter = d->mCss.find(styleid);
    if (iter != d->mCss.end())
    {
        return iter.value();
    }
    return QSharedPointer<HCssObject>(NULL);
}

bool HCssStyle::addItem(const QLatin1String& styleid, QSharedPointer<HCssObject> item)
{
    Q_D(HCssStyle);
    if (itemAt(styleid)) return false;
    d->mCss.insert(styleid,item);
    return true;
}

void HCssStyle::removeItem(const QLatin1String& styleid)
{
    Q_D(HCssStyle);
    HCssMap::iterator iter = d->mCss.find(styleid);
    if (iter != d->mCss.end())
    {
        d->mCss.erase(iter);
    }
}

const QLatin1String& HCssStyle::idCheck(const QLatin1String& id, const QLatin1String& def)
{
    return (id.size() > 1 && id != QLatin1String("undefined"))? id : def;
}

bool HCssStyle::idSetCompare(QLatin1String& id, const QLatin1String& newId)
{
    if (id != newId)
    {
        id = newId;
        return true;
    }
    return false;
}
