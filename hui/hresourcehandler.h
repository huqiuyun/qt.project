#ifndef HRESOURCEHANDLER_H
#define HRESOURCEHANDLER_H

#include "hconfig.h"
#include <QByteArray>
#include <QPixmap>

class H_API HResourceHandler
{
public:
    HResourceHandler(){}
    virtual ~HResourceHandler(){}

public:
    virtual bool loadImage(const QString& file, QPixmap& pixmap) = 0;
    virtual bool loadData(const QString& file, QByteArray &bytes) = 0;
protected:
    bool isRelativePath(const QString& path);
};

class H_API HAbsoluteHandler : public HResourceHandler
{
protected:
    bool loadImage(const QString& file, QPixmap& pixmap);
    bool loadData(const QString& file, QByteArray &bytes);
};

/** app/bin/data/{file} */
class H_API HDefaultHandler : public HAbsoluteHandler
{
private:
    bool loadImage(const QString& file, QPixmap& pixmap);
    bool loadData(const QString& file, QByteArray &bytes);
private:
    QString absolutePath(const QString& path);
    QString realPath(const QString& path);
};

/** path= :/theme/ */
class H_API HQtHandler : public HAbsoluteHandler
{
private:
    bool loadImage(const QString& file, QPixmap& pixmap);
    bool loadData(const QString& file, QByteArray &bytes);
private:
     QString realPath(const QString& path);
};

/** path="?/{pluginid}/" --> */
class H_API HPluginHandler : public HAbsoluteHandler
{
private:
    bool loadImage(const QString& file, QPixmap& pixmap);
    bool loadData(const QString& file, QByteArray &bytes);
protected:
    bool splitPath(const QString& path, QString& pluginid, QString& relPath);

    QString realPath(const QString& pluginid,const QString& relPath);
    QString absolutePath(const QString& pluginid,const QString& path);
    QString pluginWithVersion(const QString& pluginid);
};

#endif // HRESOURCEHANDLER_H
