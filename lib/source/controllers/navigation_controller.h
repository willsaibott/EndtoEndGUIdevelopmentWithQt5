#pragma once

#include <QObject>
#include <lib_global.h>
#include <models/client.h>

namespace cm {
namespace controllers {

  class CMLIBSHARED_EXPORT NavigationController : public QObject
  {
    Q_OBJECT
  public:
    explicit NavigationController(QObject *parent = nullptr);

  signals:
    void showNewClientView();
    void showDashboardView();
    void showEditView(cm::models::Client* client);
    void showSearchView();
    void showRssView();

  public slots:
  };
}
}


