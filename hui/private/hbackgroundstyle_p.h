#ifndef HBACKGROUNDSTYLE_P_H
#define HBACKGROUNDSTYLE_P_H

#include "hconfig.h"

class H_API HBackgroundStylePrivate
{
public:
    HBackgroundStylePrivate()
    {
    }
    Qt::Alignment mAlignment;
    QMargins      mMargins;
    QColor        mColor;
    QColor        mColorized;
    QString       mImagePath;
    QBrush        mBackgroundBrush;
};

#endif // HBACKGROUNDSTYLE_P_H
