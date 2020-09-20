#include "tst_statecoderepo.h"
#include <repo/statecoderepo.h>

DECLARE_TEST_STATECODE_REPO(StateCodeRepoTest)

void StateCodeRepoTest::initTestCase() {
}

void StateCodeRepoTest::isStateCodeFound() {
    // ARRANGE
    int stateCodeId = 0;
    const QString message = "READY";
    StateCodeRepository stateCodeRepository;

    // ACT
    StateCode stateCode = stateCodeRepository.getStateCode(stateCodeId);

    // ASSERT
    QVERIFY(stateCode.getMessage().toUpper() == message);
}

void StateCodeRepoTest::cleanupTestCase() {
}


