#pragma once
#include <functional>

#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QtQml/QQmlListProperty>

#include <lib_global.h>
#include <framework/command.h>
#include <controllers/idatabase_controller.h>
#include <controllers/navigation_controller.h>
#include <network/inetwork_access.h>
#include <network/iweb_request.h>
#include <models/client.h>
#include <models/client_search.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT CommandController : public QObject
{
  Q_OBJECT
  Q_PROPERTY(
      QQmlListProperty<cm::framework::Command>
      ui_create_client_view_context_commands READ
      create_client_view_context_commands CONSTANT
  )
  Q_PROPERTY(
      QQmlListProperty<cm::framework::Command>
      ui_search_client_view_context_commands READ
      search_client_view_context_commands CONSTANT
  )
  Q_PROPERTY(
      QQmlListProperty<cm::framework::Command>
      ui_edit_client_view_context_commands READ
      edit_client_view_context_commands CONSTANT
  )
  Q_PROPERTY(
      QQmlListProperty<cm::framework::Command>
      ui_rss_view_context_commands READ
      rss_view_context_commands CONSTANT
  )

public:
  explicit CommandController(
      QObject*                         parent         = nullptr,
      IDatabaseController*             db_controller  = nullptr,
      NavigationController*            nav_controller = nullptr,
      network::INetworkAccessManager*  net_manager    = nullptr,
      network::IWebRequest*            web_request    = nullptr,
      models::Client*                  new_client     = nullptr,
      models::ClientSearch*            client_search  = nullptr);
  ~CommandController();

  QQmlListProperty<cm::framework::Command>
  create_client_view_context_commands();

  QQmlListProperty<cm::framework::Command>
  search_client_view_context_commands();

  QQmlListProperty<cm::framework::Command>
  edit_client_view_context_commands();

  QQmlListProperty<cm::framework::Command>
  rss_view_context_commands();

public slots:
  void set_selected_client(cm::models::Client* selected_client);
  void onCreateClientSaveExecuted();
  void onSearchTriggered();
  void onEditClientSaveExecuted();
  void onEditClientDeleteExecuted();
  void onRssViewRefreshTriggered();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}

