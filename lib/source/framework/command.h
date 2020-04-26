#pragma once

#include <QObject>
#include <QScopedPointer>
#include <functional>
#include <lib_global.h>

namespace cm {
namespace framework {

class CMLIBSHARED_EXPORT Command : public QObject
{
  Q_OBJECT
  Q_PROPERTY( QString ui_icon_character READ icon_character CONSTANT)
  Q_PROPERTY( QString ui_description READ description CONSTANT )
  Q_PROPERTY( bool ui_can_execute READ can_be_executed NOTIFY canExecuteChanged)

public:
  explicit Command(QObject *parent                    = nullptr,
                   const QString& icon_character      = "",
                   const QString& description         = "",
                   std::function<bool()> can_executed = [](){ return true; });
  ~Command();

  const QString& icon_character() const;
  const QString& description() const;
  bool can_be_executed() const;

signals:
  void canExecuteChanged();
  void executed();

private:
  class Implementation;
  QScopedPointer<Implementation> implementation;
};

}
}

