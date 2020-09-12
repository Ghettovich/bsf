#include "statecoderepotest.h"
#include <repo/statecoderepo.h>

DECLARE_TEST_STATECODE_REPO(StateCodeRepoTest)

void StateCodeRepoTest::initTestCase() {
}

void StateCodeRepoTest::isStateCodeFound() {
    int stateCodeId = 1;
    QString connectionString = "data/bsfTest.db";
    StateCodeRepository stateCodeRepository(connectionString);

    StateCode stateCode = stateCodeRepository.getStateCode(0);

    QVERIFY(stateCode.getMessage().toUpper() == "READY");
}

void StateCodeRepoTest::cleanupTestCase() {
}


