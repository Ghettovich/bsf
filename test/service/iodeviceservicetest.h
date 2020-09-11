#ifndef BSF_IODEVICESERVICETEST_H
#define BSF_IODEVICESERVICETEST_H

#include "AutoTest.h"
#include <QtCore/QObject>
#include <QtTest/QtTest>

class IODeviceServiceTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
};


#endif //BSF_IODEVICESERVICETEST_H
