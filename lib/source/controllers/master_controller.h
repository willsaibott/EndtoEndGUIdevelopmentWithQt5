#pragma once

#include <QObject>
#include <lib_global.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT MasterController : public QObject
{
  Q_OBJECT
public:
  explicit MasterController(QObject *parent = nullptr);

signals:

public slots:
};

}
}

