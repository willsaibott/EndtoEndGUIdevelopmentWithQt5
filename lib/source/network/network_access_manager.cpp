#include "network_access_manager.h"

namespace cm {
namespace network {

class NetworkAccessManager::Implementation {
public:
  Implementation(NetworkAccessManager* manager) : _manager{ manager } {

  }

  NetworkAccessManager* _manager{ nullptr };
  QNetworkAccessManager network_manager;
};

NetworkAccessManager::
NetworkAccessManager(QObject *parent) : QObject{ parent } {
  implementation.reset(new Implementation(this));
}

NetworkAccessManager::
~NetworkAccessManager() {

}

QNetworkReply *NetworkAccessManager::
get(const QNetworkRequest &request) {
  return implementation->network_manager.get(request);
}

bool NetworkAccessManager::
is_network_accessible() const {
  return QNetworkAccessManager::Accessible ==
            implementation->network_manager.networkAccessible();
}

}
}
