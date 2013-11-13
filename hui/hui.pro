#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T22:58:30
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

DEFINES += BUILD_HFW

SOURCES += main.cpp\
        mainwindow.cpp \
    hbackgrounditem.cpp \
    hcore.cpp \
    hbase.cpp \
    hcssstyle.cpp \
    hfactory.cpp \
    hunknown.cpp \
    hresourcemgr.cpp \
    hframestyle.cpp \
    huireader.cpp \
    hxmlreader.cpp \
    hxmlattributes.cpp \
    hsystem.cpp \
    hcreator.cpp \
    hgwidget.cpp \
    hgview_win32.cpp \
    hgview.cpp \
    hgstackedwidget.cpp



win32:{
SOURCES += \
    hframestyle_win32.cpp
}

HEADERS  += mainwindow.h \
    hbackgrounditem.h \
    hconfig.h \
    hcore.h \
    hbase.h \
    hcssstyle.h \
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
    hxmlreader.h \
    hxmlattributes.h \
    hsystem.h \
    hmaintest.h \
    hcreator.h \
    private/hgwidget_p.h \
    hgwidget.h \
    private/hgview_p.h \
    hgview.h \
    hgstackedwidget.h

FORMS    += mainwindow.ui
