#ifndef HUITASK_H
#define HUITASK_H

#include "hbase.h"
#include "hlayoutconfig.h"
class HuiReader;
class QGraphicsItem;
class QWidget;
class QGraphicsWidget;
class QObject;
class HStyle;
class HPropertyProxy;
class HuiTask
{
public:
    struct Flags
    {
        // can flag
        int isQObject:1; // based QObject
        int isQWidget:1; // based QWidget
        int isGWidget:1; // based QGraphicsWidget
        int isQGItem:1; // based QGraphicsItem
        int isQLayout:1; // support QLayout for QWidget
        int isGLayout:1; // support QGraphicLayout for QGraphicsWidget
        int isScene:1; // support QGraphicsScene for HGView
        int isStyle:1; // support style for based HQWidget , HGWidget , HGView
        int isNewStyle:1; // internal flag

        int isXmlLayout:1;
        int isXmlScene:1;
        int isXmlWidget:1;
        //
        int isHQWidget:1;// object is based HQWidget
        int isHGView:1; // object is based HGView
        int isHGWidget:1; // object is based HGWidget

        Flags(){ memset(this,0,sizeof(*this)); }
    };

    class SaveFlags
    {
    public:
        SaveFlags(HuiTask* task,Flags newFlags):
            mTask(task)
        {
            mFlags = task->flags();
            task->flags() = newFlags;
        }
        ~SaveFlags()
        {
            mTask->flags() = mFlags;
        }
    private:
        HuiTask* mTask;
        Flags mFlags;
    };

    HuiTask();
    ~HuiTask();

private:
    Flags& flags() { return mFlags; }

    inline bool canCreateScene() const {
        return isHGView();
    }

    inline bool canCreateLayout() const {
        return (mFlags.isQLayout || mFlags.isGLayout);
    }

    inline bool canCreateWidget() const {
        return canGWidget() || canQWidget();
    }

    inline bool canCreateStyle() const {
        return (mFlags.isStyle);
    }

    inline bool canGWidget() const {
        return ( (mFlags.isGWidget||mFlags.isGLayout)||(mFlags.isScene&&mFlags.isXmlScene));
    }

    inline bool canGItem() const {
        return (mFlags.isScene&&mFlags.isXmlScene);
    }

    inline bool canQWidget() const {// when flag is xmlscene,then not create qwidget,only create QGrahicsItem object
        return ( (mFlags.isQWidget||mFlags.isQLayout||mFlags.isGLayout) && (0==mFlags.isXmlScene));
    }

    inline bool canQObject() const {
        return mFlags.isQObject;
    }

    // object type
    inline bool isQObject() const {
        return mFlags.isQObject;
    }

    inline bool isQWidget() const {
        return (USEOBJTYPE(QWidget) <= mObjType && mObjType < USEOBJTYPE(HQUseDefine));
    }

    inline bool isHQWidget() const {
        return (isQWidget() && mFlags.isHQWidget);
    }

    inline bool isHGView() const {
        return (isQWidget() && mFlags.isHGView);
    }

    inline bool isGraphicsItem() const {
        return (USEOBJTYPE(QGraphicsItem) < mObjType &&
                mObjType < USEOBJTYPE(QGLayoutItem));
    }

    inline bool isGWidget() const {
        return (USEOBJTYPE(QGLayoutItem) < mObjType &&
                mObjType < USEOBJTYPE(HGUseDefine));
    }

    inline bool isHGWidget() const {
        return (isGWidget() && mFlags.isHGWidget);
    }

    QGraphicsItem *gItem();
    QWidget *qWidget();
    QGraphicsWidget *gWidget();
    QObject *qObject();
    HStyle *style() const;
    //
    void createStyle();
    void createChild();
    void deleteChild();

    void installStyle();
    void deleteStyle();
    void addScene();
    void addLayout(HPropertyProxy* proxy);
    void addWidget(HPropertyProxy* proxy);

    int  findFunc(const char* clsname);
    void setFlagsWithQWidget(QWidget* parent);
    void setFlagsWithHGWidget(QGraphicsWidget* parent);
    void setFlagsWithHGItem(QGraphicsItem* parent);

    //
    static bool hasProperty(QObject* object, const char* key);
    static void setProperty(HuiTask* task,HPropertyProxy* proxy);
    static void setProperty(QObject* obj, const QList<HIdValue>& propertys);
    static bool setProperty(QObject* obj, const QString& id, const QString& attr);
    static bool invoke(QObject* obj, const char* method, const QVector<QVariant>& args);

    template<class OBJ>
    inline OBJ* objCast() {
        return static_cast<OBJ*>(mObj);
    }

    template<class OBJ>
    inline OBJ* objCast() const {
        return static_cast<OBJ*>(mObj);
    }
private:
    friend class HuiReader;

    Flags mFlags;
    void *mObj;
    int   mObjType; //@see HEnums::HObjectType
    HuiTask *mParent;
    HuiTask *mChild;
    HStyle  *mStyle;
    QString  mXmlPath;
    QList<QWidget*> mWidgets;
    QList<HIdValue> mPropertys;
    // for layout
    HLayoutConfig   mLayoutConfig;
};

#endif // HUITASK_H
