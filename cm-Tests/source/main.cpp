#include <QTest>
#include <QDebug>
#include <test_suite.h>
#include <data/datetime_decorator_tests.h>
#include <data/enumerator_decorator_tests.h>
#include <data/integer_decorator_tests.h>
#include <data/string_decorator_tests.h>


using namespace cm;

int main(int argc, char *argv[])
{
    auto& list { TestSuite::test_list() } ;
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    qDebug() << "Starting test suite...";
    qDebug() << "Accessing tests from " << list;
    qDebug() << list.size() << " tests detected";

    int failedTestsCount = 0;

    for(TestSuite* i : list) {
        qDebug() << "Executing test " << i->name;
        QString filename(i->name + ".xml");
        int result =
            QTest::qExec(i, QStringList() << " " << "-o" << filename << "-xunitxml");
        qDebug() << "Test result " << result;
        if(result != 0) {
            failedTestsCount++;
        }
    }
    qDebug() << "Test suite complete - " <<
                QString::number(failedTestsCount) << " failures detected.";
    return failedTestsCount;
}
