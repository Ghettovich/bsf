#ifndef BSF_IODEVICESERVICETEST_H
#define BSF_IODEVICESERVICETEST_H

#include "AutoTest.h"
#include <QtCore/QObject>
#include <QtTest/QtTest>

class IODeviceServiceTest : public QObject {
    Q_OBJECT

private:
    //const QString &connectionString = "data/bsfTest.db";

private slots:
    void initTestCase();
    void isArduinoDeviceWidgetListOnLayout();
    void isDeviceActionFormCreated();
    void isIODeviceLayoutPopulated();
    void cleanupTestCase();
};


#endif //BSF_IODEVICESERVICETEST_H
