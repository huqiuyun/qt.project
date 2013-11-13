#include "hsystem.h"
#include <QStringList>

class HInternalVersion
{
public:
    static quint32 version(const QStringList& s,bool major)
    {
        int bit = s.size();
        if (major)
        {
            switch(bit)
            {
            case 1:  return (s[0].toUInt() << 16);
            case 2:  return ((s[0].toUInt() << 16) + s[1].toUInt());
            default: break;
            }
        }
        else if(bit>=2)
        {
            switch(bit)
            {
            case 3:  return (s[2].toUInt() << 16);
            case 4:  return (s[2].toUInt() << 16 + s[3].toUInt());
            default: break;
            }
        }
        return 0;
    }
};

HSystem::HSystem()
{
    mVersion = QLatin1String("1.0.0.0");
}

HSystem::~HSystem()
{
}

QString HSystem::appPath() const
{
    return mAppPath;
}

void HSystem::setAppPath(const QString& path)
{
    mAppPath = path;
}

QString HSystem::dataPath() const
{
    return mDataPath;
}

void HSystem::setDataPath(const QString& path)
{
    mDataPath = path;
}

QString HSystem::pluginPath() const
{
    return mPluginPath;
}

void HSystem::setPluginPath(const QString& path)
{
    mPluginPath = path;
}

/** 1.0.0.0*/
QString HSystem::version() const
{
    return mVersion;
}

void HSystem::setVersion(const QString& version)
{
    mVersion = version;
}

quint32 HSystem::versionInt(bool major) const
{
    QStringList s = mVersion.split(QLatin1Char('.'));
    return (major) ? HInternalVersion::version(s,true) : HInternalVersion::version(s,false);
}

void HSystem::versionToInt(const QString& version, quint32&  major, quint32& lower)
{
    QStringList s = version.split(QLatin1Char('.'));
    major = HInternalVersion::version(s,true);
    lower = HInternalVersion::version(s,false);
}

quint64 HSystem::versionTo64(const QString& version)
{
    quint32 major = 0;
    quint32 lower = 0;
    versionToInt(version,major,lower);
    return ((quint64)major <<32) + lower;
}

QVariant HSystem::attribute(const char* key)
{
    Attributes::iterator iter = mAttributes.find(QLatin1String(key));
    if (iter != mAttributes.end())
        return iter.value();

    return QVariant();
}

void HSystem::addAttribute(const char* key, const QVariant& val)
{
    mAttributes.insert(QLatin1String(key),val);
}

void HSystem::removeAttribute(const char* key)
{
    Attributes::iterator iter = mAttributes.find(QLatin1String(key));
    if (iter != mAttributes.end())
        mAttributes.erase(iter);
}

void HSystem::removeAllAttribute()
{
    mAttributes.clear();
}
