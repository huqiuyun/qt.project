#include "hdraw.h"
#include "hcore.h"
#include "hresourcemgr.h"
#include <QPainter>
#include <QImage>

HDraw::HDraw()
{
}

bool HDraw::cacluImageTile(const QPixmap& pixmap,HImageTile& tile)
{
    return cacluImageTile(pixmap.toImage(),tile);
}

bool HDraw::cacluImageTile(const QImage& img,HImageTile& tile)
{
    static QRgb lineRgb = qRgb(162,0,162);
    static QRgb tileRgb = qRgb(255,0,255);
    if (img.isNull())
        return false;

    qint64 key = img.cacheKey();
    if (HCORE && HRESMGR->findImageTile(key,&tile)) {
        return true;
    }

    int _w = img.width();
    int _h = img.height();
    int _x[2] = {_w,_w};
    int _y[2] = {_h,_h};
    int row = 0 , col = 0;
    int horiLine =1, vertLine =1;
    for (int x=0; x<img.width();x++) {
        QRgb rgb=img.pixel(x,0);
        if (rgb==tileRgb) {
            if (col<2 && x>0) {
                _x[col] = x;col++;
            }
        }
        else if(rgb==lineRgb) {
            if (horiLine==1)
                _w = x;
            horiLine++;
        }
    }
    for (int y=0; y<img.height();y++) {
        QRgb rgb=img.pixel(0,y);
        if (rgb == tileRgb) {
            if (row<2 && y>0) {
                _y[row] = y;row++;
            }
        }
        else if(rgb==lineRgb){
            if (vertLine==1)
                _h = y;
            vertLine++;
        }
    }
    tile.mWidth = _w;
    tile.mHeight= _h;
    tile.mHoriLine = horiLine;
    tile.mVertLine = vertLine;
    tile.initX(_x[0],_x[1]);
    tile.initY(_y[0],_y[1]);
    qDebug("HDraw::cacluImageTile key:%lld",key);
    tile.debug();
    if (HCORE) HRESMGR->addImageTile(key,tile);
    return !(row==0&&col==0);
}

void HDraw::paint(QPainter* painter,const QRect& rect,const QColor& color, const QMargins& m)
{
    painter->fillRect(rect.marginsRemoved(m),color);
}

void HDraw::paint(QPainter* painter,const QRect& rect,const QPixmap& pixmap, const HTile& tile)
{
#define PT(m) (m.p1-m.p0)

    int x_target = rect.left();
    int y_target = rect.top();
    int w_target = rect.width();
    int h_target = rect.height();
    if (h_target<=0)
        return ;

    int h_tile  = tile.height();
    if (h_tile<=0)
        return ;

    int w_left  = PT(tile.mLeft);
    int w_mid   = PT(tile.mMid);
    int w_right = PT(tile.mRight);

    //left
    int w_targetV = 0;
    if (w_left>0) {
        int w = tile.onlyOne()?w_target:((w_target>=w_left)?w_left:w_target);
        if (w>0) {
            //qDebug("--HDraw::paint left tile:x=%d,y=%d,w=%d,h=%d",x_target,y_target,w,h_target);
            painter->drawPixmap(x_target, y_target, w, h_target, pixmap, tile.mLeft.p0, tile.mY.p0, w_left, h_tile);
            x_target += w;
            w_targetV = w;
        }
    }
    //mid
    if (w_mid>0) {
        int w = w_target-(w_left+w_right);
        if (w>0) {
            //qDebug("--HDraw::paint mid tile:x=%d,y=%d,w=%d,h=%d",x_target,y_target,w,h_target);
            painter->drawPixmap(x_target, y_target, w, h_target, pixmap, tile.mMid.p0, tile.mY.p0, w_mid, h_tile);
            x_target += w;
            w_targetV += w;
        }
    }
    //right
    if (w_right>0) {
        int w = w_target-w_targetV;
        if (w>0) {
            //qDebug("--HDraw::paint right tile:x=%d,y=%d,w=%d,h=%d",x_target,y_target,w,h_target);
            painter->drawPixmap(x_target, y_target, w, h_target, pixmap, tile.mRight.p0, tile.mY.p0, w_right, h_tile);
        }
    }
    return ;
}

void HDraw::paint(QPainter* painter,const QRect& rect,
                  const QPixmap& pixmap, const QMargins& m, const HImageTile& imgtile,int idx)
{
    QRect rc = rect.marginsRemoved(m);
    int w_target = rc.width();
    int h_target = rc.height();
    if (w_target<=0 || h_target<=0)
        return;

    //qDebug("HDraw::paint begin key:%lld,x:%d,y=%d,w=%d,h=%d",pixmap.cacheKey(),rc.left(),rc.top(),w_target,h_target);

    HImageTile nextimgtile=imgtile;
    nextimgtile.next(idx);

    H9Tile* tile = &nextimgtile.m9Tile;
    if (tile->onlyOne())
        nextimgtile.sysTile();

    int y_targetV= rc.top();
    int h_targetV = tile->onlyOne()?h_target:((h_target>=tile->mOne.height())?tile->mOne.height():h_target);
    if (h_targetV>0)
    {
        QRect one_rc(rc.left(),y_targetV,w_target,h_targetV);
        //qDebug("HDraw::paint one tile:x=%d,y=%d,w=%d,h=%d",one_rc.left(),one_rc.top(),one_rc.width(),one_rc.height());

        paint(painter,one_rc,pixmap,tile->mOne);
        y_targetV += h_targetV;
    }

    if (tile->mTwo.height()>0) {
        int h = h_target-(h_targetV+tile->mThree.height());
        if (h>0) {
            QRect two_rc(rc.left(),y_targetV,w_target,h);
            //qDebug("HDraw::paint two tile:x=%d,y=%d,w=%d,h=%d",two_rc.left(),two_rc.top(),two_rc.width(),two_rc.height());

            paint(painter,two_rc,pixmap,tile->mTwo);
            h_targetV += h;
            y_targetV += h;
        }
    }

    if (tile->mThree.height()>0) {
        int h = h_target - h_targetV;
        if (h>0) {
            QRect three_rc(rc.left(),y_targetV,w_target,h);
            //qDebug("HDraw::paint three tile:x=%d,y=%d,w=%d,h=%d",three_rc.left(),three_rc.top(),three_rc.width(),three_rc.height());

            paint(painter,three_rc,pixmap,tile->mThree);
        }
    }
}
