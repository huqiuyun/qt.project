#ifndef HQLAYOUTSTYLE_H
#define HQLAYOUTSTYLE_H

#include "hlayoutstyle.h"
#include <QPointer>
#include <QList>

class QWidget;
class QLayout;

class H_API HQLayoutStyle : public HLayoutStyle
{
public:
    explicit HQLayoutStyle(QObject *parent = 0);
    explicit HQLayoutStyle(const HObjectInfo& objinfo, QObject *parent = 0);

     DECLARE_OBJECT_STATIC_CREATE(HQLayoutStyle);
public:
    void setWindow(QWidget* window);
    QLayout* layout() const;

    void setLayoutType(HEnums::HLayoutType type);

    /** set margins for all child item in layout */
    void setMargins(const QMargins& m);
    QMargins margins() const;

    /** set alignment all child item in layout*/
    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    /** set per child item space in owner layout */
    int spacing() const;
    void setSpacing(int s);

    void setAlignment(QWidget* w, Qt::Alignment align);
    /** add widget to owner layout */
    virtual int  addWidget(QWidget* widget);
    virtual int  insertWidget(QWidget* widget ,const HLayoutConf& conf);
    virtual bool removeWidget(QWidget* widget);

    virtual bool addChildWidget(QWidget* widget ,const HLayoutConf& conf);
    virtual void removeChildWidget(QWidget* widget);

    virtual void resizeEvent(const QSize& );
    virtual HBaseStyle* clone();
protected:
    HChildWidgetList<QWidget> mChilds;
    QWidget* mWindow;
};

#endif // HQLAYOUTSTYLE_H
