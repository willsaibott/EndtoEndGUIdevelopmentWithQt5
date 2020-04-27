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

  if (object.contains("decorator")) {
    const auto& decorator { object.value("decorator").toObject() };
    for (const auto& entry : implementation->_data_decorators) {
      entry->update(decorator);
    }
  }

  if (object.contains("entity")) {
    const auto& entity { object.value("entity").toObject() };
    for (const auto& entry : implementation->_child_entities) {
      entry->update(entity);
    }
  }

  if (object.contains("collections")) {
    const auto& array { object.value("entity").toArray() };
    for (const auto& entry : implementation->_child_collections) {
      entry->update(array);
    }
  }
}

QJsonObject Entity::
to_json() const {
  QJsonObject output, entities, decorators, collections;

  for (const auto& entry : implementation->_data_decorators) {
    decorators.insert(entry->key(), entry->to_json());
  }

  for (const auto& entry : implementation->_child_entities) {
    entities.insert(entry->key(), entry->to_json());
  }

  for (const auto& entry : implementation->_child_collections) {
    QJsonArray array;
    for (const auto& entity: entry->base_entities()) {
      array.append(entity->to_json());
    }
    collections.insert(entry->key(), array);
  }

  output.insert("decorator",   decorators);
  output.insert("entity",      entities);
  output.insert("collections", collections);
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
