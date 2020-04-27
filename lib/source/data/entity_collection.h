#pragma once

#include <QObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QVector>
#include <QList>

#include <lib_global.h>

namespace cm {
namespace data {
  class Entity;

  class CMLIBSHARED_EXPORT EntityCollectionObject : public QObject {
    Q_OBJECT

  public:
    EntityCollectionObject(QObject* parent = nullptr) : QObject{ parent } {}
    virtual ~EntityCollectionObject() {}

  signals:
    void collectionChanged();
  };


  class EntityCollectionBase : public EntityCollectionObject {
    Q_OBJECT
  public:
    EntityCollectionBase(QObject*       parent,
                         const QString& key = "SomeCollectionKey")
      : EntityCollectionObject{ parent },
        _key{ key }

    {

    }

    virtual
    ~EntityCollectionBase() {}

    const QString& key() const {
      return _key;
    }

    virtual void clear()                        = 0;
    virtual void update(const QJsonArray& json) = 0;
    virtual QVector<Entity*> base_entities()    = 0;

    template<class T>
    QList<T*>& derived_entities();

    template<class T>
    T* add_entity(T* entity);

  private:
    QString _key;

  };


  template <typename T>
  class EntityCollection : public EntityCollectionBase {
  public:
    EntityCollection(QObject*       parent = nullptr,
                     const QString& key = "SomeCollectionKey")
      : EntityCollectionBase(parent, key)
    { }

    ~ EntityCollection()
    { }

    void
    clear() override {
      for (auto entity : _collection) {
        entity->deleteLater();
      }
      _collection.clear();
    }

    void
    update(const QJsonArray& json) override {
      clear();
      for (const QJsonValue& jvalue : json) {
        add_entity(new T(this, jvalue.toObject()));
      }
    }

    QVector<Entity*>
    base_entities() override {
      QVector<Entity*> output;
      output.reserve(_collection.size());
      for (T* entity : _collection) {
        output.push_back(entity);
      }
      return output;
    }

    QList<T*>&
    derived_entities() {
      return _collection;
    }

    T*
    add_entity(T* entity) {
      if (!_collection.contains(entity)) {
        _collection.append(entity);
        emit EntityCollectionObject::collectionChanged();
      }
      return entity;
    }

  private:
    QList<T*> _collection;
  };

  template <class T>
  QList<T*>& EntityCollectionBase::
  derived_entities() {
    return dynamic_cast<const EntityCollection<T>&>(*this).derived_entities();
  }

  template <class T>
  T* EntityCollectionBase::
  add_entity(T* entity) {
    return dynamic_cast<const EntityCollection<T>&>(*this).add_entity(entity);
  }

}
}
