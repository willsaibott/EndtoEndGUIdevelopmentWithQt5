#pragma once

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QScopedPointer>

#include <lib_global.h>
#include <data/data_decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT IntegerDecorator : public DataDecorator
{
  Q_OBJECT
  Q_PROPERTY(int ui_value READ value WRITE set_value NOTIFY valueChanged)

public:
  explicit IntegerDecorator(Entity *parent       = nullptr,
                            const QString& key   = "SomeRandomKey",
                            const QString& label = "",
                            const int& value     = 0);
  ~IntegerDecorator() override;

  int value() const;
  operator int() const;
  IntegerDecorator& set_value(int new_value);

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

