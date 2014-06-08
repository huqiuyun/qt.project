#ifndef HDRAW_H
#define HDRAW_H

#include "hbase.h"

class QPainter;
class H_API HDraw
{
public:
    HDraw();

    static bool  cacluImageTile(const QPixmap& pixmap,HImageTile& tile);
    static bool  cacluImageTile(const QImage& img,HImageTile& tile);

    /** @state widget's state @see HWidgetState*/
    void  paint(QPainter* painter,const QRect& rect,const QColor& color, const QMargins& m);
    void  paint(QPainter* painter,const QRect& rect,const QBrush& br, const QMargins& m);

    /** @state widget's state @see HWidgetState*/
    void  paint(QPainter* painter,const QRect& rect,const QPixmap& image, const QMargins& m , const HImageTile& tile,int idx);

private:
    void paint(QPainter* painter,const QRect& rect,const QPixmap& pixmap, const HTile& tile);
};

#endif // HDRAW_H
