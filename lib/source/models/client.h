#pragma once

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <lib_global.h>

#include <data/string_decorator.h>
#include <data/entity.h>
#include <data/entity_collection.h>

#include <models/address.h>
#include <models/appointment.h>
#include <models/contact.h>

namespace cm {
namespace models {

class CMLIBSHARED_EXPORT Client : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY( cm::data::StringDecorator*    ui_reference       MEMBER reference    CONSTANT )
  Q_PROPERTY( cm::data::StringDecorator*    ui_name            MEMBER name_field   CONSTANT )
  Q_PROPERTY( cm::models::Address*          ui_supply_address  MEMBER supply_addr  CONSTANT )
  Q_PROPERTY( cm::models::Address*          ui_billing_address MEMBER billing_addr CONSTANT )
  Q_PROPERTY( QQmlListProperty<Appointment> ui_appointments    READ   appointments NOTIFY appointmentsChanged)
  Q_PROPERTY( QQmlListProperty<Contact>     ui_contacts        READ   contacts     NOTIFY contactsChanged)

public:

  friend class ClientTests;
  explicit Client(QObject *parent = nullptr);
  Client(QObject* parent, const QJsonObject& json);

  data::StringDecorator* reference{ nullptr };
  data::StringDecorator* name_field{ nullptr };
  Address*               supply_addr{ nullptr };
  Address*               billing_addr{ nullptr };

  QQmlListProperty<Appointment> appointments();
  QQmlListProperty<Contact>     contacts();

  static QString NAME;
  static QString REFERENCE;
  static QString NAME_FIELD;
  static QString SUPPLY_ADDRESS;
  static QString BILLING_ADDRESS;
  static QString LABEL;
  static QString REFERENCE_LABEL;
  static QString NAME_FIELD_LABEL;
  static QString SUPPLY_ADDRESS_LABEL;
  static QString BILLING_ADDRESS_LABEL;
  static QString APPOINTMENTS;
  static QString APPOINTMENTS_LABEL;
  static QString CONTACTS;
  static QString CONTACTS_LABEL;

signals:
  void appointmentsChanged();
  void contactsChanged();

private:
  data::EntityCollection<Appointment>* _appointments;
  data::EntityCollection<Contact>*     _contacts;
};

}
}


