#include "contact.h"

namespace cm {
namespace models {
using namespace data;

const QString Contact::NAME { "contact" };
const QString Contact::CONTACT_TYPE { "contact_type" };
const QString Contact::ADDRESS { "address" };
const QString Contact::TELEPHONE { "Telephone" };
const QString Contact::EMAIL { "Email" };
const QString Contact::FAX { "Fax" };
const QString Contact::UNKNOWN { "" };
const QString Contact::LABEL { "Contact" };
const QString Contact::CONTACT_TYPE_LABEL { "Contact Type" };
const QString Contact::ADDRESS_LABEL { "Address" };

EnumeratorDecorator::descriptor_t Contact::descriptor {
  { static_cast<int>(contact_type_t::Unknown),   UNKNOWN },
  { static_cast<int>(contact_type_t::Telephone), TELEPHONE },
  { static_cast<int>(contact_type_t::Email),     EMAIL },
  { static_cast<int>(contact_type_t::Fax),       FAX }
};

Contact::
Contact(QObject *parent) : Entity{ parent, NAME } {
  contact_type = static_cast<EnumeratorDecorator*>(
                   add_data_item(
                     new EnumeratorDecorator(this,
                                             CONTACT_TYPE,
                                             CONTACT_TYPE_LABEL,
                                             0,
                                             descriptor)));

  address      = static_cast<StringDecorator*>(
                   add_data_item(
                     new StringDecorator(this, ADDRESS, ADDRESS_LABEL)));
}

Contact::
Contact(QObject *parent, const QJsonObject &json)
  : Contact{ parent } {
  update(json);
}

}
}

