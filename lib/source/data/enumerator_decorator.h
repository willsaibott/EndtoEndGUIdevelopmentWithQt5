#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QScopedPointer>
#include <QMap>

#include <lib_global.h>
#include <data/data_decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT EnumeratorDecorator : public DataDecorator
{
  Q_OBJECT
  Q_PROPERTY( int ui_value READ value WRITE set_value NOTIFY valueChanged )
  Q_PROPERTY( QString ui_value_description READ value_description NOTIFY valueChanged )

public:
  using descriptor_t = QMap<int, QString>;

  EnumeratorDecorator(Entity* parent                 = nullptr,
                      const QString& key             = "SomeItemKey",
                      const QString& label           = "",
                      const int&     value           = 0,
                      const descriptor_t& descriptor = {});
  ~EnumeratorDecorator();

  int value() const;
  operator int() const;
  EnumeratorDecorator& set_value(int value);
  QString value_description() const;

  // DataDecorator interface
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

