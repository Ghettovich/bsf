#include <QtTest/QtTest>
#include "service/iodeviceservicetest.h"
#include "service/logservicetest.h"
#include "recipetest.h"

int main(int argc, char *argv[])
{
    int status = 0;

    {
        LogServiceTest ta;
        status |= QTest::qExec(&ta, argc, argv);
    }
    {
        IODeviceServiceTest ta;
        status |= QTest::qExec(&ta, argc, argv);
    }
    {
        RecipeTest ta;
        status |= QTest::qExec(&ta, argc, argv);
    }

    return status;
}
