#pragma once

#include <QNetworkReply>
#include <QNetworkRequest>

namespace cm {
namespace network {
class INetworkAccessManager
{
public:
    INetworkAccessManager(){}
    virtual ~INetworkAccessManager(){}
    virtual QNetworkReply* get(const QNetworkRequest& request) = 0;
    virtual bool is_network_accessible() const = 0;
};
}}
