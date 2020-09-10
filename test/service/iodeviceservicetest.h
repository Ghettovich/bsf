#ifndef BSF_IODEVICESERVICETEST_H
#define BSF_IODEVICESERVICETEST_H

#include <QtCore/QObject>
#include <QtTest/QtTest>

class IODeviceServiceTest : public QObject {
    Q_OBJECT

private:
    QString connectionString = "data/bsfTest.db";

private slots:
    void initTestCase();
    void myFirstTest();
    void cleanupTestCase();
};


#endif //BSF_IODEVICESERVICETEST_H
