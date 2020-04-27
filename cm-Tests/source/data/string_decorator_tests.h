#ifndef STRINGDECORATORTESTS_H
#define STRINGDECORATORTESTS_H

#include <QtTest>

#include <data/string_decorator.h>

#include <test_suite.h>

namespace cm {
namespace data {

class StringDecoratorTests : public TestSuite
{
  Q_OBJECT

public:
  StringDecoratorTests();

private slots:
  void constructor_givenNoParameters_setsDefaultProperties();
  void constructor_givenParameters_setsProperties();

  void set_value_givenNewValue_updatesValueAndEmitsSignal();
  void set_value_givenSameValue_takesNoAction();

  void to_json_whenDefaultValue_returnsJson();
  void to_json_whenValueSet_returnsJson();

  void update_whenPresentInJson_updatesValue();
  void update_whenNotPresentInJson_updatesValueToDefault();
};

}}

#endif
