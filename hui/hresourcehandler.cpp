#include "hresourcehandler.h"
#include "hcore.h"
#include "hsystem.h"
#include <QDir>
#include <QRegExp>

//HResourceHandler
bool HResourceHandler::isRelativePath(const QString& path)
{
    if (path.isEmpty())
        return false;

    if (!QDir::isRelativePath(path)) {
        return false;
    }

    QRegExp reg("[\\*\\?\\|\\<\\>\\\"\\:]");
    if (path.contains(reg)) {
        return false;
    }
    return true;
}

//HAbsoluteHandler
bool HAbsoluteHandler::loadImage(const QString& path, QPixmap& pixmap)
{
    return pixmap.load(path);
}

bool HAbsoluteHandler::loadData(const QString& path, QByteArray &bytes)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        bytes = file.readAll();
        return true;
    }
    return false;
}

//HDefaultHandler
bool HDefaultHandler::loadImage(const QString& path, QPixmap& pixmap)
{
    if (isRelativePath(path)) {
        return HAbsoluteHandler::loadImage(realPath(path),pixmap);
    }
    return false;
}

bool HDefaultHandler::loadData(const QString& path, QByteArray &bytes)
{
    if (isRelativePath(path)) {
        return HAbsoluteHandler::loadData(realPath(path),bytes);
    }
    return false;
}

QString HDefaultHandler::realPath(const QString& path)
{// is
    return absolutePath(path);
}

QString HDefaultHandler::absolutePath(const QString& path)
{
    return QString(HSYSTEM->dataPath()+path);
}

//HQtHandler
bool HQtHandler::loadImage(const QString& path, QPixmap& pixmap)
{
    if(path.startsWith(":/")) {
        return HAbsoluteHandler::loadImage(realPath(path),pixmap);
    }
    return false;
}

bool HQtHandler::loadData(const QString& path, QByteArray &bytes)
{
    if(path.startsWith(":/")) {
        return HAbsoluteHandler::loadData(realPath(path),bytes);
    }
    return false;
}

QString HQtHandler::realPath(const QString& path)
{//
    return path;
}

//HPluginHandler
bool HPluginHandler::loadImage(const QString& path, QPixmap& pixmap)
{
    Q_UNUSED(pixmap);
    if(path.startsWith('?')) {
        QString pluginid,relPath;
        if (!splitPath(path,pluginid,relPath)) return false;
        return HAbsoluteHandler::loadImage(realPath(pluginid,relPath),pixmap);
    }
    return false;
}

bool HPluginHandler::loadData(const QString& path, QByteArray &bytes)
{
    Q_UNUSED(bytes);
    if(path.startsWith('?')) {
        QString pluginid,relPath;
        if (!splitPath(path,pluginid,relPath)) return false;

        return HAbsoluteHandler::loadData(realPath(pluginid,relPath),bytes);
    }
    return false;
}

bool HPluginHandler::splitPath(const QString& path, QString& pluginid, QString& relPath)
{
    QRegExp reg("[\\\\/]");
    int index = path.indexOf(reg,1);
    if (index<=0) return false;
    pluginid = path.mid(1,index-1);
    relPath = path.mid(index);
    return true;
}

QString HPluginHandler::realPath(const QString& pluginid,const QString& relPath)
{
    return absolutePath(pluginid,relPath);
}

QString HPluginHandler::absolutePath(const QString& pluginid,const QString& relPath)
{
   return QString(HSYSTEM->pluginPath() + pluginWithVersion(pluginid) + relPath);
}

QString HPluginHandler::pluginWithVersion(const QString& pluginid)
{
    int version = 0; //go to get plugin version information
    return (version > 0) ? QString("%1/%2").arg(pluginid).arg(version) : pluginid;
}
