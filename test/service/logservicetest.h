#ifndef BSF_LOGSERVICETEST_H
#define BSF_LOGSERVICETEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class LogServiceTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void isLogListGreaterThenZero();
    void isLogListSizeIncreased();
    void cleanupTestCase();
};


#endif //BSF_LOGSERVICETEST_H
