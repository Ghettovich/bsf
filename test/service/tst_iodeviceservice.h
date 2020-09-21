#ifndef BSF_TST_IODEVICESERVICE_H
#define BSF_TST_IODEVICESERVICE_H

#include "AutoTest.h"
#include <QtCore/QObject>
#include <QtTest/QtTest>

class IODeviceServiceTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
};


#endif //BSF_TST_IODEVICESERVICE_H
