#ifndef HBUS_H
#define HBUS_H

#include "hbase.h"

class IHServiceModule
{
public:
    virtual ~IHServiceModule() {}

    virtual bool loadModule( const QString &serviceName ) = 0;
};

class HBusService;
class HBusPrivate;

class H_API HBus
{
    friend class HBusService;
    friend class HBusInterface;
    friend class HBusInterfaceAdaptor;

public:
    explicit HBus();
    ~HBus();

    void setServiceModule(IHServiceModule* module);

    HBusService *addService( const QString &serviceName );
    void removeService( const QString &serviceName );
    void removeAll();

    bool connect(const QString &serviceName, const QString &signalName, QObject *receiver, const char *slot);
    void disconnect(const QString &serviceName, const QString &signalName, QObject *receiver, const char *slot);
    void notify(const QString &serviceName, const QString &signalName, const QVariantList &args);

    QVariant directCall(const QString &serviceName, const QString &interfaceName, const char *methodName, const QVariantList &args);
private:
    HBusService *serviceOf( const QString &serviceName );
    IHServiceModule* module() const;
private:
    HBusPrivate *d;
};

//
class HBusInterfaceAdaptor;
class H_API HBusService
{
    friend class HBus;
    friend class HBusInterface;

public:
    bool addInterface(const QString &interfaceName, QObject *object );
    void removeInterface(const QString &interfaceName);
    void removeAll();
    QString name() const;

private:
    HBusService( const QString &serviceName );
    ~HBusService();

    HBusInterfaceAdaptor *interfaceOf( const QString &interfaceName );

private:
    QHash<QString, HBusInterfaceAdaptor*> mInterfaces;
    QString mName;
};

#endif // HBUS_H
