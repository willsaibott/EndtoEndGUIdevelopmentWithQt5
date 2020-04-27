#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QScopedPointer>

#include <lib_global.h>

namespace cm {
namespace data {

class Entity;

class CMLIBSHARED_EXPORT DataDecorator : public QObject
{
  Q_OBJECT
  Q_PROPERTY( QString ui_label READ label CONSTANT )

public:
  explicit DataDecorator(Entity *parent       = nullptr,
                         const QString& key   = "SomeItemKey",
                         const QString& label = "");

  virtual ~DataDecorator();

  const QString& key() const;
  const QString& label() const;
  Entity* parent_entity();

  virtual QJsonValue to_json() const = 0;
  virtual void update(const QJsonObject& object) = 0;

private:

  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}

