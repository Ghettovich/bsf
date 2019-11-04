#-------------------------------------------------
#
# Project created by QtCreator 2019-08-17T13:19:52
#
#-------------------------------------------------

QT       += core gui network sql

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
        src/data/dbmanager.cpp \
        src/domain/arduino.cpp \
        src/domain/distantcensor.cpp \
        src/domain/iodevice.cpp \
        src/domain/weightcensor.cpp \
        src/model/logtablemodel.cpp \
        src/ui/forms/deviceform.cpp \
        src/ui/forms/devicemanager.cpp \
        src/ui/tabs/arduinotab.cpp \
        src/ui/tabs/controlpaneltab.cpp \
        src/ui/tabs/logtab.cpp \
        src/ui/tabs/recipetab.cpp \
        src/ui/widgets/maintabbarwidget.cpp \
        src/ui/mainwindow.cpp
        main.cpp
        server.cpp

HEADERS += \
        mainwindow.h \
        server.h
        incl/data/dbmanager.h \
        incl/domain/arduino.h \
        incl/domain/distantcensor.h \
        incl/domain/iodevice.h \
        incl/domain/weightcensor.h \
        incl/model/logtablemodel.h \
        ui/forms/deviceform.h \
        ui/forms/devicemanager.h \
        ui/tabs/arduinotab.h \
        ui/tabs/controlpaneltab.h \
        ui/tabs/iodevice.h \
        ui/tabs/logtab.h \
        ui/tabs/recipetab.h \
        ui/widgets/maintabbarwidget.h \
        ui/mainwindow.h \

FORMS += \
        mainwindow.ui
        devicewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
