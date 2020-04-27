#include "client.h"
#include <models/address.h>

namespace cm {
namespace models {
using namespace data;

QString Client::NAME { "client" };
QString Client::REFERENCE { "reference" };
QString Client::NAME_FIELD { "name" };
QString Client::SUPPLY_ADDRESS { "supply_address" };
QString Client::BILLING_ADDRESS { "billing_address" };
QString Client::LABEL { "Client" };
QString Client::REFERENCE_LABEL { "Reference" };
QString Client::NAME_FIELD_LABEL { "Name" };
QString Client::SUPPLY_ADDRESS_LABEL { "Address" };
QString Client::BILLING_ADDRESS_LABEL { "Billing Address" };
QString Client::APPOINTMENTS { "appointments" };
QString Client::APPOINTMENTS_LABEL { "Appointments" };
QString Client::CONTACTS { "contacts" };
QString Client::CONTACTS_LABEL { "Contacts" };

Client::
Client(QObject *parent) : Entity{ parent, NAME } {
  reference  = static_cast<StringDecorator*>(
                 add_data_item(
                   new StringDecorator(this, REFERENCE, REFERENCE_LABEL)));
  name_field = static_cast<StringDecorator*>(
                 add_data_item(
                   new StringDecorator(this, NAME_FIELD, NAME_FIELD_LABEL)));
  supply_addr = static_cast<Address*>(
                  add_child(new Address(this), SUPPLY_ADDRESS));
  billing_addr = static_cast<Address*>(
                   add_child(new Address(this), BILLING_ADDRESS));
  _appointments = static_cast<EntityCollection<Appointment>*>(
                    add_child_collection(
                      new EntityCollection<Appointment>(this, APPOINTMENTS)
                    ));
  _contacts = static_cast<EntityCollection<Contact>*>(
                add_child_collection(
                  new EntityCollection<Contact>(this, CONTACTS)));
}

Client::
Client(QObject *parent, const QJsonObject &json)
  : Client{ parent }
{
  update(json);
}

QQmlListProperty<Appointment> Client::
appointments() {
  return QQmlListProperty<Appointment>(this, _appointments->derived_entities());
}

QQmlListProperty<Contact> Client::
contacts() {
  return QQmlListProperty<Contact>(this, _contacts->derived_entities());
}



}
}

