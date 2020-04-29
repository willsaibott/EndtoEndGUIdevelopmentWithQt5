#include "command_controller.h"

#include <QList>
#include <QDebug>

namespace cm {
namespace controllers {

class CommandController::Implementation {
public:
  Implementation(CommandController*               controller,
                 IDatabaseController*             db_controller,
                 NavigationController*            nav_controller,
                 network::INetworkAccessManager*  net_manager,
                 network::IWebRequest*            rss_web_request,
                 models::Client*                  new_client,
                 models::ClientSearch*            search_client)
    : command_controller{ controller },
      database_controller{ db_controller },
      navigation_controller{ nav_controller },
      network_manager{ net_manager },
      rss_request{ rss_web_request },
      new_client{ new_client },
      search_client{ search_client }
  {
    using cm::framework::Command;
    Command* create_client_save_command =
        new Command(controller, QChar(0xf0c7), "Save");
    QObject::connect( create_client_save_command,
                      &Command::executed,
                      command_controller,
                      &CommandController::onCreateClientSaveExecuted );

    Command* search_client_command =
        new Command(controller, QChar(0xf002), "Search");
    QObject::connect( search_client_command,
                      &Command::executed,
                      command_controller,
                      &CommandController::onSearchTriggered );

    Command* edit_client_command =
        new Command(controller, QChar(0xf0c7), "Save");

    QObject::connect( edit_client_command,
                      &Command::executed,
                      command_controller,
                      &CommandController::onEditClientSaveExecuted );

    Command* delete_client_command =
        new Command(controller, QChar(0xf235), "Delete");

    QObject::connect( delete_client_command,
                      &Command::executed,
                      command_controller,
                      &CommandController::onEditClientDeleteExecuted );

    Command* rss_refresh_command =
        new Command(controller, QChar(0xf021), "Refresh");

    QObject::connect(rss_refresh_command,
                     &Command::executed,
                     command_controller,
                     &CommandController::onRssViewRefreshTriggered);

    create_client_view_context_commands.push_back(create_client_save_command);
    search_client_view_context_commands.push_back(search_client_command);
    edit_client_view_context_commands.push_back(edit_client_command);
    edit_client_view_context_commands.push_back(delete_client_command);
    rss_view_context_commands.push_back(rss_refresh_command);
  }

  CommandController*              command_controller{ nullptr };
  IDatabaseController*            database_controller{ nullptr };
  NavigationController*           navigation_controller{ nullptr };
  network::INetworkAccessManager* network_manager{ nullptr };
  network::IWebRequest*           rss_request{ nullptr };
  models::Client*                 new_client{ nullptr };
  models::Client*                 selected_client{ nullptr };
  models::ClientSearch*           search_client{ nullptr };
  QList<cm::framework::Command*>  create_client_view_context_commands{};
  QList<cm::framework::Command*>  search_client_view_context_commands{};
  QList<cm::framework::Command*>  edit_client_view_context_commands{};
  QList<cm::framework::Command*>  rss_view_context_commands{};
};

CommandController::
CommandController(QObject*                        parent,
                  IDatabaseController*            db_controller,
                  NavigationController*           nav_controller,
                  network::INetworkAccessManager* network_manager,
                  network::IWebRequest*           web_request,
                  models::Client*                 new_client,
                  models::ClientSearch*           client_search)
  : QObject(parent)
{
  implementation.reset(
        new Implementation(this,
                           db_controller,
                           nav_controller,
                           network_manager,
                           web_request,
                           new_client,
                           client_search));
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

QQmlListProperty<framework::Command> CommandController::
search_client_view_context_commands() {
  return QQmlListProperty<framework::Command>(
              this,
              implementation->search_client_view_context_commands);
}

QQmlListProperty<framework::Command> CommandController::
edit_client_view_context_commands() {
  return QQmlListProperty<framework::Command>(
              this,
              implementation->edit_client_view_context_commands);
}

QQmlListProperty<framework::Command> CommandController::
rss_view_context_commands() {
  return QQmlListProperty<framework::Command>(
            this, implementation->rss_view_context_commands);
}

void CommandController::
onCreateClientSaveExecuted() {
  auto& db_controller{ implementation->database_controller };
  auto& new_client{ implementation->new_client };
  qDebug() << "You executed the Save command!";
  bool ok {
    db_controller->createRow(models::Client::NAME,
                             new_client->id(),
                             new_client->to_json())
  };
  if (ok) {
    qDebug() << "New client saved successfully";
    implementation->search_client
                  ->search_text()
                  ->set_value(implementation->new_client->id());
    implementation->search_client->search();
    implementation->navigation_controller->showSearchView();
  }
  else {
    qDebug() << "ERROR: New client was not saved";
  }

}

void CommandController::
onSearchTriggered() {
  qDebug() << "You executed the Search command!";
  implementation->search_client->search();
}

void CommandController::
onEditClientSaveExecuted() {
  qDebug() << "You executed the Save command!";
  auto& db_controller{ implementation->database_controller };
  const auto& client{ implementation->selected_client };
  db_controller->updateRow(cm::models::Client::NAME, client->id(), client->to_json());
  qDebug() << "Updated client saved.";
}

void CommandController::
onEditClientDeleteExecuted() {
  qDebug() << "You executed the Delete command!";
  auto& db_controller{ implementation->database_controller };
  const auto& client{ implementation->selected_client };
  db_controller->deleteRow(cm::models::Client::NAME, client->id());
  implementation->selected_client = nullptr;

  qDebug() << "Deleted client.";
  implementation->search_client->search();
  implementation->navigation_controller->showDashboardView();
}

void CommandController::
onRssViewRefreshTriggered() {
  qDebug() << "Refreshing...";
  implementation->rss_request->execute();
}

void CommandController::
set_selected_client(cm::models::Client* client) {
  implementation->selected_client = client;
}

}
}
