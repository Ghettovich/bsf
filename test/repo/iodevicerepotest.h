#ifndef BSF_IODEVICEREPOTEST_H
#define BSF_IODEVICEREPOTEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class IODeviceRepoTest : public QObject {
Q_OBJECT

private slots:
    void initTestCase();
    void isIODeviceTypeFound();
    void isIODeviceListNotEmpty();
    void isIODeviceListFromArduinoEmpty();
    void cleanUpTestCase();
};


#endif //BSF_IODEVICEREPOTEST_H
