#include "integer_decorator_tests.h"

#include <QSignalSpy>
#include <data/entity.h>

namespace cm {
namespace data { // Instance
static IntegerDecoratorTests instance;

IntegerDecoratorTests::IntegerDecoratorTests()
    : TestSuite( "IntegerDecoratorTests" )
{
}
}
namespace data { // Tests
void IntegerDecoratorTests::
constructor_givenNoParameters_setsDefaultProperties() {
    IntegerDecorator decorator;
    QCOMPARE(decorator.parent_entity(), nullptr);
    QCOMPARE(decorator.key(), QString("SomeRandomKey"));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), 0);
}

void IntegerDecoratorTests::
constructor_givenParameters_setsProperties() {
    Entity parent_entity;
    IntegerDecorator decorator(&parent_entity, "Test Key", "Test Label", 99);
    QCOMPARE(decorator.parent_entity(), &parent_entity);
    QCOMPARE(decorator.key(), QString("Test Key"));
    QCOMPARE(decorator.label(), QString("Test Label"));
    QCOMPARE(decorator.value(), 99);
}

void IntegerDecoratorTests::
set_value_givenNewValue_updatesValueAndEmitsSignal() {
    IntegerDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator, &IntegerDecorator::valueChanged);
    QCOMPARE(decorator.value(), 0);
    decorator.set_value(99);
    QCOMPARE(decorator.value(), 99);
    QCOMPARE(valueChangedSpy.count(), 1);
}

void IntegerDecoratorTests::
set_value_givenSameValue_takesNoAction() {
    Entity parent_entity;
    IntegerDecorator decorator(&parent_entity, "Test Key", "Test Label", 99);
    QSignalSpy valueChangedSpy(&decorator, &IntegerDecorator::valueChanged);
    QCOMPARE(decorator.value(), 99);
    decorator.set_value(99);
    QCOMPARE(decorator.value(), 99);
    QCOMPARE(valueChangedSpy.count(), 0);
}

void IntegerDecoratorTests::
to_json_whenDefaultValue_returnsJson() {
    IntegerDecorator decorator;
    QCOMPARE(decorator.to_json(), QJsonValue(0));
}

void IntegerDecoratorTests::
to_json_whenValueSet_returnsJson() {
    IntegerDecorator decorator;
    decorator.set_value(99);
    QCOMPARE(decorator.to_json(), QJsonValue(99));
}

void IntegerDecoratorTests::
update_whenPresentInJson_updatesValue() {
    Entity parent_entity;
    IntegerDecorator decorator(&parent_entity, "Test Key", "Test Label", 99);
    QSignalSpy valueChangedSpy(&decorator, &IntegerDecorator::valueChanged);
    QCOMPARE(decorator.value(), 99);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Test Key", 123);
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), 123);
    QCOMPARE(valueChangedSpy.count(), 1);
}

void IntegerDecoratorTests::
update_whenNotPresentInJson_doNotSetAnyValue() {
    Entity parent_entity;
    IntegerDecorator decorator(&parent_entity,
                               "Test Key",
                               "Test Label",
                               99);
    QSignalSpy valueChangedSpy(&decorator, &IntegerDecorator::valueChanged);
    QCOMPARE(decorator.value(), 99);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1", "Value 1");
    jsonObject.insert("Key 2", 123);
    jsonObject.insert("Key 3", 3);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(), 99);
    QCOMPARE(valueChangedSpy.count(), 0);
}

}}
