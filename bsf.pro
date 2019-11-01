#-------------------------------------------------
#
# Project created by QtCreator 2019-08-17T13:19:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bsf
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

CONFIG += c++11

SOURCES += \
        domain/iodevice.cpp \
        domain/weightcensor.cpp \
        loginframe.cpp \
        main.cpp \
        maintabbarwidget.cpp \
        mainwindow.cpp \
        models/logtablemodel.cpp \
        server.cpp \
        tabs/main/arduinotab.cpp \
        tabs/main/controlpaneltab.cpp \
        tabs/main/iodevicetab.cpp \
        tabs/main/logtab.cpp \
        tabs/main/recipetab.cpp

HEADERS += \
        headers/domain/arduino.h \
        headers/domain/distantcensor.h \
        headers/domain/iodevice.h \
        headers/domain/weightcensor.h \
        headers/tabs/main/controlpaneltab.h \
        maintabbarwidget.h \
        headers/models/logtablemodel.h \
        headers/tabs/main/arduinotab.h \
        headers/tabs/main/iodevicetab.h \
        headers/tabs/main/logtab.h \
        headers/tabs/main/recipetab.h \
        loginframe.h \
        mainwindow.h \
        server.h

FORMS += \
        mainwindow.ui
        devicewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
