#include "datetime_decorator_tests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace cm {
namespace data { // Instance

static DateTimeDecoratorTests instance;

DateTimeDecoratorTests::DateTimeDecoratorTests()
  : TestSuite( "DateTimeDecoratorTests" )
{
}

}

namespace data { // Tests

void DateTimeDecoratorTests::
constructor_givenNoParameters_setsDefaultProperties() {
  DateTimeDecorator decorator;

  QCOMPARE(decorator.parent_entity(), nullptr);
  QCOMPARE(decorator.key(), QString("SomeRandomKey"));
  QCOMPARE(decorator.label(), QString(""));
  QCOMPARE(decorator.value(), QDateTime());
}

void DateTimeDecoratorTests::
constructor_givenParameters_setsProperties() {
  Entity parent_entity;
  DateTimeDecorator decorator(&parent_entity, "Test Key", "Test Label", testDate);

  QCOMPARE(decorator.parent_entity(), &parent_entity);
  QCOMPARE(decorator.key(), QString("Test Key"));
  QCOMPARE(decorator.label(), QString("Test Label"));
  QCOMPARE(decorator.value(), testDate);
}

void DateTimeDecoratorTests::
set_value_givenNewValue_updatesValueAndEmitsSignal() {
  DateTimeDecorator decorator;
  QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);

  QCOMPARE(decorator.value(), QDateTime());

  decorator.set_value(testDate);

  QCOMPARE(decorator.value(), testDate);
  QCOMPARE(valueChangedSpy.count(), 1);
}

void DateTimeDecoratorTests::
set_value_givenSameValue_takesNoAction() {
  Entity parent_entity;
  DateTimeDecorator decorator(&parent_entity, "Test Key", "Test Label", testDate);
  QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);

  QCOMPARE(decorator.value(), testDate);

  decorator.set_value(testDate);

  QCOMPARE(decorator.value(), testDate);
  QCOMPARE(valueChangedSpy.count(), 0);
}

void DateTimeDecoratorTests::
to_json_whenDefaultValue_returnsJson() {
  DateTimeDecorator decorator;

  QCOMPARE(decorator.to_json(), QJsonValue(QDateTime().toString(Qt::ISODate)));
}

void DateTimeDecoratorTests::
to_json_whenValueSet_returnsJson() {
  DateTimeDecorator decorator;
  decorator.set_value(testDate);

  QCOMPARE(decorator.to_json(), QJsonValue(testDate.toString(Qt::ISODate)));
}

void DateTimeDecoratorTests::
update_whenPresentInJson_updatesValue() {
  Entity parent_entity;
  DateTimeDecorator decorator(&parent_entity, "Test Key", "Test Label", testDate);
  QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);

  QCOMPARE(decorator.value(), testDate);

  QJsonObject jsonObject;
  jsonObject.insert("Key 1", "Value 1");
  jsonObject.insert("Test Key", QDateTime(QDate(2016, 4, 18), QTime(10, 37, 14)).toString(Qt::ISODate));
  jsonObject.insert("Key 3", 3);

  decorator.update(jsonObject);

  QCOMPARE(decorator.value(), QDateTime(QDate(2016, 4, 18), QTime(10, 37, 14)));
  QCOMPARE(valueChangedSpy.count(), 1);
}

void DateTimeDecoratorTests::
update_whenNotPresentInJson_updatesValueToDefault() {
  Entity parent_entity;
  DateTimeDecorator decorator(&parent_entity, "Test Key", "Test Label", testDate);
  QSignalSpy valueChangedSpy(&decorator, &DateTimeDecorator::valueChanged);

  QCOMPARE(decorator.value(), testDate);

  QJsonObject jsonObject;
  jsonObject.insert("Key 1", "Value 1");
  jsonObject.insert("Key 2", QDateTime(QDate(2016, 4, 18), QTime(10, 37, 14)).toString(Qt::ISODate));
  jsonObject.insert("Key 3", 3);

  decorator.update(jsonObject);

  QCOMPARE(decorator.value(), testDate);
  QCOMPARE(valueChangedSpy.count(), 0);
}

void DateTimeDecoratorTests::
toIso8601String_whenDefaultValue_returnsString() {
  DateTimeDecorator decorator;

  QCOMPARE(decorator.to_iso8601(), QString(""));
}

void DateTimeDecoratorTests::
toIso8601String_whenValueSet_returnsString() {
  DateTimeDecorator decorator;
  decorator.set_value(testDate);

  QCOMPARE(decorator.to_iso8601(), QString("2017-08-19T16:40:32"));
}

void DateTimeDecoratorTests::
toPrettyDateString_whenDefaultValue_returnsString() {
  DateTimeDecorator decorator;

  QCOMPARE(decorator.to_pretty_date_string(), QString("null"));
}

void DateTimeDecoratorTests::
toPrettyDateString_whenValueSet_returnsString() {
  DateTimeDecorator decorator;
  decorator.set_value(testDate);

  QCOMPARE(decorator.to_pretty_date_string(), QString("19 Aug 2017"));
}

void DateTimeDecoratorTests::
toPrettyTimeString_whenDefaultValue_returnsString() {
  DateTimeDecorator decorator;

  QCOMPARE(decorator.to_pretty_time_string(), QString("null"));
}

void DateTimeDecoratorTests::
toPrettyTimeString_whenValueSet_returnsString() {
  DateTimeDecorator decorator;
  decorator.set_value(testDate);

  QCOMPARE(decorator.to_pretty_time_string(), QString("04:40 pm"));
}

void DateTimeDecoratorTests::
toPrettyString_whenDefaultValue_returnsString() {
  DateTimeDecorator decorator;

  QCOMPARE(decorator.to_pretty_string(), QString("null"));
}

void DateTimeDecoratorTests::
toPrettyString_whenValueSet_returnsString() {
  DateTimeDecorator decorator;
  decorator.set_value(testDate);

  QCOMPARE(decorator.to_pretty_string(), QString("Sat 19 Aug 2017 @ 16:40:32"));
}

}}
