#ifndef HGLOBAL_H
#define HGLOBAL_H

#include "hconfig.h"

class QGraphicsWidget;
class QWidget;

class H_API HGlobal
{
public:
    static void setGWidgetAttribute(QGraphicsWidget* window, const QString& attribute);
    static void setQWidgetAttribute(QWidget* window, const QString& attribute);
    static int  mulDiv(int number,int numerator,int denominator);
};

#endif // HGLOBAL_H
