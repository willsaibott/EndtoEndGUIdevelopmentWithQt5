#include "appointment.h"

namespace cm {
namespace models {
using namespace data;

const QString Appointment::NAME {"appointment"};
const QString Appointment::START_AT{ "start_at" };
const QString Appointment::END_AT{ "end_at" };
const QString Appointment::NOTES{ "notes" };
const QString Appointment::LABEL{ "Appointment "};
const QString Appointment::START_AT_LABEL{ "Start" };
const QString Appointment::END_AT_LABEL{ "End" };
const QString Appointment::NOTES_LABEL{ "Notes" };

Appointment::
Appointment(QObject *parent) : Entity{ parent, NAME }
{
  start_at = static_cast<DateTimeDecorator*>(
               add_data_item(
                 new DateTimeDecorator(this, START_AT, START_AT_LABEL)));
  end_at   = static_cast<DateTimeDecorator*>(
               add_data_item(
                 new DateTimeDecorator(this, END_AT, END_AT_LABEL))
               );
  notes    = static_cast<StringDecorator*>(
               add_data_item(
                 new StringDecorator(this, NOTES, NOTES_LABEL)));
}

Appointment::
Appointment(QObject *parent, const QJsonObject &json)
  : Appointment{ parent }
{
  update(json);
}

}
}
