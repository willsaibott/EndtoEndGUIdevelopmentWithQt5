#include "master_controller_tests.h"

namespace cm {
namespace controllers {

static MasterControllerTests instance;

MasterControllerTests::
MasterControllerTests() : TestSuite ("MasterControllerTests")
{

}

void MasterControllerTests::
initTestCase() {
  qDebug() << "before all...";
}

void MasterControllerTests::
cleanupTestCase() {
  qDebug() << "after all...";
}

void MasterControllerTests::
init() {
  qDebug() << "before each...";
}

void MasterControllerTests::
cleanup() {
  qDebug() << "after each...";
}

void MasterControllerTests::
welcomeMessage_returnsCorrectMessage() {
    QCOMPARE( master_controller.welcome_message(),
              QString{ "Welcome to the Client Management system!" } );
}
}
}
