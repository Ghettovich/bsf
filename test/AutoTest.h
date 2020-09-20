#ifndef BSF_AUTOTEST_H
#define BSF_AUTOTEST_H

#include <QTest>
#include <QList>
#include <QString>
#include <QSharedPointer>
#include <server/httpserver.h>


namespace AutoTest
{
    typedef QList<QObject*> TestList;

    inline TestList& testList()
    {
        static TestList list;
        return list;
    }

    inline bool findObject(QObject* object)
    {
        TestList& list = testList();
        if (list.contains(object))
        {
            return true;
        }
                foreach (QObject* test, list)
            {
                if (test->objectName() == object->objectName())
                {
                    return true;
                }
            }
        return false;
    }

    inline void addTest(QObject* object)
    {
        TestList& list = testList();
        if (!findObject(object))
        {
            list.append(object);
        }
    }

    inline int run(int argc, char *argv[])
    {
        int ret = 0;

                foreach (QObject* test, testList())
            {
                ret += QTest::qExec(test, argc, argv);
            }

        return ret;
    }
}

template <class T>
class Test
{
public:
    QSharedPointer<T> child;

    Test(const QString& name) : child(new T)
    {
        child->setObjectName(name);
        AutoTest::addTest(child.data());
    }
};

#define DECLARE_TEST_LOGSERVICE(className) static Test<className> t("LogServiceTest");
#define DECLARE_TEST_IODEVICESERVICE(className) static Test<className> t("IODeviceServiceTest");
#define DECLARE_TEST_NETWORKSERVICE(className) static Test<className> t("NetworkServiceTest");
#define DECLARE_TEST_RECIPE(className) static Test<className> t(#className);
#define DECLARE_TEST_ARDUINO_REPO(className) static Test<className> t("ArduinoRepoTest");
#define DECLARE_TEST_ACTION_ARDUINO_REPO(className) static Test<className> t("ActionArduinoRepoTest");
#define DECLARE_TEST_IODEVICE_REPO(className) static Test<className> t("IODeviceRepoTest");
#define DECLARE_TEST_RECIPE_REPO(className) static Test<className> t("RecipeRepoTest");
#define DECLARE_TEST_STATECODE_REPO(className) static Test<className> t("StateCodeRepoTest");
#define DECLARE_TEST_TRANSFORMPAYLOAD(className) static Test<className> t("TransformPayloadTest");

#define TEST_MAIN \
 int main(int argc, char *argv[]) \
 {                \
    QApplication app(argc, argv); \
    ::testing::InitGoogleTest(&argc, argv); \
    return AutoTest::run(argc, argv); \
 }

#endif //BSF_AUTOTEST_H
