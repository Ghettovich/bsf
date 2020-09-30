#include "tst_statecoderepo.h"
#include <repo/statecoderepo.h>

DECLARE_TEST_STATECODE_REPO(StateCodeRepoTest)

void StateCodeRepoTest::initTestCase() {
    db.createTestDatabase();
    db.insertData();
}

/*
 * Check if the statecode is found with id.
 * */
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


