#ifndef HQLAYOUT_H
#define HQLAYOUT_H

#include "hlayout.h"
#include "hlayoutconfig.h"
#include <QPointer>

class QWidget;
class QLayout;

class H_API HQLayout : public HLayout
{
public:
    explicit HQLayout(QObject *parent = 0);

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
    virtual int  insertWidget(QWidget* widget ,const HLayoutConfig& conf);
    virtual bool removeWidget(QWidget* widget);

    virtual bool addChildWidget(QWidget* widget ,const HLayoutConfig& conf);
    virtual void removeChildWidget(QWidget* widget);

    virtual void resizeEvent(const QSize& );
protected:
    HItemWidgets<QWidget> mChilds;
    QWidget* mWindow;
};

#endif // HQLAYOUT_H
