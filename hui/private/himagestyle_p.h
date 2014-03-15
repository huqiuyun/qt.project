#ifndef HBACKGROUNDSTYLE_P_H
#define HBACKGROUNDSTYLE_P_H

#include "hbase.h"

class H_API HBackgroundStylePrivate
{
public:
    HBackgroundStylePrivate()
    {
    }
    void calcuTile();

    Qt::Alignment mAlignment;
    QMargins      mMargins;
    QColor        mColor;
    QColor        mColorized;
    QString       mImagePath;
    QBrush        mBackgroundBrush;
    QPixmap       mImage;
    HImageTile    mImageTile;
};

#endif // HBACKGROUNDSTYLE_P_H
