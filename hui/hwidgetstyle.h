#ifndef HWIDGETSTYLE_H
#define HWIDGETSTYLE_H

#include "hbasestyle.h"

class H_API HWidgetStyle : public HBaseStyle
{
    Q_OBJECT
    Q_PROPERTY(	QString windowAttribute READ windowAttribute WRITE setWindowAttribute)
public:
    explicit HWidgetStyle(QObject *parent = 0);
    explicit HWidgetStyle(const HObjectInfo& objinfo, QObject *parent = 0);

public:
    QString windowAttribute() const;
    void setWindowAttribute(const QString& a);

    HBaseStyle* clone();
    void copyTo(HBaseStyle* obj);
protected:
    virtual void onSetWindowAttribute(){}
protected:
    QString  mWinAttribute; // "int:0|int:1" @see QWidget::setAttribute
};

#endif // HWIDGETSTYLE_H
