#include "master_controller.h"

namespace cm {
namespace controllers {

class MasterController::Implementation {
public:
  MasterController*     _master_controller{ nullptr };
  NavigationController* _navigation_controller{ nullptr };
  CommandController*    _command_controller{ nullptr };
  QString               _welcome_message{ "This is MasterController to Major Tom" };

  Implementation(MasterController* master_controller)
    : _master_controller{ master_controller }
  {
    _navigation_controller = new NavigationController(master_controller);
    _command_controller    = new CommandController(master_controller);
  }
};

NavigationController* MasterController::
navigation_controller() {
  return implementation->_navigation_controller;
}

CommandController* MasterController::
command_controller() const {
  return implementation->_command_controller;
}

const QString& MasterController::
welcome_message() const {
  return implementation->_welcome_message;
}


MasterController::
MasterController(QObject *parent) : QObject(parent) {
  implementation.reset(new MasterController::Implementation(this));
}

MasterController::
~MasterController() {

}

}
}
