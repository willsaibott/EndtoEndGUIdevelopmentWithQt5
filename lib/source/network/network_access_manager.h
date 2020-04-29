#pragma once

#include <QObject>
#include <QScopedPointer>
#include <lib_global.h>
#include <network/inetwork_access.h>

namespace cm {
namespace network {

class NetworkAccessManager : public QObject, public INetworkAccessManager
{
  Q_OBJECT

public:
  explicit NetworkAccessManager(QObject *parent = nullptr);
  ~NetworkAccessManager();
  QNetworkReply* get(const QNetworkRequest& request) override;
  bool is_network_accessible() const override;

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;

};

}
}

