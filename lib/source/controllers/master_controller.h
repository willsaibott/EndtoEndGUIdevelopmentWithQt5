#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <lib_global.h>

#include <controllers/navigation_controller.h>
#include <controllers/command_controller.h>

#include <models/client.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT
  Q_PROPERTY( QString ui_welcome_message READ welcome_message CONSTANT )
  Q_PROPERTY( cm::controllers::NavigationController*
              ui_navigation_ctrl READ navigation_controller   CONSTANT )
  Q_PROPERTY( cm::controllers::CommandController*
              ui_command_ctrl READ command_controller         CONSTANT )
  Q_PROPERTY( cm::models::Client* ui_client READ new_client   CONSTANT )

public:
  explicit MasterController(QObject *parent = nullptr);
  ~MasterController();

  const QString&
  welcome_message() const;

  NavigationController*
  navigation_controller();

  CommandController*
  command_controller();

  models::Client*
  new_client();

signals:

public slots:

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}

