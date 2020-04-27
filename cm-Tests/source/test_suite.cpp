#include "test_suite.h"

namespace cm {

TestSuite::
TestSuite(const QString& name) : name{ name } {
  qDebug() << "Creating test " << name;
  test_list().push_back(this);
  qDebug() << test_list().size() << " tests recorded";
}

TestSuite::
~TestSuite() {
  qDebug() << "Destroying test";
}

QVector<TestSuite*>& TestSuite::
test_list() {
  static QVector<TestSuite*> instance{};
  return instance;
}

}
