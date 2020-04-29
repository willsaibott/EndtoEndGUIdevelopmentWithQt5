#include "master_controller.h"

#include <network/web_request.h>

namespace cm {
namespace controllers {
using namespace network;

class MasterController::Implementation {
public:
  MasterController*     _master_controller{ nullptr };
  NavigationController* _navigation_controller{ nullptr };
  CommandController*    _command_controller{ nullptr };
  DatabaseController*   _database_controller{ nullptr };
  NetworkAccessManager* _network_access_manager{ nullptr };
  models::Client*       _client{ nullptr };
  models::ClientSearch* _client_search{ nullptr };
  WebRequest*           _rss_web_request{ nullptr };
  rss::RssChannel*      _channel{ nullptr };
  QString               _welcome_message{ "Welcome to the Client Management system!" };

  Implementation(MasterController* master_controller)
    : _master_controller{ master_controller }
  {
    static const QUrl url{ "http://feeds.bbci.co.uk/news/rss.xml?edition=uk" };
    _navigation_controller  = new NavigationController(master_controller);
    _database_controller    = new DatabaseController(master_controller);
    _network_access_manager = new NetworkAccessManager(master_controller);
    _client                 = new models::Client(master_controller);
    _rss_web_request        = new WebRequest(master_controller,
                                             _network_access_manager,
                                             url);
    _client_search          =
        new models::ClientSearch(master_controller, _database_controller);

    QObject::connect(_rss_web_request,
                     &WebRequest::request_complete,
                     master_controller,
                     &MasterController::on_rss_reply_received);

    _command_controller    =
        new CommandController(master_controller,
                              _database_controller,
                              _navigation_controller,
                              _network_access_manager,
                              _rss_web_request,
                              _client,
                              _client_search);
  }
};

NavigationController* MasterController::
navigation_controller() {
  return implementation->_navigation_controller;
}

CommandController* MasterController::
command_controller() {
  return implementation->_command_controller;
}

DatabaseController *MasterController::
database_controller() {
  return implementation->_database_controller;
}

models::Client *MasterController::
new_client() {
  return implementation->_client;
}

models::ClientSearch *MasterController::
client_search() {
  return implementation->_client_search;
}

network::NetworkAccessManager *MasterController::
network_access_manager() {
  return implementation->_network_access_manager;
}

rss::RssChannel *MasterController::
rss_channel() {
  return implementation->_channel;
}

void MasterController::
select_client(models::Client *client) {
  implementation->_navigation_controller->showEditView(client);
}

void MasterController::
on_rss_reply_received(int status_code, QByteArray body) {
  qDebug() << "Received RSS request response code " << status_code << ":";
  qDebug() << body;

  if (implementation->_channel) {
    implementation->_channel->deleteLater();
    implementation->_channel = nullptr;
    emit rssChannelChanged();
  }

  implementation->_channel = rss::RssChannel::from_xml(body, this);
  emit rssChannelChanged();
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
