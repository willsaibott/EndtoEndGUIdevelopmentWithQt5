#include "integer_decorator.h"

namespace cm {
namespace data {

class IntegerDecorator::Implementation {
public:
  Implementation(IntegerDecorator* decorator, int value)
    : _decorator{ decorator }, _value{ value }
  {

  }

  IntegerDecorator* _decorator;
  int               _value;
};

IntegerDecorator::
IntegerDecorator(Entity*        parent,
                 const QString& key,
                 const QString& label,
                 const int&     value)
  : DataDecorator (parent, key, label)
{
  implementation.reset(new Implementation(this, value));
}

IntegerDecorator::
~IntegerDecorator() {

}

int IntegerDecorator::
value() const {
  return implementation->_value;
}

IntegerDecorator::operator
int() const {
  return value();
}

IntegerDecorator &IntegerDecorator::
set_value(int new_value) {
  if (new_value != implementation->_value) {
    implementation->_value = new_value;
    emit valueChanged();
  }
  return *this;
}

QJsonValue IntegerDecorator::
to_json() const {
  return QJsonValue(implementation->_value);
}

void IntegerDecorator::
update(const QJsonObject &object) {
  if (object.contains(key())) {
    set_value(object[key()].toInt());
  }
}

}
}
