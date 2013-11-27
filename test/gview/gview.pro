#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T22:58:30
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gview
TEMPLATE = app

CONFIG(debug, debug|release) {
     DESTDIR = ../../bin/debug
} else {
     DESTDIR = ../../bin/release
}

SOURCES += main.cpp\
        mainwindow.cpp \

HEADERS  += mainwindow.h \
    hmaintest.h \

RESOURCES += \
    hmaintest.qrc

OTHER_FILES +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../bin/release/ -lhui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../bin/debug/ -lhui
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../../bin/release/ -lhui
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../bin/debug/ -lhui

INCLUDEPATH += $$PWD/../../hui
DEPENDPATH += $$PWD/../../hui
