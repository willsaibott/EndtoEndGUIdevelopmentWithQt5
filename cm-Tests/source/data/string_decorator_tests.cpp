#include "string_decorator_tests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace cm {
namespace data { // Instance

static StringDecoratorTests instance;

StringDecoratorTests::StringDecoratorTests()
  : TestSuite( "StringDecoratorTests" )
{
}

}

namespace data { // Tests

void StringDecoratorTests::
constructor_givenNoParameters_setsDefaultProperties() {
  StringDecorator decorator;

  QCOMPARE(decorator.parent_entity(), nullptr);
  QCOMPARE(decorator.key(), QString("SomeItemKey"));
  QCOMPARE(decorator.label(), QString(""));
  QCOMPARE(decorator.value(), QString(""));
}

void StringDecoratorTests::
constructor_givenParameters_setsProperties() {
  Entity parent_entity;
  StringDecorator decorator(&parent_entity, "Test Key", "Test Label", "Test Value");

  QCOMPARE(decorator.parent_entity(), &parent_entity);
  QCOMPARE(decorator.key(), QString("Test Key"));
  QCOMPARE(decorator.label(), QString("Test Label"));
  QCOMPARE(decorator.value(), QString("Test Value"));
}

void StringDecoratorTests::
set_value_givenNewValue_updatesValueAndEmitsSignal() {
  StringDecorator decorator;
  QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);

  QCOMPARE(decorator.value(), QString(""));

  decorator.set_value("New Value");

  QCOMPARE(decorator.value(), QString("New Value"));
  QCOMPARE(valueChangedSpy.count(), 1);
}

void StringDecoratorTests::
set_value_givenSameValue_takesNoAction() {
  Entity parent_entity;
  StringDecorator decorator(&parent_entity, "Test Key", "Test Label", "Test Value");
  QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);

  QCOMPARE(decorator.value(), QString("Test Value"));

  decorator.set_value("Test Value");

  QCOMPARE(decorator.value(), QString("Test Value"));
  QCOMPARE(valueChangedSpy.count(), 0);
}

void StringDecoratorTests::
to_json_whenDefaultValue_returnsJson() {
  StringDecorator decorator;

  QCOMPARE(decorator.to_json(), QJsonValue(""));
}

void StringDecoratorTests::
to_json_whenValueSet_returnsJson() {
  StringDecorator decorator;
  decorator.set_value("Test Value");

  QCOMPARE(decorator.to_json(), QJsonValue("Test Value"));
}

void StringDecoratorTests::
update_whenPresentInJson_updatesValue() {
  Entity parent_entity;
  StringDecorator decorator(&parent_entity, "Test Key", "Test Label", "Test Value");
  QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);

  QCOMPARE(decorator.value(), QString("Test Value"));

  QJsonObject jsonObject;
  jsonObject.insert("Key 1", "Value 1");
  jsonObject.insert("Test Key", "New Value");
  jsonObject.insert("Key 3", 3);

  decorator.update(jsonObject);

  QCOMPARE(decorator.value(), QString("New Value"));
  QCOMPARE(valueChangedSpy.count(), 1);
}

void StringDecoratorTests::
update_whenNotPresentInJson_updatesValueToDefault() {
  Entity parent_entity;
  StringDecorator decorator(&parent_entity, "Test Key", "Test Label", "Test Value");
  QSignalSpy valueChangedSpy(&decorator, &StringDecorator::valueChanged);

  QCOMPARE(decorator.value(), QString("Test Value"));

  QJsonObject jsonObject;
  jsonObject.insert("Key 1", "Value 1");
  jsonObject.insert("Key 2", "New Value");
  jsonObject.insert("Key 3", 3);

  decorator.update(jsonObject);

  QCOMPARE(decorator.value(), QString("Test Value"));
  QCOMPARE(valueChangedSpy.count(), 0);
}

}}
