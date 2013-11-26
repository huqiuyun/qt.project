#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T22:58:30
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hui
TEMPLATE = app

DEFINES += BUILD_HFW

SOURCES += main.cpp\
        mainwindow.cpp \
    hcore.cpp \
    hbase.cpp \
    hfactory.cpp \
    hunknown.cpp \
    hresourcemgr.cpp \
    hframestyle.cpp \
    huireader.cpp \
    hsystem.cpp \
    hcreator.cpp \
    hgwidget.cpp \
    hgview.cpp \
    hgstackedwidget.cpp \
    hresourcehandler.cpp \
    hbackgroundstyle.cpp \
    hlayoutstyle.cpp \
    hgscenestyle.cpp \
    hbasestyle.cpp \
    hqlayoutstyle.cpp \
    hglayoutstyle.cpp \
    hgwidgetstyle.cpp \
    hstyle.cpp \
    hqwidget.cpp \
    hwidgetstyle.cpp \
    hgscene.cpp \
    hgproxywidget.cpp \
    huitask.cpp \
    hpropertyproxy.cpp \
    hfontstyle.cpp



win32:{
SOURCES +=
}

HEADERS  += mainwindow.h \
    hconfig.h \
    hcore.h \
    hbase.h \
    private/hcore_p.h \
    hfactory.h \
    hfactory_i.h \
    hguid.h \
    hunknown.h \
    hunknown_i.h \
    herror.h \
    hctypes.h \
    hresourcemgr.h \
    hframestyle.h \
    huireader.h \
    hsystem.h \
    hmaintest.h \
    hcreator.h \
    private/hgwidget_p.h \
    hgwidget.h \
    private/hgview_p.h \
    hgview.h \
    hgstackedwidget.h \
    hresourcehandler.h \
    henums.h \
    hbackgroundstyle.h \
    hlayoutstyle.h \
    hgscenestyle.h \
    private/hbackgroundstyle_p.h \
    hbasestyle.h \
    hqlayoutstyle.h \
    hglayoutstyle.h \
    hgwidgetstyle.h \
    hstyle.h \
    hqwidget.h \
    hwidgetstyle.h \
    private/hqwidget_p.h \
    hgscene.h \
    hattributeproxy.h \
    hgproxywidget.h \
    huitask.h \
    hpropertyproxy.h \
    hfontstyle.h

FORMS    += mainwindow.ui

RESOURCES += \
    hmaintest.qrc

OTHER_FILES +=
