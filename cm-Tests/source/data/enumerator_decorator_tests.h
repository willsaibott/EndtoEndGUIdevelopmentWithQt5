#ifndef ENUMERATORDECORATORTESTS_H
#define ENUMERATORDECORATORTESTS_H

#include <QtTest>

#include <data/enumerator_decorator.h>

#include <test_suite.h>

namespace cm {
namespace data {

class EnumeratorDecoratorTests : public TestSuite
{
  Q_OBJECT

public:
  EnumeratorDecoratorTests();

private slots:
  void constructor_givenNoParameters_setsDefaultProperties();
  void constructor_givenParameters_setsProperties();

  void set_value_givenNewValue_updatesValueAndEmitsSignal();
  void set_value_givenSameValue_takesNoAction();

  void to_json_whenDefaultValue_returnsJson();
  void to_json_whenValueSet_returnsJson();

  void update_whenPresentInJson_updatesValue();
  void update_whenNotPresentInJson_updatesValueToDefault();

private:
  enum class eTestEnum {
    Unknown = 0,
    Value1,
    Value2,
    Value3
  };

  const QMap<int, QString> descriptionMapper{
    {static_cast<int>(eTestEnum::Unknown), ""},
    {static_cast<int>(eTestEnum::Value1), "Value 1"},
    {static_cast<int>(eTestEnum::Value2), "Value 2"},
    {static_cast<int>(eTestEnum::Value3), "Value 3"}
  };
};

}}

#endif
