#include "hglobal.h"
#include <QGraphicsWidget>
#include <QWidget>

namespace hui {

template<class T>
void setAttributeT(T* window, const QString& attribute)
{
    if (!window) return;
    QStringList list = attribute.split("|");
    for(int i=0; i< list.size();i++) {
        QString attr = list.at(i);
        QStringList item = attr.split(":");
        if (item.size()>=2)
        {
            int val = item.at(0).toInt();
            if (val>=0 && val < Qt::WA_AttributeCount)
                window->setAttribute((Qt::WidgetAttribute)val,(item.at(1)==QLatin1String("true")));
        }
    }
}
} //namespace hui

void HGlobal::setGWidgetAttribute(QGraphicsWidget* window, const QString& attribute)
{
    hui::setAttributeT<QGraphicsWidget>(window,attribute);
}

void HGlobal::setQWidgetAttribute(QWidget* window, const QString& attribute)
{
    hui::setAttributeT<QWidget>(window,attribute);
}

int  HGlobal::mulDiv(int number,int numerator,int denominator)
{
#ifdef WIN32
    return MulDiv(number,numerator,denominator);
#else
    qreal val = ((qreal)number*numerator)/(qreal)denominator;
    int ival = val;
    if (val>=0.0) {
        if (val - (qreal)ival >=0.5)
            return ival+1;
        else
            return ival;
    }
    else{
        if ( (qreal)ival-val >=0.5)
            return ival-1;
        else
            return ival;
    }
#endif
}


