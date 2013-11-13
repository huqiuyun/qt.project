#ifndef HSYSTEM_H
#define HSYSTEM_H

#include "hconfig.h"
#include <QString>
#include <QMap>
#include <QVariant>

class H_API HSystem
{
public:
    HSystem();
    virtual ~HSystem();

public:
    QString appPath() const;
    void setAppPath(const QString& path);

    QString dataPath() const;
    void setDataPath(const QString& path);

    QString pluginPath() const;
    void setPluginPath(const QString& path);

    /** 1.0.0.0; 1.0,0 ; 1.0 */
    QString version() const;
    void setVersion(const QString& version);
    quint32 versionInt(bool major) const;
    void    versionToInt(const QString& version,quint32& major, quint32& lower);
    quint64 versionTo64(const QString& version);

    QVariant attribute(const char* key);
    void addAttribute(const char* key, const QVariant& val);
    void removeAttribute(const char* key);
    void removeAllAttribute();
private:
    typedef QMap<QLatin1String, QVariant> Attributes;
    Attributes mAttributes;
    QString mAppPath;
    QString mDataPath;
    QString mPluginPath;
    QString mVersion;
};

#endif // HSYSTEM_H
