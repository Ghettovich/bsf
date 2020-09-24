#ifndef BSF_TST_SOCKETMANAGER_H
#define BSF_TST_SOCKETMANAGER_H

#include "AutoTest.h"
#include <QtCore/QObject>

class SocketManagerTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void connectoToHost();
    void broadcastRecipePayload();
    void receivePayload();
    void cleanupTestCase();

};


#endif //BSF_TST_SOCKETMANAGER_H
