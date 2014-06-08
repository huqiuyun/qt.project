#ifndef HIMAGESTYLE_P_H
#define HIMAGESTYLE_P_H

#include "hbase.h"
#include "himagestyle.h"
class H_API HImageStylePrivate
{
public:
    HImageStylePrivate():
        mIndex(0),
        mStyles(HImageStyle::ImageOnly)
    {
    }
    void calcuTile();

    Qt::Alignment mAlignment;
    QMargins      mMargins;
    QColor        mColor;
    QBrush        mBrush;
    QString       mImagePath;
    QPixmap       mImage;
    HImageTile    mImageTile;
    int           mIndex;
    HImageStyle::GImageStyles  mStyles;
};

#endif // HIMAGESTYLE_P_H
