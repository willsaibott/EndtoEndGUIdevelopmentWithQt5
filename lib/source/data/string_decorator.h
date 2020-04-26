#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QScopedPointer>
#include <QString>

#include <lib_global.h>
#include <data/data_decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT StringDecorator : public DataDecorator
{
  Q_OBJECT
  Q_PROPERTY( QString ui_value READ value WRITE set_value NOTIFY valueChanged)

public:
  explicit StringDecorator(Entity *parent       = nullptr,
                           const QString& key   = "SomeItemKey",
                           const QString& label = "",
                           const QString& value = "");
  ~StringDecorator() override;

  StringDecorator& set_value(const QString& value);
  const QString& value() const;
  virtual QJsonValue to_json() const override;
  virtual void update(const QJsonObject& object) override;

signals:

  void valueChanged();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}


