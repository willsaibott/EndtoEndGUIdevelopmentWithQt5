#pragma once

#include <QObject>

#include <lib_global.h>

#include <data/datetime_decorator.h>
#include <data/string_decorator.h>
#include <data/entity.h>

namespace cm {
namespace models {

class CMLIBSHARED_EXPORT Appointment : public data::Entity {
  Q_OBJECT
  Q_PROPERTY(cm::data::DateTimeDecorator* ui_start_at MEMBER start_at CONSTANT)
  Q_PROPERTY(cm::data::DateTimeDecorator* ui_end_at   MEMBER end_at   CONSTANT)
  Q_PROPERTY(cm::data::StringDecorator*   ui_notes    MEMBER notes    CONSTANT)

public:

  explicit Appointment(QObject *parent = nullptr);
  Appointment(QObject* parent, const QJsonObject& json);

  data::DateTimeDecorator* start_at { nullptr };
  data::DateTimeDecorator* end_at { nullptr };
  data::StringDecorator*   notes { nullptr };

  static const QString NAME;
  static const QString START_AT;
  static const QString END_AT;
  static const QString NOTES;
  static const QString LABEL;
  static const QString START_AT_LABEL;
  static const QString END_AT_LABEL;
  static const QString NOTES_LABEL;

signals:

public slots:
};

}
}

