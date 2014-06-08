#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T22:58:30
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hui
TEMPLATE = lib


CONFIG(debug, debug|release) {
     DESTDIR = ../../bin/debug
} else {
     DESTDIR = ../../bin/release
}

DEFINES += BUILD_HUI

SOURCES += hcore.cpp \
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
    himagestyle.cpp \
    hbasestyle.cpp \
    hgwidgetstyle.cpp \
    hstyle.cpp \
    hqwidget.cpp \
    hwidgetstyle.cpp \
    hgscene.cpp \
    hgproxywidget.cpp \
    huitask.cpp \
    hpropertyproxy.cpp \
    hfontstyle.cpp \
    hdraw.cpp \
    hgbutton.cpp \
    hgroup.cpp \
    hglable.cpp \
    hcolorstyle.cpp \
    hgcombobox.cpp \
    hlayoutconfig.cpp \
    hglobal.cpp \
    hgtree.cpp \
    hgsplitter.cpp \
    hgcaption.cpp \
    hbus.cpp \
    hgscrollbar.cpp \
    hgscrollarea.cpp \
    hganimation.cpp \
    hgitemview.cpp \
    hglistbox.cpp \
    hlayout.cpp \
    hglayout.cpp \
    hqlayout.cpp \
    hgsceneitem.cpp

HEADERS  += hconfig.h \
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
    hcreator.h \
    private/hgwidget_p.h \
    hgwidget.h \
    private/hgview_p.h \
    hgview.h \
    hgstackedwidget.h \
    hresourcehandler.h \
    henums.h \
    himagestyle.h \
    private/himagestyle_p.h \
    hbasestyle.h \
    hgwidgetstyle.h \
    hstyle.h \
    hqwidget.h \
    hwidgetstyle.h \
    private/hqwidget_p.h \
    hgscene.h \
    hgproxywidget.h \
    private/hgproxywidget_p.h \
    huitask.h \
    hpropertyproxy.h \
    hfontstyle.h \
    hdraw.h \
    hgbutton.h \
    hgroup.h \
    hglable.h \
    hcolorstyle.h \
    hgcombobox.h \
    hlayoutconfig.h \
    hglobal.h \
    hgtree.h \
    hgsplitter.h \
    hgcaption.h \
    hbus.h \
    hgscrollbar.h \
    hgscrollarea.h \
    hganimation.h \
    hgitemview.h \
    private/hgitemview_p.h \
    private/hgscrollarea_p.h \
    hglistbox.h \
    hglayout.h \
    hlayout.h \
    hqlayout.h \
    hgsceneitem.h

OTHER_FILES +=
