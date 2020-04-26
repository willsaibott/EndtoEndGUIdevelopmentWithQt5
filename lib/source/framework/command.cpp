#include "command.h"

namespace cm {
namespace framework {

class Command::Implementation {
public:
  Implementation(const QString&        icon_character,
                 const QString&        description,
                 std::function<bool()> can_execute)
    : icon_character{ icon_character },
      description{ description },
      can_execute{ can_execute }
  {

  }

  QString               icon_character;
  QString               description;
  std::function<bool()> can_execute;
};

Command::
Command(QObject*              parent,
        const QString&        icon_character,
        const QString&        description,
        std::function<bool()> can_execute)
  : QObject(parent)
{
  implementation.reset(
        new Implementation(icon_character, description, can_execute));
}

Command::
~Command() {

}

const QString& Command::
icon_character() const {
  return implementation->icon_character;
}

const QString& Command::
description() const {
  return implementation->description;
}

bool Command::
can_be_executed() const {
  return implementation->can_execute();
}

}
}
