#ifndef BSF_LOGSERVICETEST_H
#define BSF_LOGSERVICETEST_H

#include "AutoTest.h"
#include <QtCore/QObject>

class LogServiceTest : public QObject {
    Q_OBJECT

private:
    //const QString &connectionString = "data/bsfTest.db";

private slots:
    void initTestCase();
    void isLogListGreaterThenZero();
    void cleanupTestCase();
};

//DECLARE_TEST(LogServiceTest)

#endif //BSF_LOGSERVICETEST_H
