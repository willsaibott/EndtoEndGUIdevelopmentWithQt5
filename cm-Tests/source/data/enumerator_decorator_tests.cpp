#include "enumerator_decorator_tests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace cm {
namespace data { // Instance

static EnumeratorDecoratorTests instance;

EnumeratorDecoratorTests::EnumeratorDecoratorTests()
  : TestSuite( "EnumeratorDecoratorTests" )
{
}

}

namespace data { // Tests

void EnumeratorDecoratorTests::
constructor_givenNoParameters_setsDefaultProperties() {
  EnumeratorDecorator decorator;

  QCOMPARE(decorator.parent_entity(), nullptr);
  QCOMPARE(decorator.key(), QString("SomeItemKey"));
  QCOMPARE(decorator.label(), QString(""));
  QCOMPARE(decorator.value(), 0);
  QCOMPARE(decorator.value_description(), QString(""));
}

void EnumeratorDecoratorTests::
constructor_givenParameters_setsProperties() {
  Entity parent_entity;
  EnumeratorDecorator decorator(&parent_entity,
                                "Test Key",
                                "Test Label",
                                static_cast<int>(eTestEnum::Value2),
                                descriptionMapper);

  QCOMPARE(decorator.parent_entity(), &parent_entity);
  QCOMPARE(decorator.key(), QString("Test Key"));
  QCOMPARE(decorator.label(), QString("Test Label"));
  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
  QCOMPARE(decorator.value_description(), QString("Value 2"));
}

void EnumeratorDecoratorTests::
set_value_givenNewValue_updatesValueAndEmitsSignal() {
  Entity parent_entity;
  EnumeratorDecorator decorator(&parent_entity,
                                "Test Key",
                                "Test Label",
                                static_cast<int>(eTestEnum::Unknown),
                                descriptionMapper);
  QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Unknown));
  QCOMPARE(decorator.value_description(), QString(""));

  decorator.set_value(static_cast<int>(eTestEnum::Value2));

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
  QCOMPARE(decorator.value_description(), QString("Value 2"));
  QCOMPARE(valueChangedSpy.count(), 1);
}

void EnumeratorDecoratorTests::
set_value_givenSameValue_takesNoAction() {
  Entity parent_entity;
  EnumeratorDecorator decorator(&parent_entity,
                                "Test Key",
                                "Test Label",
                                static_cast<int>(eTestEnum::Value2),
                                descriptionMapper);
  QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
  QCOMPARE(decorator.value_description(), QString("Value 2"));

  decorator.set_value(static_cast<int>(eTestEnum::Value2));

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
  QCOMPARE(decorator.value_description(), QString("Value 2"));
  QCOMPARE(valueChangedSpy.count(), 0);
}

void EnumeratorDecoratorTests::
to_json_whenDefaultValue_returnsJson() {
  EnumeratorDecorator decorator;

  QCOMPARE(decorator.to_json(), QJsonValue(static_cast<int>(eTestEnum::Unknown)));
}

void EnumeratorDecoratorTests::
to_json_whenValueSet_returnsJson() {
  EnumeratorDecorator decorator;
  decorator.set_value(static_cast<int>(eTestEnum::Value2));

  QCOMPARE(decorator.to_json(), QJsonValue(static_cast<int>(eTestEnum::Value2)));
}

void EnumeratorDecoratorTests::
update_whenPresentInJson_updatesValue() {
  Entity parent_entity;
  EnumeratorDecorator decorator(&parent_entity,
                                "Test Key",
                                "Test Label",
                                static_cast<int>(eTestEnum::Value2),
                                descriptionMapper);
  QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
  QCOMPARE(decorator.value_description(), QString("Value 2"));

  QJsonObject jsonObject;
  jsonObject.insert("Key 1", "Value 1");
  jsonObject.insert("Test Key", static_cast<int>(eTestEnum::Value3));
  jsonObject.insert("Key 3", 3);

  decorator.update(jsonObject);

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value3));
  QCOMPARE(decorator.value_description(), QString("Value 3"));
  QCOMPARE(valueChangedSpy.count(), 1);
}

void EnumeratorDecoratorTests::
update_whenNotPresentInJson_updatesValueToDefault() {
  Entity parent_entity;
  EnumeratorDecorator decorator(&parent_entity,
                                "Test Key",
                                "Test Label",
                                static_cast<int>(eTestEnum::Value2),
                                descriptionMapper);
  QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
  QCOMPARE(decorator.value_description(), QString("Value 2"));

  QJsonObject jsonObject;
  jsonObject.insert("Key 1", "Value 1");
  jsonObject.insert("Key 2", 123);
  jsonObject.insert("Key 3", 3);

  decorator.update(jsonObject);

  QCOMPARE(decorator.value(), static_cast<int>(eTestEnum::Value2));
  QCOMPARE(decorator.value_description(), QString("Value 2"));
  QCOMPARE(valueChangedSpy.count(), 0);
}

}}
