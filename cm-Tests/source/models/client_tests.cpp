#include "client_tests.h"

#include <QString>
#include <QtTest>

#include <QJsonArray>
#include <QJsonDocument>

#include <models/client.h>

using namespace cm::models;

namespace cm {
namespace models { // Structors

static ClientTests instance;

ClientTests::ClientTests()
  : TestSuite( "ClientTests" )
{
}

}

namespace models { // Tests

void ClientTests::
constructor_givenParent_setsParentAndDefaultProperties() {
  Client testClient(this);

  QCOMPARE(testClient.parent(), this);
  QCOMPARE(testClient.reference->value(), QString(""));
  QCOMPARE(testClient.name_field->value(), QString(""));

  verifyDefaultBillingAddress(testClient.billing_addr);
  verifyDefaultSupplyAddress(testClient.supply_addr);
  verifyDefaultAppointments(testClient._appointments->derived_entities());
  verifyDefaultContacts(testClient._contacts->derived_entities());
}

void ClientTests::
constructor_givenParentAndJsonObject_setsParentAndProperties() {
  Client testClient(this, QJsonDocument::fromJson(jsonByteArray).object());

  QCOMPARE(testClient.parent(), this);
  QCOMPARE(testClient.reference->value(), QString("CM0001"));
  QCOMPARE(testClient.name_field->value(), QString("Mr Test Testerson"));

  verifyBillingAddress(testClient.billing_addr);
  verifySupplyAddress(testClient.supply_addr);
  verifyAppointments(testClient._appointments->derived_entities());
  verifyContacts(testClient._contacts->derived_entities());
}

void ClientTests::
toJson_withDefaultProperties_constructsJson() {
  Client testClient(this);

  QJsonDocument jsonDoc(testClient.to_json());

  QVERIFY(jsonDoc.isObject());

  QJsonObject jsonObject = jsonDoc.object();

  QVERIFY(jsonObject.contains(Client::REFERENCE));
  QCOMPARE(jsonObject.value(Client::REFERENCE).toString(), QString(""));
  QVERIFY(jsonObject.contains(Client::NAME_FIELD));
  QCOMPARE(jsonObject.value(Client::NAME_FIELD).toString(), QString(""));

  verifyDefaultBillingAddress(jsonObject);
  verifyDefaultSupplyAddress(jsonObject);
  verifyDefaultAppointments(jsonObject);
  verifyDefaultContacts(jsonObject);
}

void ClientTests::
toJson_withSetProperties_constructsJson() {
  Client testClient(this, QJsonDocument::fromJson(jsonByteArray).object());

  QCOMPARE(testClient.reference->value(), QString("CM0001"));
  QCOMPARE(testClient.name_field->value(), QString("Mr Test Testerson"));

  verifyBillingAddress(testClient.billing_addr);
  verifySupplyAddress(testClient.supply_addr);
  verifyAppointments(testClient._appointments->derived_entities());
  verifyContacts(testClient._contacts->derived_entities());

  QJsonDocument jsonDoc(testClient.to_json());

  QVERIFY(jsonDoc.isObject());

  QJsonObject jsonObject = jsonDoc.object();

  QVERIFY(jsonObject.contains(Client::REFERENCE));
  QCOMPARE(jsonObject.value(Client::REFERENCE).toString(), QString("CM0001"));
  QVERIFY(jsonObject.contains(Client::NAME_FIELD));
  QCOMPARE(jsonObject.value(Client::NAME_FIELD).toString(), QString("Mr Test Testerson"));

  verifyBillingAddress(jsonObject);
  verifySupplyAddress(jsonObject);
  verifyAppointments(jsonObject);
  verifyContacts(jsonObject);
}

void ClientTests::
update_givenJsonObject_updatesProperties() {
  Client testClient(this);

  testClient.update(QJsonDocument::fromJson(jsonByteArray).object());

  QCOMPARE(testClient.reference->value(), QString("CM0001"));
  QCOMPARE(testClient.name_field->value(), QString("Mr Test Testerson"));

  verifyBillingAddress(testClient.billing_addr);
  verifySupplyAddress(testClient.supply_addr);
  verifyAppointments(testClient._appointments->derived_entities());
  verifyContacts(testClient._contacts->derived_entities());
}

void ClientTests::
update_givenEmptyJsonObject_updatesPropertiesToDefaults() {
  Client testClient(this, QJsonDocument::fromJson(jsonByteArray).object());

  QCOMPARE(testClient.reference->value(), QString("CM0001"));
  QCOMPARE(testClient.name_field->value(), QString("Mr Test Testerson"));

  verifyBillingAddress(testClient.billing_addr);
  verifySupplyAddress(testClient.supply_addr);
  verifyAppointments(testClient._appointments->derived_entities());
  verifyContacts(testClient._contacts->derived_entities());

  testClient.update(QJsonObject());

  QCOMPARE(testClient.reference->value(), QString("CM0001"));
  QCOMPARE(testClient.name_field->value(), QString("Mr Test Testerson"));

  verifyBillingAddress(testClient.billing_addr);
  verifySupplyAddress(testClient.supply_addr);
  verifyAppointments(testClient._appointments->derived_entities());
  verifyContacts(testClient._contacts->derived_entities());
}

void ClientTests::
id_givenPrimaryKeyWithNoValue_returnsUuid() {
  Client testClient(this);
  auto id = testClient.id();
  // Using individual character checks
  QCOMPARE(testClient.id().left(1), QString("{"));
  QCOMPARE(testClient.id().mid(9, 1), QString("-"));
  QCOMPARE(testClient.id().mid(14, 1), QString("-"));
  QCOMPARE(testClient.id().mid(19, 1), QString("-"));
  QCOMPARE(testClient.id().mid(24, 1), QString("-"));
  QCOMPARE(testClient.id().right(1), QString("}"));
  // Using regular expression pattern matching
  QVERIFY(QRegularExpression("\\{.{8}-(.{4})-(.{4})-(.{4})-(.{12})\\}")
             .match(testClient.id())
             .hasMatch());
}

void ClientTests::
id_givenPrimaryKeyWithValue_returnsPrimaryKey() {
  Client testClient(this, QJsonDocument::fromJson(jsonByteArray).object());
  QCOMPARE(testClient.reference->value(), QString("CM0001"));
  QCOMPARE(testClient.id(), testClient.reference->value());
}

void ClientTests::
verifyBillingAddress(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::BILLING_ADDRESS));
  QJsonObject billing_addr = jsonObject.value(Client::BILLING_ADDRESS).toObject();

  QVERIFY(billing_addr.contains(Address::BUILDING));
  QCOMPARE(billing_addr.value(Address::BUILDING).toString(), QString("Billing Building"));
  QVERIFY(billing_addr.contains(Address::STREET));
  QCOMPARE(billing_addr.value(Address::STREET).toString(), QString("Billing Street"));
  QVERIFY(billing_addr.contains(Address::CITY));
  QCOMPARE(billing_addr.value(Address::CITY).toString(), QString("Billing City"));
  QVERIFY(billing_addr.contains(Address::POSTCODE));
  QCOMPARE(billing_addr.value(Address::POSTCODE).toString(), QString("Billing Postcode"));
}

void ClientTests::
verifyDefaultBillingAddress(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::BILLING_ADDRESS));
  QJsonObject billing_addr = jsonObject.value(Client::BILLING_ADDRESS).toObject();

  QVERIFY(billing_addr.contains(Address::BUILDING));
  QCOMPARE(billing_addr.value(Address::BUILDING).toString(), QString(""));
  QVERIFY(billing_addr.contains(Address::STREET));
  QCOMPARE(billing_addr.value(Address::STREET).toString(), QString(""));
  QVERIFY(billing_addr.contains(Address::CITY));
  QCOMPARE(billing_addr.value(Address::CITY).toString(), QString(""));
  QVERIFY(billing_addr.contains(Address::POSTCODE));
  QCOMPARE(billing_addr.value(Address::POSTCODE).toString(), QString(""));
}

void ClientTests::
verifyBillingAddress(Address* address) {
  QVERIFY(address != nullptr);

  QCOMPARE(address->building->value(), QString("Billing Building"));
  QCOMPARE(address->street->value(), QString("Billing Street"));
  QCOMPARE(address->city->value(), QString("Billing City"));
  QCOMPARE(address->postcode->value(), QString("Billing Postcode"));
}

void ClientTests::
verifyDefaultBillingAddress(Address* address) {
  QVERIFY(address != nullptr);

  QCOMPARE(address->building->value(), QString(""));
  QCOMPARE(address->street->value(), QString(""));
  QCOMPARE(address->city->value(), QString(""));
  QCOMPARE(address->postcode->value(), QString(""));
}

void ClientTests::
verifySupplyAddress(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::SUPPLY_ADDRESS));
  QJsonObject billing_addr = jsonObject.value(Client::SUPPLY_ADDRESS).toObject();

  QVERIFY(billing_addr.contains(Address::BUILDING));
  QCOMPARE(billing_addr.value(Address::BUILDING).toString(), QString("Supply Building"));
  QVERIFY(billing_addr.contains(Address::STREET));
  QCOMPARE(billing_addr.value(Address::STREET).toString(), QString("Supply Street"));
  QVERIFY(billing_addr.contains(Address::CITY));
  QCOMPARE(billing_addr.value(Address::CITY).toString(), QString("Supply City"));
  QVERIFY(billing_addr.contains(Address::POSTCODE));
  QCOMPARE(billing_addr.value(Address::POSTCODE).toString(), QString("Supply Postcode"));
}

void ClientTests::
verifyDefaultSupplyAddress(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::SUPPLY_ADDRESS));
  QJsonObject billing_addr = jsonObject.value(Client::SUPPLY_ADDRESS).toObject();

  QVERIFY(billing_addr.contains(Address::BUILDING));
  QCOMPARE(billing_addr.value(Address::BUILDING).toString(), QString(""));
  QVERIFY(billing_addr.contains(Address::STREET));
  QCOMPARE(billing_addr.value(Address::STREET).toString(), QString(""));
  QVERIFY(billing_addr.contains(Address::CITY));
  QCOMPARE(billing_addr.value(Address::CITY).toString(), QString(""));
  QVERIFY(billing_addr.contains(Address::POSTCODE));
  QCOMPARE(billing_addr.value(Address::POSTCODE).toString(), QString(""));
}

void ClientTests::
verifySupplyAddress(Address* address) {
  QVERIFY(address != nullptr);

  QCOMPARE(address->building->value(), QString("Supply Building"));
  QCOMPARE(address->street->value(), QString("Supply Street"));
  QCOMPARE(address->city->value(), QString("Supply City"));
  QCOMPARE(address->postcode->value(), QString("Supply Postcode"));
}

void ClientTests::
verifyDefaultSupplyAddress(Address* address) {
  QVERIFY(address != nullptr);

  QCOMPARE(address->building->value(), QString(""));
  QCOMPARE(address->street->value(), QString(""));
  QCOMPARE(address->city->value(), QString(""));
  QCOMPARE(address->postcode->value(), QString(""));
}

void ClientTests::
verifyAppointments(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::APPOINTMENTS));
  QJsonArray appointments = jsonObject.value(Client::APPOINTMENTS).toArray();

  QCOMPARE(appointments.size(), 2);
  QVERIFY(appointments.at(0).isObject());
  QVERIFY(appointments.at(1).isObject());

  QJsonObject appointment1 = (appointments.at(0).toObject());
  QVERIFY(appointment1.contains(Appointment::START_AT));
  QCOMPARE(appointment1.value(Appointment::START_AT).toString(), QString("2017-08-20T12:45:00"));
  QVERIFY(appointment1.contains(Appointment::END_AT));
  QCOMPARE(appointment1.value(Appointment::END_AT).toString(), QString("2017-08-20T13:00:00"));
  QVERIFY(appointment1.contains(Appointment::NOTES));
  QCOMPARE(appointment1.value(Appointment::NOTES).toString(), QString("Test appointment 1"));

  QJsonObject appointment2 = (appointments.at(1).toObject());
  QVERIFY(appointment2.contains(Appointment::START_AT));
  QCOMPARE(appointment2.value(Appointment::START_AT).toString(), QString("2017-08-21T10:30:00"));
  QVERIFY(appointment2.contains(Appointment::END_AT));
  QCOMPARE(appointment2.value(Appointment::END_AT).toString(), QString("2017-08-21T11:30:00"));
  QVERIFY(appointment2.contains(Appointment::NOTES));
  QCOMPARE(appointment2.value(Appointment::NOTES).toString(), QString("Test appointment 2"));
}

void ClientTests::
verifyDefaultAppointments(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::APPOINTMENTS));
  QJsonArray appointments = jsonObject.value(Client::APPOINTMENTS).toArray();

  QCOMPARE(appointments.size(), 0);
}

void ClientTests::
verifyAppointments(const QList<Appointment*>& appointments) {
  QCOMPARE(appointments.size(), 2);

  QCOMPARE(appointments.size(), 2);
  QCOMPARE(appointments.at(0)->start_at->value(), QDateTime(QDate(2017, 8, 20), QTime(12, 45)));
  QCOMPARE(appointments.at(0)->end_at->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
  QCOMPARE(appointments.at(0)->notes->value(), QString("Test appointment 1"));
  QCOMPARE(appointments.at(1)->start_at->value(), QDateTime(QDate(2017, 8, 21), QTime(10, 30)));
  QCOMPARE(appointments.at(1)->end_at->value(),QDateTime(QDate(2017, 8, 21), QTime(11, 30)));
  QCOMPARE(appointments.at(1)->notes->value(), QString("Test appointment 2"));
}

void ClientTests::
verifyDefaultAppointments(const QList<Appointment*>& appointments) {
  QCOMPARE(appointments.size(), 0);
}

void ClientTests::
verifyContacts(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::CONTACTS));
  QJsonArray contacts = jsonObject.value(Client::CONTACTS).toArray();

  QCOMPARE(contacts.size(), 2);
  QVERIFY(contacts.at(0).isObject());
  QVERIFY(contacts.at(1).isObject());

  QJsonObject contact1 = (contacts.at(0).toObject());
  QVERIFY(contact1.contains(Client::SUPPLY_ADDRESS));
  QCOMPARE(contact1.value(Client::SUPPLY_ADDRESS).toString(), QString("email@test.com"));
  QVERIFY(contact1.contains(Contact::CONTACT_TYPE));
  QCOMPARE(contact1.value(Contact::CONTACT_TYPE).toInt(), static_cast<int>(Contact::contact_type_t::Email));

  QJsonObject contact2 = (contacts.at(1).toObject());
  QVERIFY(contact2.contains(Client::SUPPLY_ADDRESS));
  QCOMPARE(contact2.value(Client::SUPPLY_ADDRESS).toString(), QString("012345678"));
  QVERIFY(contact2.contains(Contact::CONTACT_TYPE));
  QCOMPARE(contact2.value(Contact::CONTACT_TYPE).toInt(), static_cast<int>(Contact::contact_type_t::Telephone));
}

void ClientTests::
verifyDefaultContacts(const QJsonObject& jsonObject) {
  QVERIFY(jsonObject.contains(Client::CONTACTS));
  QJsonArray contacts = jsonObject.value(Client::CONTACTS).toArray();

  QCOMPARE(contacts.size(), 0);
}

void ClientTests::
verifyContacts(const QList<Contact*>& contacts) {
  QCOMPARE(contacts.size(), 2);

  QCOMPARE(contacts.size(), 2);
  QCOMPARE(contacts.at(0)->address->value(), QString("email@test.com"));
  QCOMPARE(contacts.at(0)->contact_type->value(), static_cast<int>(Contact::contact_type_t::Email));
  QCOMPARE(contacts.at(1)->address->value(), QString("012345678"));
  QCOMPARE(contacts.at(1)->contact_type->value(), static_cast<int>(Contact::contact_type_t::Telephone));
}

void ClientTests::
verifyDefaultContacts(const QList<Contact*>& contacts) {
  QCOMPARE(contacts.size(), 0);
}

}
}
