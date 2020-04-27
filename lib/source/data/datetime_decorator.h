#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QScopedPointer>
#include <QDateTime>

#include <lib_global.h>
#include <data/data_decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT DateTimeDecorator : public DataDecorator
{
  Q_OBJECT
  Q_PROPERTY( QDateTime ui_value READ value WRITE set_value NOTIFY valueChanged)
  Q_PROPERTY( QString ui_iso8601_string READ to_iso8601 NOTIFY valueChanged)
  Q_PROPERTY( QString ui_pretty_date_string READ to_pretty_date_string NOTIFY valueChanged)
  Q_PROPERTY( QString ui_pretty_time_string READ to_pretty_time_string NOTIFY valueChanged)
  Q_PROPERTY( QString ui_pretty_string READ to_pretty_string NOTIFY valueChanged)

public:
  explicit DateTimeDecorator(Entity *parent         = nullptr,
                             const QString& key     = "SomeRandomKey",
                             const QString& label   = "",
                             const QDateTime& value = {});
  ~DateTimeDecorator();

  const QDateTime& value() const;
  operator QDateTime() const;
  DateTimeDecorator& set_value(const QDateTime& new_value);

  QString to_iso8601() const;
  QString to_pretty_date_string() const;
  QString to_pretty_time_string() const;
  QString to_pretty_string() const;

  virtual QJsonValue to_json() const override;
  virtual void update(const QJsonObject &object) override;

signals:
  void valueChanged();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}


