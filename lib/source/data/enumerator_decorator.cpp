#include "enumerator_decorator.h"

namespace cm {
namespace data {

class EnumeratorDecorator::Implementation {
public:
  Implementation(EnumeratorDecorator* decorator,
                 int                  value,
                 const descriptor_t&  descriptor)
    : _decorator{ decorator}, _descriptor{ descriptor }, _value{ value }
  {

  }
  ~Implementation() { }

  EnumeratorDecorator* _decorator{ nullptr };
  descriptor_t         _descriptor;
  int                  _value;
};

EnumeratorDecorator::
EnumeratorDecorator(Entity*             parent,
                    const QString&      key,
                    const QString&      label,
                    const int&          value,
                    const descriptor_t& descriptor)
  : DataDecorator { parent, key, label }
{
  implementation.reset(new Implementation(this, value, descriptor));
}

EnumeratorDecorator::
~EnumeratorDecorator() {

}

int EnumeratorDecorator::
value() const {
  return implementation->_value;
}

EnumeratorDecorator &EnumeratorDecorator::
set_value(int value) {
  if (value != implementation->_value) {
    implementation->_value = value;
    emit valueChanged();
  }
  return *this;
}

QString EnumeratorDecorator::
value_description() const {
  QString output;
  auto it = implementation->_descriptor.find(implementation->_value);
  if (it != implementation->_descriptor.end()) {
    output = it.value();
  }
  return output;
}

EnumeratorDecorator::
operator int() const {
  return value();
}

QJsonValue EnumeratorDecorator::
to_json() const {
  return QJsonValue{ implementation->_value };
}

void EnumeratorDecorator::
update(const QJsonObject &object) {
  if (object.contains(key())) {
    set_value(object[key()].toInt());
  }
}

}
}

