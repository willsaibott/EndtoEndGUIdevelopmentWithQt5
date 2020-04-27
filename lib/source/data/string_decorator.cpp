#include "string_decorator.h"
#include <QVariant>

namespace cm {
namespace data {

class StringDecorator::Implementation {
public:
  Implementation(StringDecorator* decorator, const QString& value)
    : _decorator{ decorator }, _value{ value }
  {

  }

  StringDecorator* _decorator{ nullptr };
  QString _value;
};

StringDecorator::
StringDecorator(Entity*        parent,
                const QString& key,
                const QString& label,
                const QString& value) :  DataDecorator{ parent, key, label }
{
  implementation.reset(new Implementation(this, value));
}

StringDecorator::
~StringDecorator() {

}

StringDecorator &StringDecorator::
set_value(const QString &value) {
  if (value != implementation->_value) {
    implementation->_value = value;
    emit valueChanged();
  }
  return *this;
}

const QString &StringDecorator::
value() const {
  return implementation->_value;
}

const QString &StringDecorator::
label() const {
  return  DataDecorator::label();
}

StringDecorator::operator
QString() const {
  return value();
}

QJsonValue StringDecorator::
to_json() const {
  return QJsonValue::fromVariant(QVariant{ implementation->_value });
}

void StringDecorator::
update(const QJsonObject &object) {
  if (object.contains(key())) {
    set_value(object[key()].toString());
  }
  else {
    set_value("");
  }
}

}
}
