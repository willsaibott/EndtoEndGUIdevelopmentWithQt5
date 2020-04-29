#include "web_request.h"

#include <QMap>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace cm {
namespace network {

static const QMap<QNetworkReply::NetworkError, QString> network_error_Mapper {
  { QNetworkReply::ConnectionRefusedError,
        "The remote server refused the connection (the server is not accepting requests)." },
  { QNetworkReply::UnknownServerError,
        "An unkown error related to the server response was detected." }

};

class WebRequest::Implementation {
public:
  Implementation(WebRequest*            web_req,
                 INetworkAccessManager* manager,
                 const QUrl&            url)
    : web_request{ web_req }, network_access_manager{ manager }, url{ url }
  {

  }

  WebRequest*             web_request{ nullptr };
  INetworkAccessManager*  network_access_manager{ nullptr };
  QUrl                    url{};
  QNetworkReply*          reply{ nullptr };

  bool
  is_busy() const {
    return _is_busy;
  }

  void
  set_is_busy(bool value) {
    if (value != _is_busy) {
      _is_busy = value;
      emit web_request->is_busy_changed();
    }
  }

private:
  bool _is_busy{false};
};


WebRequest::
WebRequest(QObject*               parent,
           INetworkAccessManager* network_manager,
           const QUrl&            url)
  : QObject (parent)
{
  implementation.reset(
        new WebRequest::Implementation(this, network_manager, url));
}

WebRequest::
~WebRequest() {
}

void WebRequest::
execute() {
  auto& reply{ implementation->reply };
  if (!implementation->is_busy()) {
    if (implementation->network_access_manager->is_network_accessible()) {
      implementation->set_is_busy(true);
      QNetworkRequest request;
      request.setUrl(implementation->url);
      reply = implementation->network_access_manager->get(request);
      if (reply) {
        connect(reply, &QNetworkReply::finished,  this, &WebRequest::reply_delegate);
        connect(reply, &QNetworkReply::sslErrors, this, &WebRequest::ssl_errors_delegate);
      }
    }
    else {
      emit error("Network not accessible");
    }
  }
  else {
    qDebug() << "Request is busy right now";
  }
}

bool WebRequest::
is_busy() const {
  return implementation->is_busy();
}

void WebRequest::
set_url(const QUrl &url) {
  if (url != implementation->url) {
    implementation->url = url;
    emit url_changed();
  }
}

QUrl WebRequest::
url() const {
  return implementation->url;
}

void WebRequest::
reply_delegate() {
  auto& reply{ implementation->reply };
  implementation->set_is_busy(false);
  if (reply) {
    disconnect(reply,
               &QNetworkReply::finished,
               this,
               &WebRequest::reply_delegate);
    disconnect(reply,
               &QNetworkReply::sslErrors,
               this,
               &WebRequest::ssl_errors_delegate);

    const auto status_code { reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) };
    auto response_body{ reply->readAll() };
    auto reply_status { reply->error() };
    reply->deleteLater();

    qDebug() << "Request status: " << status_code.toString();
    qDebug() << "Error status: "   << reply_status;

    if (reply_status != QNetworkReply::NoError) {
      emit error(network_error_Mapper[reply->error()]);
    }

    emit request_complete(status_code.toInt(), response_body);
  }
  else {
    emit error("Unexpected error - reply object is null");
  }
}

void WebRequest::
ssl_errors_delegate(const QList<QSslError> &errors) {
  QString ssl_error;
  for (const auto& err : errors) {
    ssl_error += err.errorString() + "\n";
  }
  emit error(ssl_error);
}

}
}
