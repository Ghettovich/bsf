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
        src/controller/devicecontroller.cpp \
        src/controller/relaycontroller.cpp \
        src/data/bsfdatabaseconfig.cpp \
        src/domain/distantcensor.cpp \
        src/domain/iodevice.cpp \
        src/domain/weightcensor.cpp \
        src/model/logtablemodel.cpp \
        src/repo/arduinorepo.cpp \
        src/repo/relayrepo.cpp \
        src/ui/forms/deviceform.cpp \
        src/ui/forms/relayform.cpp \
        src/ui/tabs/arduinotab.cpp \
        src/ui/tabs/controlpaneltab.cpp \
        src/ui/tabs/iodevicetab.cpp \
        src/ui/tabs/logtab.cpp \
        src/ui/tabs/recipetab.cpp \
        src/ui/widgets/maintabbarwidget.cpp \
        src/ui/mainwindow.cpp
        main.cpp
        server.cpp

HEADERS += \
        incl/controller/devicecontroller.h \
        incl/controller/relaycontroller.h \
        incl/data/bsfdatabaseconfig.h \
        incl/domain/distantcensor.h \
        incl/domain/iodevice.h \
        incl/domain/weightcensor.h \
        incl/model/logtablemodel.h \
        incl/repo/arduinorepo.h \
        incl/repo/relayrepo.h \
        incl/ui/forms/deviceform.h \
        incl/ui/forms/relayform.h \
        incl/ui/tabs/arduinotab.h \
        incl/ui/tabs/controlpaneltab.h \
        incl/ui/tabs/iodevicetab.h \
        incl/ui/tabs/logtab.h \
        incl/ui/tabs/recipetab.h \
        incl/ui/widgets/maintabbarwidget.h \
        incl/ui/mainwindow.h \
        server.h

FORMS += \
        src/ui/mainwindow.ui
        src/ui/forms/devicewidget.ui
        src/ui/forms/testrelaywidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
