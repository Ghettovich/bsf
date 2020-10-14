#ifndef BSF_TST_NETWORKSERVICE_H
#define BSF_TST_NETWORKSERVICE_H

#include "AutoTest.h"
#include <QtCore/QObject>

class NetworkServiceTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void requestFullStatePayload();
    //void setRecipeForWeightStation();
    void cleanupTestCase();
};


#endif //BSF_TST_NETWORKSERVICE_H
