#include "command_controller.h"

#include <QList>
#include <QDebug>

namespace cm {
namespace controllers {

class CommandController::Implementation {
public:
  Implementation(CommandController* controller)
    : command_controller{ controller }
  {
    using cm::framework::Command;
    Command* create_client_save_command =
        new Command(controller, QChar(0xf0c7), "Save" );
    QObject::connect( create_client_save_command,
                      &Command::executed,
                      command_controller,
                      &CommandController::onCreateClientSaveExecuted);
    create_client_view_context_commands.push_back(create_client_save_command);
  }

  CommandController* command_controller{ nullptr };
  QList<cm::framework::Command*> create_client_view_context_commands{};
};

CommandController::
CommandController(QObject *parent) : QObject(parent) {
  implementation.reset(new Implementation(this));
}

CommandController::
~CommandController() {

}

QQmlListProperty<framework::Command> CommandController::
create_client_view_context_commands() {
  return QQmlListProperty<framework::Command>(
              this,
              implementation->create_client_view_context_commands);
}

void CommandController::
onCreateClientSaveExecuted() {
  qDebug() << "You executed the Save command!";
}

}
}
