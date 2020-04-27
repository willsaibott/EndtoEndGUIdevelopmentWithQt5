#include "datetime_decorator.h"
#include <QVariant>
#include <QLocale>

namespace cm {
namespace data {

class DateTimeDecorator::Implementation {
public:
  Implementation(DateTimeDecorator* decorator, const QDateTime& value)
    : _value{ value }, _decorator{ decorator }
  {

  }
  ~Implementation() {}

  QDateTime          _value;
  DateTimeDecorator* _decorator{ nullptr };
};


DateTimeDecorator::
DateTimeDecorator(Entity*          parent,
                  const QString&   key,
                  const QString&   label,
                  const QDateTime& value)
  : DataDecorator{ parent, key, label }
{
  implementation.reset(new Implementation(this, value));
}

DateTimeDecorator::
~DateTimeDecorator() {

}

const QDateTime &DateTimeDecorator::
value() const {
  return implementation->_value;
}

DateTimeDecorator &DateTimeDecorator::
set_value(const QDateTime &new_value) {
  if (new_value != implementation->_value) {
    implementation->_value = new_value;
    emit valueChanged();
  }
  return *this;
}

QString DateTimeDecorator::
to_iso8601() const {
  static QLocale locale{ QLocale::English };
  QString output;
  if (!implementation->_value.isNull()) {
    output = implementation->_value.toString(Qt::ISODate);
  }
  return output;
}

QString DateTimeDecorator::
to_pretty_date_string() const {
  static QLocale locale{ QLocale::English };
  QString output { "null" };
  if (!implementation->_value.isNull()) {
    output = locale.toString(implementation->_value, "d MMM yyyy");
  }
  return output;
}

QString DateTimeDecorator::
to_pretty_time_string() const {
  static QLocale locale{ QLocale::English };
  QString output { "null" };
  if (!implementation->_value.isNull()) {
    output = locale.toString(implementation->_value, "hh:mm ap");
  }
  return output;
}

QString DateTimeDecorator::
to_pretty_string() const {
  static QLocale locale{ QLocale::English };
  QString output { "null" };
  if (!implementation->_value.isNull()) {
    output = locale.toString(implementation->_value, "ddd d MMM yyyy @ HH:mm:ss");
  }
  return output;
}

QJsonValue DateTimeDecorator::
to_json() const {
  static QLocale locale{ QLocale::English };
  return QJsonValue{ implementation->_value.toString(Qt::ISODate) };
}

void DateTimeDecorator::
update(const QJsonObject &object) {
  if (object.contains(key())) {
    set_value(QDateTime::fromString(object[key()].toString(), Qt::ISODate));
  }
}

DateTimeDecorator::operator
QDateTime() const {
  return value();
}

}
}


