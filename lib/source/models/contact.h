#pragma once

#include <QObject>
#include <lib_global.h>

#include <data/enumerator_decorator.h>
#include <data/string_decorator.h>
#include <data/entity.h>

namespace cm {
namespace models {

class CMLIBSHARED_EXPORT Contact : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(cm::data::EnumeratorDecorator* ui_contact_type MEMBER contact_type CONSTANT)
  Q_PROPERTY(cm::data::StringDecorator*     ui_address      MEMBER address      CONSTANT)

public:

  enum class contact_type_t {
    Unknown = 0,
    Telephone,
    Email,
    Fax
  };

  explicit Contact(QObject *parent = nullptr);
  Contact(QObject* parent, const QJsonObject& json);

  data::EnumeratorDecorator* contact_type{ nullptr };
  data::StringDecorator*     address{ nullptr };

  static data::EnumeratorDecorator::descriptor_t descriptor;

  static const QString NAME;
  static const QString CONTACT_TYPE;
  static const QString ADDRESS;
  static const QString TELEPHONE;
  static const QString EMAIL;
  static const QString UNKNOWN;
  static const QString FAX;
  static const QString LABEL;
  static const QString CONTACT_TYPE_LABEL;
  static const QString ADDRESS_LABEL;

signals:

public slots:
};

}
}


