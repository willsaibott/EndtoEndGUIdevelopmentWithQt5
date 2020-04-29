#pragma once

#include <QObject>
#include <QList>
#include <QScopedPointer>
#include <QSslError>

#include <network/iweb_request.h>
#include <network/inetwork_access.h>

namespace cm {
namespace network {

class WebRequest : public QObject, public IWebRequest
{
  Q_OBJECT
public:
  WebRequest(QObject* parent = nullptr) = delete;
  WebRequest(QObject*               parent,
             INetworkAccessManager* network_manager,
             const QUrl&            url);
  ~WebRequest();

public:
    void execute() override;
    bool is_busy() const override;
    void set_url(const QUrl& url) override;
    QUrl url() const override;

signals:
    void error(QString message);
    void is_busy_changed();
    void request_complete(int statusCode, QByteArray body);
    void url_changed();

private slots:
    void reply_delegate();
    void ssl_errors_delegate( const QList<QSslError>& _errors );

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}
