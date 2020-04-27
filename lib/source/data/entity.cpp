#include "entity.h"

#include <QJsonArray>

namespace cm {
namespace data {

class Entity::Implementation {
public:
  Implementation(Entity* entity, const QString& key)
    : _entity{ entity }, _key{ key }
  {

  }

  Entity*                              _entity{ nullptr };
  QString                              _key;
  QMap<QString, Entity*>               _child_entities;
  QMap<QString, DataDecorator*>        _data_decorators;
  QMap<QString, EntityCollectionBase*> _child_collections;
};

Entity::
Entity(QObject *parent, const QString &key)
  : QObject (parent)
{
  implementation.reset(new Implementation(this, key));
}

Entity::
Entity(QObject *parent, const QString &key, const QJsonObject object)
  : Entity{ parent, key }
{
  update(object);
}

Entity::
~Entity() {

}

const QString &Entity::
key() const {
  return implementation->_key;
}

void Entity::
update(const QJsonObject &object) {

  for (const auto& entry : implementation->_data_decorators) {
    entry->update(object);
  }

  for (const auto& key : implementation->_child_entities.keys()) {
    if (object.contains(key)) {
      implementation->_child_entities.value(key)
                    ->update(object.value(key).toObject());
    }
  }

  for (const auto& key : implementation->_child_collections.keys()) {
    if (object.contains(key)) {
      implementation->_child_collections.value(key)
                    ->update(object.value(key).toArray());
    }
  }
}

QJsonObject Entity::
to_json() const {
  QJsonObject output;

  for (const auto& key : implementation->_data_decorators.keys()) {
    const auto& entry { implementation->_data_decorators.value(key) };
    output.insert(key, entry->to_json());
  }

  for (const auto& key : implementation->_child_entities.keys()) {
    const auto& entry { implementation->_child_entities.value(key) };
    output.insert(key, entry->to_json());
  }

  for (const auto& key : implementation->_child_collections.keys()) {
    const auto& entry { implementation->_child_collections.value(key) };
    QJsonArray array;
    for (const auto& entity: entry->base_entities()) {
      array.append(entity->to_json());
    }
    output.insert(key, array);
  }
  return output;
}

Entity *Entity::
add_child(Entity *entity, const QString &key) {
  auto& children{ implementation->_child_entities };
  if (!children.count(key)) {
    children[key] = entity;
    emit childEntitiesChanged();
  }
  return entity;
}

DataDecorator *Entity::
add_data_item(DataDecorator *decorator) {
  auto& data_items{ implementation->_data_decorators };
  const auto&key { decorator->key() };
  if (!data_items.contains(key)) {
    data_items[key] = decorator;
  }
  return decorator;
}

EntityCollectionBase *Entity::
add_child_collection(EntityCollectionBase *collection) {
  auto& collections{ implementation->_child_collections };
  const auto& key{ collection->key() };
  if (!collections.contains(key)) {
    collections[key] = collection;
    emit childCollectionsChanged(key);
  }
  return collection;
}

}
}
