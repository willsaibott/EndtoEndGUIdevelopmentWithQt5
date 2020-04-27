#include <data/data_decorator.h>
#include <data/entity.h>

namespace cm {
namespace data {

//class Entity : public QObject {} ;

class DataDecorator::Implementation {
public:
  Implementation(Entity* parent, const QString& key, const QString& label)
    : _parent_entity{ parent }, _key{ key }, _label{ label }
  {

  }

  Entity* _parent_entity{ nullptr };
  QString _key;
  QString _label;
};

DataDecorator::
DataDecorator(Entity *parent, const QString &key, const QString &label)
  : QObject (dynamic_cast<QObject*>(parent))
{
  implementation.reset(new Implementation(parent, key, label));
}

DataDecorator::
~DataDecorator() {

}

const QString &DataDecorator::
key() const {
  return implementation->_key;
}

const QString &DataDecorator::
label() const {
  return implementation->_label;
}

Entity *DataDecorator::
parent_entity() {
  return implementation->_parent_entity;
}

}
}
