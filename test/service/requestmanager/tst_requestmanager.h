#ifndef BSF_TST_REQUESTMANAGER_H
#define BSF_TST_REQUESTMANAGER_H

#include "AutoTest.h"
#include <QtCore/QObject>


class RequestManagerTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isHttpCallReadyEmitted();
    void isHttpErrorEmitted();
    void cleanupTestCase();
};


#endif //BSF_TST_REQUESTMANAGER_H
