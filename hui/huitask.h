#ifndef HUITASK_H
#define HUITASK_H

#include "hbase.h"

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
        int isObjHQWidget:1;// object is based HQWidget
        int isObjHGView:1; // object is based HGView
        int isObjHGWidget:1; // object is based HGWidget

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
        return mFlags.isScene;
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
    inline bool isQWidget() const {
        return (USEOBJTYPE(QWidget) <= mObjType && mObjType < USEOBJTYPE(QUseDefine));
    }

    inline bool isHQWidget() const {
        return (isQWidget() && mFlags.isObjHQWidget);
    }

    inline bool isHGView() const {
        return (isQWidget() && mFlags.isObjHGView);
    }

    inline bool isGraphicsItem() const {
        return (USEOBJTYPE(QGraphicsItem) < mObjType &&
                mObjType < USEOBJTYPE(QGLayoutItem));
    }

    inline bool isGWidget() const {
        return (USEOBJTYPE(QGLayoutItem) < mObjType &&
                mObjType < USEOBJTYPE(HGLayoutItemUseDefine));
    }

    inline bool isHGWidget() const {
        return (isGWidget() && mFlags.isObjHGWidget);
    }

    QGraphicsItem *gItem();
    QWidget *qWidget();
    QGraphicsWidget *gWidget();
    QObject *qObject();
    HStyle *style() const;
    //
    void generateStyle();
    void generateChild();
    void deleteChild();

    void installStyle();
    void deleteStyle();
    void addScene(bool& main);
    void addLayout(HPropertyProxy* proxy,bool isUse);
    void addWidget(HPropertyProxy* proxy,bool isUse);
    void addWidgetToList();

    int  findFunc(const char* clsname);
    bool hasProperty(QObject* object, const char* key);
    void setFlagsWithQWidget(QWidget* parent);
    void setFlagsWithHGWidget(QGraphicsWidget* parent);
    void setFlagsWithHGItem(QGraphicsItem* parent);

    static void execSkipProperty(HuiTask* task,HPropertyProxy* proxy,bool isUse);
    static bool setProperty(QObject* obj, const QString& id, const QString& attr,bool isUse);

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
    HLayoutConf    mLayoutConf;
    QList<HIdValue> mLayoutPropertys;
};

#endif // HUITASK_H
