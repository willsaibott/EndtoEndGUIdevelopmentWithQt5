#ifndef DATETIMEDECORATORTESTS_H
#define DATETIMEDECORATORTESTS_H

#include <QtTest>

#include <data/datetime_decorator.h>

#include <test_suite.h>

namespace cm {
namespace data {

class DateTimeDecoratorTests : public TestSuite
{
  Q_OBJECT

public:
  DateTimeDecoratorTests();

private slots:
  void constructor_givenNoParameters_setsDefaultProperties();
  void constructor_givenParameters_setsProperties();

  void set_value_givenNewValue_updatesValueAndEmitsSignal();
  void set_value_givenSameValue_takesNoAction();

  void to_json_whenDefaultValue_returnsJson();
  void to_json_whenValueSet_returnsJson();

  void update_whenPresentInJson_updatesValue();
  void update_whenNotPresentInJson_updatesValueToDefault();

  void toIso8601String_whenDefaultValue_returnsString();
  void toIso8601String_whenValueSet_returnsString();
  void toPrettyDateString_whenDefaultValue_returnsString();
  void toPrettyDateString_whenValueSet_returnsString();
  void toPrettyTimeString_whenDefaultValue_returnsString();
  void toPrettyTimeString_whenValueSet_returnsString();
  void toPrettyString_whenDefaultValue_returnsString();
  void toPrettyString_whenValueSet_returnsString();

private:
  QDateTime testDate{QDate(2017, 8, 19), QTime(16, 40, 32)};
};

}}

#endif
