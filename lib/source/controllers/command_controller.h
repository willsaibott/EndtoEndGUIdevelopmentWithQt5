#pragma once
#include <functional>

#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QtQml/QQmlListProperty>

#include <lib_global.h>
#include <framework/command.h>

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
public:
  explicit CommandController(QObject *parent = nullptr);
  ~CommandController();

  QQmlListProperty<cm::framework::Command>
  create_client_view_context_commands();

public slots:
  void onCreateClientSaveExecuted();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}

