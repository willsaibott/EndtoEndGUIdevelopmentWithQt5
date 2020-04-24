#pragma once

#include <QObject>
#include <QString>
#include <lib_global.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT
  Q_PROPERTY( QString ui_welcome_message MEMBER welcomeMessage CONSTANT )
public:
  explicit MasterController(QObject *parent = nullptr);

  QString welcomeMessage{ "This is MasterController to Major Tom" };

signals:

public slots:
};

}
}

