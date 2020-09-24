#ifndef BSF_TST_PAYLOADSERVICE_H
#define BSF_TST_PAYLOADSERVICE_H

#include "AutoTest.h"
#include <QtCore/QObject>

class PayloadServiceTest  : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void parsePayloadOnIncomingUdpPackets();
    void isUdpSocketErrorEmitted();
    void broadcastRecipePayload();
    void cleanupTestCase();
};


#endif //BSF_TST_PAYLOADSERVICE_H
