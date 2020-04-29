#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <lib_global.h>

#include <controllers/navigation_controller.h>
#include <controllers/command_controller.h>
#include <controllers/database_controller.h>
#include <network/network_access_manager.h>

#include <models/client.h>
#include <models/client_search.h>
#include <rss/rss_channel.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT
  Q_PROPERTY( QString ui_welcome_message READ welcome_message CONSTANT )
  Q_PROPERTY( cm::controllers::NavigationController* ui_navigation_ctrl
              READ navigation_controller   CONSTANT )
  Q_PROPERTY( cm::controllers::CommandController*  ui_command_ctrl
              READ command_controller CONSTANT )
  Q_PROPERTY( cm::controllers::DatabaseController* ui_db_controller
              READ database_controller CONSTANT )
  Q_PROPERTY( cm::network::NetworkAccessManager* ui_net_manager
              READ network_access_manager CONSTANT )
  Q_PROPERTY( cm::models::Client*       ui_client        READ new_client    CONSTANT )
  Q_PROPERTY( cm::models::ClientSearch* ui_client_search READ client_search CONSTANT )
  Q_PROPERTY( cm::rss::RssChannel*      ui_rss_channel   READ rss_channel   NOTIFY   rssChannelChanged )

public:
  explicit MasterController(QObject *parent = nullptr);
  ~MasterController();

  const QString&
  welcome_message() const;

  NavigationController*
  navigation_controller();

  CommandController*
  command_controller();

  DatabaseController*
  database_controller();

  models::Client*
  new_client();

  models::ClientSearch*
  client_search();

  network::NetworkAccessManager*
  network_access_manager();

  rss::RssChannel*
  rss_channel();

signals:
  void rssChannelChanged();

public slots:

  void select_client(cm::models::Client* client);
  void on_rss_reply_received(int status_code, QByteArray body);

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}

