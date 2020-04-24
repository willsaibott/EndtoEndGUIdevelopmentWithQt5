#pragma once

#include <QObject>

class MasterController : public QObject
{
  Q_OBJECT
public:
  explicit MasterController(QObject *parent = nullptr);

signals:

public slots:
};

