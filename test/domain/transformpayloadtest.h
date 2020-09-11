#ifndef BSF_TRANSFORMPAYLOADTEST_H
#define BSF_TRANSFORMPAYLOADTEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class TransformPayloadTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isArduinoUpdatedWithStateAndIODeviceList();
    void cleanupTestCase();

};


#endif //BSF_TRANSFORMPAYLOADTEST_H
