#ifndef BSF_TST_LOGSERVICE_H
#define BSF_TST_LOGSERVICE_H

#include "AutoTest.h"
#include <QtCore/QObject>

class LogServiceTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isLogListNotEmpty();
    void isLogListSizeIncreased();
    void cleanupTestCase();
};


#endif //BSF_TST_LOGSERVICE_H
