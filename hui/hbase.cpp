#include "hbase.h"
#include <QMargins>

HAnchor::HAnchor()
{
    Qt::AnchorPoint dummy[] = {
        Qt::AnchorLeft, Qt::AnchorRight,
        Qt::AnchorTop, Qt::AnchorBottom};
    for (uint i = 0; i < sizeof(dummy)/sizeof(dummy[0]); ++i) {
        mItems[i].distance = 0;
        mItems[i].first  = dummy[i];
        mItems[i].second = dummy[i];
    }
}

HAnchor::HAnchor(const HAnchorItem_t item[4])
{
    for (int i = 0; i < 4; i++)
        mItems[i] = item[i];
}

HAnchor::HAnchor(const HAnchor& anchor)
{
    *this = anchor;
}

HAnchor& HAnchor::operator=(const HAnchor& anchor)
{
    for (int i = 0; i < 4; i++) {
        mItems[i] = anchor.mItems[i];
    }
    return *this;
}

int HAnchor::counts() const
{
    return 4;
}

HAnchorItem_t HAnchor::at(int p)
{
    return mItems[p];
}

void HAnchor::operator >> (QByteArray& bytes)
{
    bytes.append((const char*)&mItems[0],sizeof(mItems));
}

void HAnchor::operator << (const QByteArray& bytes)
{
    if (bytes.size()>= (int)sizeof(mItems)) {
        memcpy((void*)&mItems[0], bytes.data(), sizeof(mItems));
    }
}

void debugTile(const HTile& t)
{
    qDebug("--xLeft:%d,%d",t.mLeft.p0,t.mLeft.p1);
    qDebug("--xMid:%d,%d",t.mMid.p0,t.mMid.p1);
    qDebug("--xRight:%d,%d",t.mRight.p0,t.mRight.p1);
    qDebug("--y:%d,%d\n",t.mY.p0,t.mY.p1);
}


void HImageTile::initX(int x0, int x1)
{
    m9Tile.initX(mWidth,x0,x1);
}

void HImageTile::initY(int y0, int y1)
{
    m9Tile.initY(mHeight,y0,y1);
}

bool HImageTile::next(int idx)
{
    int hori = idx%mHoriLine;
    int vert = idx/mHoriLine;
    if (vert>=mVertLine)
    {
        return false;
    }
    int w = mWidth*hori;
    int h = mHeight*vert;
    m9Tile.offsetX(w+hori);
    m9Tile.offsetY(h+vert);
    return true;
}

void HImageTile::sysTile()
{
    if (mSys) {
        divX();
        divY();
    }
}

void HImageTile::divX()
{
    int x = (mWidth-3);
    if (x<=0) return;
    x = x/2;
    initX(x,x+2);
}

void HImageTile::divY()
{
    int y = (mHeight-3);
    if (y<=0) return;
    y = y/2;
    initY(y,y+2);
}

void HImageTile::debug() const
{
    qDebug("HImageTile width=%d,height=%d,horiLine=%d,vertLine=%d",mWidth,mHeight,mHoriLine,mVertLine);
    debugTile(m9Tile.mOne);
    debugTile(m9Tile.mTwo);
    debugTile(m9Tile.mThree);
}
