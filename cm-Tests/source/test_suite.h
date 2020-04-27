#pragma once

#include <QObject>
#include <QTest>
#include <QString>
#include <QVector>

namespace cm {

  class TestSuite : public QObject
  {
    Q_OBJECT
  public:
    explicit TestSuite(const QString& name = "");
    virtual ~TestSuite();

    QString name;
    static QVector<TestSuite*>& test_list();

  signals:

  public slots:
  };

}

