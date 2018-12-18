#-------------------------------------------------
#
# Project created by QtCreator 2018-11-23T21:59:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LightBulb
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    channel.cpp \
    channelmanager.cpp \
    networkhandler.cpp \
    settingspanel.cpp \
    outputhandler.cpp \
    settingsenttecpro.cpp \
    channelupdater.cpp \
    settingsartnet.cpp

HEADERS += \
        mainwindow.h \
    channel.h \
    channelmanager.h \
    networkhandler.h \
    settingspanel.h \
    outputhandler.h \
    settingsenttecpro.h \
    channelupdater.h \
    settingsartnet.h

FORMS += \
        mainwindow.ui \
    channel.ui \
    channelmanager.ui \
    settingspanel.ui \
    settingsenttecpro.ui \
    settingsartnet.ui

unix|win32: LIBS += -L$$PWD/../Libs/LPL/ -lplanklight

INCLUDEPATH += $$PWD/../Libs/LPL
DEPENDPATH += $$PWD/../Libs/LPL

unix|win32: LIBS += -lftd2xx


unix|win32: LIBS += -lboost_chrono.1.68

unix|win32: LIBS += -lboost_system.1.68

unix|win32: LIBS += -lboost_thread.1.68
