#pragma once

#include <QObject>

class IDatabaseController : public QObject
{
  Q_OBJECT
public:
  explicit IDatabaseController(QObject *parent = nullptr);

signals:

public slots:
};

