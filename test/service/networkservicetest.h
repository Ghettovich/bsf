#ifndef BSF_NETWORKSERVICETEST_H
#define BSF_NETWORKSERVICETEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class NetworkServiceTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void requestFullStatePayload();
    void cleanupTestCase();
};


#endif //BSF_NETWORKSERVICETEST_H
