#pragma once

#include <QObject>

#include <lib_global.h>
#include <data/string_decorator.h>
#include <data/entity.h>

namespace cm {
namespace models {

class CMLIBSHARED_EXPORT Address : public data::Entity
{
  Q_OBJECT
  Q_PROPERTY(cm::data::StringDecorator* ui_building MEMBER building CONSTANT)
  Q_PROPERTY(cm::data::StringDecorator* ui_street MEMBER street CONSTANT)
  Q_PROPERTY(cm::data::StringDecorator* ui_city MEMBER city CONSTANT)
  Q_PROPERTY(cm::data::StringDecorator* ui_postcode MEMBER postcode CONSTANT)
  Q_PROPERTY(QString ui_full_address READ full_address CONSTANT)

public:
  explicit Address(QObject *parent = nullptr);
  Address(QObject* parent, const QJsonObject& json);
  data::StringDecorator* building{ nullptr };
  data::StringDecorator* street{ nullptr };
  data::StringDecorator* city{ nullptr };
  data::StringDecorator* postcode{ nullptr };

  QString full_address() const;

  static const QString NAME;
  static const QString BUILDING;
  static const QString STREET;
  static const QString CITY;
  static const QString POSTCODE;
  static const QString LABEL;
  static const QString BUILDING_LABEL;
  static const QString STREET_LABEL;
  static const QString CITY_LABEL;
  static const QString POSTCODE_LABEL;

signals:

public slots:
};

}
}
