#include "address.h"

namespace cm {
namespace models {

using namespace data;

const QString Address::NAME{ "address" };
const QString Address::POSTCODE{ "postcode" };
const QString Address::CITY{ "city" };
const QString Address::STREET{ "street" };
const QString Address::BUILDING{ "building" };
const QString Address::POSTCODE_LABEL{ "Postcode" };
const QString Address::CITY_LABEL{ "City" };
const QString Address::STREET_LABEL{ "Street" };
const QString Address::BUILDING_LABEL{ "Building" };

Address::
Address(QObject *parent) : Entity(parent, NAME) {
  building = static_cast<StringDecorator*>(
               add_data_item(
                 new StringDecorator(this, BUILDING, BUILDING_LABEL)));
  street   = static_cast<StringDecorator*>(
               add_data_item(
                 new StringDecorator(this, STREET, STREET_LABEL)));
  city     = static_cast<StringDecorator*>(
               add_data_item(
                 new StringDecorator(this, CITY, CITY_LABEL)));
  postcode = static_cast<StringDecorator*>(
               add_data_item(
                 new StringDecorator(this, POSTCODE, POSTCODE_LABEL)));
}

Address::
Address(QObject *parent, const QJsonObject &json) : Address{ parent } {
  update(json);
}

QString Address::
full_address() const {
  return building->value() + "\n" +
         street->value() + "\n" +
         city->value() + "\n" +
         postcode->value();
}

}
}
