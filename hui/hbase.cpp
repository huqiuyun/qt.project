#include "hbase.h"

HAnchor::HAnchor()
{
    Qt::AnchorPoint dummy[] = {
        Qt::AnchorLeft, Qt::AnchorRight,
        Qt::AnchorTop, Qt::AnchorBottom};
    for (uint i = 0; i < sizeof(dummy)/sizeof(dummy[0]); ++i)
    {
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
    for (int i = 0; i < 4; i++)
    {
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
    if (bytes.size()>= (int)sizeof(mItems))
    {
        memcpy((void*)&mItems[0], bytes.data(), sizeof(mItems));
    }
}
