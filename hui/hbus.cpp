#include "hbus.h"
#include <QMetaMethod>
#include <QPluginLoader>

struct HBusSignalHandler
{
    QString signalName;
    QPointer<QObject> receiver;
    QMetaMethod	metaMethod;
};

class HBusSignal : public QList<HBusSignalHandler>
{
public:
    HBusSignal(){}
};

bool checkSlot( QObject *object, const char *method )
{
    int count = object->metaObject()->methodCount();
    for (int i = count - 1; i >= QObject::staticMetaObject.methodCount(); --i)
    {
        QMetaMethod mm = object->metaObject()->method(i);
        QString sig = mm.methodSignature();
        int pos = sig.indexOf('(');
        if(sig.left(pos) == method)
        {
            return true;
        }
    }
    return false;
}

QMetaMethod getSlotMethod( QObject *obejct, const char *slot )
{
    int count = obejct->metaObject()->methodCount();
    for (int i = count - 1; i >= QObject::staticMetaObject.methodCount(); --i) {
        QMetaMethod mm = obejct->metaObject()->method(i);
        QString sig = mm.methodSignature();
        int pos = sig.indexOf('(');
        if(sig.left(pos) == slot)
        {
            return mm;
        }
    }
    return QMetaMethod();
}
//
class HBusInterfaceAdaptor
{
public:
    HBusInterfaceAdaptor(QObject *obj);
    ~HBusInterfaceAdaptor(){}

    QVariant invoke( const char *method, const  QList<QVariant> &args);
    QVariant invoke(const QMetaMethod &mm, const QList<QVariant> &args);

private:
    QPointer<QObject> mObject;
};

HBusInterfaceAdaptor::HBusInterfaceAdaptor( QObject *obj )
    : mObject(obj)
{
}

QVariant HBusInterfaceAdaptor::invoke( const char *method, const QList<QVariant> &args )
{
    if(mObject) {
        QMetaMethod mm = getSlotMethod(mObject, method);
        if (mm.methodIndex() != -1) {
            return invoke(mm, args);
        }
    }
    return QVariant();
}

QVariant HBusInterfaceAdaptor::invoke( const QMetaMethod &mm, const QList<QVariant> &args )
{
    if(mm.parameterNames().count() <= args.count()) {
        QVarLengthArray<void *, 10> params;
        params.reserve(args.count());

        QVariant ret;

        QString returnType = mm.typeName();
        if(returnType.isEmpty()) {
            params.append( 0 );
        }
        else {
            params.append( const_cast<void*>(ret.constData()) );
        }

        for(int i = 0; i < args.count(); i++) {
            params.append( const_cast<void*>(args[i].constData()) );
        }
        mObject->qt_metacall(QMetaObject::InvokeMetaMethod, mm.methodIndex(), params.data());
        return ret;
    }
    return QVariant();
}

//
class HBusInterface
{
public:
    HBusInterface(HBus* bus, const QString &serviceName, const QString &interfaceName );
    QVariant call( const char *method, const QList<QVariant> &args );

private:
    HBusInterfaceAdaptor *adaptor();
    QString mServiceName;
    QString mInterfaceName;
    HBusInterfaceAdaptor *mAdaptor;
    HBus* mBus;
};

HBusInterface::HBusInterface(HBus* bus, const QString &serviceName, const QString &interfaceName )
    : mServiceName(serviceName) ,
      mInterfaceName(interfaceName) ,
      mAdaptor(NULL) ,
      mBus(bus)
{
}

QVariant HBusInterface::call( const char *method, const QList<QVariant> &args )
{
    HBusInterfaceAdaptor *interfaceAdaptor = adaptor();
    if (interfaceAdaptor) {
        return interfaceAdaptor->invoke( method, args );
    }
    return QVariant();
}

HBusInterfaceAdaptor * HBusInterface::adaptor()
{
    if (!mAdaptor) {
        HBusService *service = mBus->serviceOf( mServiceName );
        if (!service) {
            if (mBus->module() &&
                    mBus->module()->loadModule(mServiceName)) {
                service = mBus->serviceOf( mServiceName );
            }
        }
        if (service) {
            mAdaptor = service->interfaceOf( mInterfaceName );
        }
    }
    return mAdaptor;
}

//
class HBusPrivate
{
public:
    HBusPrivate()
        : mReentrant(0)
        , mServiceModule(NULL)
    {
    }
    QHash<QString, HBusService*> mServices;
    QHash<QString, HBusSignal*> mSignals;
    int mReentrant;
    IHServiceModule* mServiceModule;
};

HBus::HBus()
     : d(new HBusPrivate())
{
}

HBus::~HBus()
{
    removeAll();
    hDelete(d);
}

void HBus::setServiceModule(IHServiceModule* module)
{
    d->mServiceModule = module;
}

HBusService *HBus::addService( const QString &serviceName )
{
    QHash<QString, HBusService*>::iterator iter = d->mServices.find(serviceName);
    if (iter!=d->mServices.end())
        return iter.value();

    HBusService *service = new HBusService( serviceName );
    d->mServices[serviceName] = service;
    return service;
}

void HBus::removeService( const QString &serviceName )
{
    QHash<QString, HBusService*>::iterator iter = d->mServices.find(serviceName);
    if (iter != d->mServices.end()) {
        HBusService *service = iter.value();
        d->mServices.erase(iter);
        hDelete(service);
    }
}

void HBus::removeAll()
{
    foreach(HBusService *service, d->mServices.values()) {
        hDelete(service);
    }
    d->mServices.clear();

    foreach(HBusSignal *signal, d->mSignals.values()) {
        hDelete(signal);
    }
    d->mSignals.clear();
}

HBusService *HBus::serviceOf( const QString &serviceName )
{
    if( d->mServices.contains(serviceName) ) {
        return d->mServices[serviceName];
    }
    return NULL;
}

IHServiceModule* HBus::module() const
{
    return d->mServiceModule;
}

void HBus::notify( const QString &serviceName, const QString &signalName, const QVariantList &args )
{
    QHash<QString,HBusSignal*>::iterator iter = d->mSignals.find(serviceName);
    if (iter==d->mSignals.end()) {
        return;
    }
    d->mReentrant++;

    HBusSignal* signal = iter.value();
    bool needClear = false;
    int  count = signal->count();
    for(int i = 0; i < count; i++) {
        const HBusSignalHandler &handler = signal->at(i);
        if (handler.receiver) {
            if (handler.signalName == signalName) {
                HBusInterfaceAdaptor adaptor(handler.receiver);
                adaptor.invoke(handler.metaMethod, args);
            }
        }
        else {
            needClear = true;
        }
    }

    if (needClear && d->mReentrant == 1) {
        int count = signal->count();
        for(int i = count - 1; i >= 0; i--) {
            const HBusSignalHandler &handler = signal->at(i);
            if(handler.receiver == NULL) {
                signal->removeAt(i);
            }
        }

        if (signal->count()<=0) {
            d->mSignals.erase(iter);
            delete signal;
        }
    }
    d->mReentrant--;
}

bool HBus::connect( const QString &serviceName,
                    const QString &signalName, QObject *receiver, const char *slot )
{
    QMetaMethod method = getSlotMethod(receiver, slot);
    if (method.methodIndex() == -1) {
        return false;
    }

    HBusSignal* signal = NULL;
    QHash<QString,HBusSignal*>::iterator iter = d->mSignals.find(serviceName);
    if (iter==d->mSignals.end()) {
        signal = new HBusSignal();
        d->mSignals[serviceName] = signal;
    }
    else {
        signal = iter.value();
    }

    int count = signal->count();
    for(int i = 0; i < count; i++)
    {
        const HBusSignalHandler &handler = signal->at(i);
        if	(handler.signalName == signalName
             && handler.receiver == receiver
             && handler.metaMethod.methodIndex() == method.methodIndex())
        {
            return true;
        }
    }

    HBusSignalHandler handler;
    handler.signalName = signalName;
    handler.receiver = receiver;
    handler.metaMethod = method;
    signal->append(handler);
    return true;
}

void HBus::disconnect( const QString &serviceName,
                       const QString &signalName, QObject *receiver, const char *slot )
{
    QMetaMethod method = getSlotMethod(receiver, slot);
    if (method.methodIndex() == -1) {
        return;
    }

    QHash<QString,HBusSignal*>::iterator iter = d->mSignals.find(serviceName);
    if (iter==d->mSignals.end()) {
        return;
    }

    HBusSignal* signal = iter.value();
    int count = signal->count();
    for(int i = 0; i < count; i++) {
        HBusSignalHandler &handler = (*signal)[i];
        if	(handler.signalName == signalName
             && handler.receiver == receiver
             && handler.metaMethod.methodIndex() == method.methodIndex()) {
            if(d->mReentrant > 0) {
                handler.receiver = NULL;
            }
            else {
                signal->removeAt(i);
            }
            break;
        }
    }
}

QVariant HBus::directCall( const QString &serviceName,
                           const QString &interfaceName, const char *methodName, const QVariantList &args )
{
    HBusInterface ia(this,serviceName, interfaceName);
    return ia.call(methodName, args);
}

HBusService::HBusService( const QString &serviceName )
    : mName( serviceName )
{
}

HBusService::~HBusService()
{
    removeAll();
}

bool HBusService::addInterface( const QString &interfaceName, QObject *object )
{
    QHash<QString, HBusInterfaceAdaptor*>::iterator iter = mInterfaces.find(interfaceName);
    if (iter!=mInterfaces.end())
        return true;

    HBusInterfaceAdaptor *adaptor = new HBusInterfaceAdaptor( object );
    mInterfaces[interfaceName] = adaptor;
    return true;
}

void HBusService::removeInterface(const QString &interfaceName)
{
    QHash<QString, HBusInterfaceAdaptor*>::iterator iter = mInterfaces.find(interfaceName);
    if (iter!=mInterfaces.end()) {
        HBusInterfaceAdaptor* adaptor = iter.value();
        mInterfaces.erase(iter);
        hDelete(adaptor);
    }
}

void HBusService::removeAll()
{
    foreach(HBusInterfaceAdaptor *adaptor, mInterfaces.values())
    {
        hDelete(adaptor);
    }
    mInterfaces.clear();
}

HBusInterfaceAdaptor * HBusService::interfaceOf( const QString &interfaceName )
{
    return mInterfaces[interfaceName];
}

QString HBusService::name() const
{
    return mName;
}
