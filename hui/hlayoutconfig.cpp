#include "HLayoutConfig.h"
#include "hstyle.h"
#include "hcore.h"

class HLayoutConfigPrivate
{
public:
    HLayoutConfigPrivate()
    {
       mRow = -1;
       mColumn =  mStretch = 0;
       mAlign = 0;
       mStyle = NULL;
    }

    int mRow;
    int mColumn;
    int mStretch;
    QMargins mMargins;
    Qt::Alignment mAlign;
    HClassInfo mProxyClsInfo;
    const HStyle* mStyle;
};

HLayoutConfig::HLayoutConfig(QObject *parent) :
    QObject(parent),
    d_ptr(new HLayoutConfigPrivate())
{
}

HLayoutConfig::HLayoutConfig(int index, QObject *parent) :
    QObject(parent),
    d_ptr(new HLayoutConfigPrivate())
{
    d_ptr->mRow = index;
}

HLayoutConfig::HLayoutConfig(int row,int col,QObject *parent):
    QObject(parent),
    d_ptr(new HLayoutConfigPrivate())
{
    d_ptr->mRow = row;
    d_ptr->mColumn = col;
}

HLayoutConfig::~HLayoutConfig()
{
    delete d_ptr;
}

void HLayoutConfig::setStyle(const HStyle* style)
{
    d_ptr->mStyle = style;
}

const HStyle* HLayoutConfig::style() const
{
    return d_ptr->mStyle?d_ptr->mStyle:HSTYLE;
}

int HLayoutConfig::index() const
{
    return d_ptr->mRow;
}

void HLayoutConfig::setIndex(int idx)
{
    d_ptr->mRow = idx;
}

int HLayoutConfig::row() const
{
    return d_ptr->mRow;
}

void HLayoutConfig::setRow(int row)
{
    d_ptr->mRow = row;
}

int HLayoutConfig::column() const
{
    return d_ptr->mColumn;
}

void HLayoutConfig::setColumn(int col)
{
    d_ptr->mColumn = col;
}

int HLayoutConfig::stretch() const
{
    return d_ptr->mStretch;
}

void HLayoutConfig::setStretch(int s)
{
    d_ptr->mStretch = s;
}

void HLayoutConfig::setMargins(const QMargins& m)
{
    d_ptr->mMargins = m;
}

QMargins HLayoutConfig::margins() const
{
    return d_ptr->mMargins;
}

void HLayoutConfig::setAlignment(Qt::Alignment align)
{
    d_ptr->mAlign = align;
}

Qt::Alignment HLayoutConfig::alignment() const
{
    return d_ptr->mAlign;
}

HClassInfo HLayoutConfig::proxyWidget() const
{
    return d_ptr->mProxyClsInfo;
}

void HLayoutConfig::addChild(const QString& name,const HClassInfo& info)
{
    if (name==QLatin1String("proxyWidget"))
        d_ptr->mProxyClsInfo = info;
}

