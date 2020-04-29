#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QMap>

#include <lib_global.h>
#include <data/data_decorator.h>
#include <data/entity_collection.h>
#include <data/string_decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT Entity : public QObject
{
  Q_OBJECT

public:
  Entity(QObject* parent = nullptr, const QString&key = "SomeEntityKey");
  Entity(QObject* parent, const QString&key, const QJsonObject object);
  virtual ~Entity();

  const QString& key() const;
  QJsonObject to_json() const;
  void update(const QJsonObject& object);
  const QString id() const;

signals:
  void childEntitiesChanged();
  void dataDecoratorsChanged();
  void childCollectionsChanged(const QString& collection_key);


protected:
  Entity*
  add_child(Entity* entity, const QString& key);

  DataDecorator*
  add_data_item(DataDecorator* decorator);

  EntityCollectionBase*
  add_child_collection(EntityCollectionBase* collection);


  void
  set_primary_key(StringDecorator* primary_key);

  class Implementation;
  QScopedPointer<Implementation> implementation;
};



}
}
