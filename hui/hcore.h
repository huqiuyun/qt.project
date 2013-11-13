#ifndef HCORE_H
#define HCORE_H

#include "hconfig.h"
#include <QObject>

class HResourceMgr;
class HCssStyle;
class HFactory;
class HSystem;
class HCorePrivate;

class H_API HCore : public QObject
{
public:
    Q_OBJECT
    Q_DECLARE_PRIVATE( HCore )
    Q_DISABLE_COPY( HCore )

public:
    explicit HCore(QObject *parent = 0);
    virtual ~HCore();

    static HCore* core();
    static void initHCore(HCore* core);

public:
    virtual HCssStyle* cssStyle();
    virtual HFactory*  factory();
    virtual HResourceMgr* resMgr();
    virtual HSystem* system();

protected:
    HCore(HCorePrivate& dd,QObject* parent = 0);

private:
    HCorePrivate* d_ptr;
    static HCore* gHCore;
};

#define HCORE       HCore::core()
#define HFACTORY    HCore::core()->factory()
#define HCSSSTYLE   HCore::core()->cssStyle()
#define HRESMGR     HCore::core()->resMgr()
#define HSYSTEM     HCore::core()->system()

#endif // HCORE_H
