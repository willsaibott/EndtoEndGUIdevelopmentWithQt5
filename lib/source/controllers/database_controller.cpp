#include "database_controller.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlDriver>

namespace cm {
namespace controllers {
class DatabaseController::Implementation {
public:
 Implementation(DatabaseController* controller) : _controller{ controller } {
   if (initialize()) {
     qDebug() << "Database created using Sqlite Version: " + sqlite_version();
     if (create_tables()) {
       qDebug() << "Database tables created";
     }
     else {
       qDebug() << "ERROR: Unable to create database tables";
     }
   }
   else {
     qDebug() << "ERROR: UNable to open database";
   }
 }

 DatabaseController*  _controller;
 QSqlDatabase         _database;

private:
  bool
  initialize() {
    _database = QSqlDatabase::addDatabase("QSQLITE", "cm");
    _database.setDatabaseName("cm.sqlite");
    return _database.open();
  }

  bool
  create_tables() {
    return create_json_table("client");
  }

  bool
  create_json_table(const QString& table_name) const {
    QSqlQuery query{ _database };
    QString  sql_statement{
      "CREATE TABLE IF NOT EXISTS " +
      table_name + " (id text primary key, json text not null)"
    };

    return query.prepare(sql_statement) &&
           query.exec();
  }

  QString
  sqlite_version() const {
    QString version { QString::number(-1) };
    QSqlQuery query{ _database };
    if (query.exec("SELECT sqlite_version()") && query.next()) {
      version = query.value(0).toString();
    }
    return version;
  }
};

DatabaseController::
DatabaseController(QObject *parent) : IDatabaseController (parent) {
implementation.reset(new Implementation(this));
}

DatabaseController::
~DatabaseController() {

}

bool DatabaseController::
createRow(const QString&     table_name,
         const QString&     id,
         const QJsonObject& object) const
{
  bool ok { !table_name.isEmpty() && ! id.isEmpty() && !object.isEmpty() };
  if (ok) {
    QSqlQuery query { implementation->_database };
    QString sql_statement{
      "INSERT OR REPLACE INTO " + table_name + "(id, json) VALUES (:id, :json)"
    };
    if ((ok = query.prepare(sql_statement))) {
      const auto compact{ QJsonDocument{ object }.toJson(QJsonDocument::Compact) };
      query.bindValue(":id",   QVariant{ id });
      query.bindValue(":json", QVariant{ compact });
      ok = query.exec() && query.numRowsAffected();
    }
  }
  return ok;
}

bool DatabaseController::
deleteRow(const QString &table_name, const QString &id) const {
  bool ok{ !table_name.isEmpty() && !id.isEmpty() };
  if (ok) {
    QSqlQuery query{ implementation->_database };
    QString sql_statement { "DELETE FROM " + table_name + " WHERE id=:id" };
    if ((ok = query.prepare(sql_statement))) {
      query.bindValue(":id", QVariant{ id });
      ok = query.exec() && query.numRowsAffected();
    }
  }
  return ok;
}

QJsonArray DatabaseController::
find(const QString &table_name, const QString &search_text) const {
  QJsonArray output;
  if (!table_name.isEmpty() && !search_text.isEmpty()) {
    QSqlQuery query( implementation->_database );
    QString sql_statement{
      "SELECT json FROM " + table_name + " where lower(json) like :term"
    };
    if (query.prepare(sql_statement)) {
      query.bindValue(":term", "%" + search_text.toLower() + "%" );
      if (query.exec()) {
        while (query.next()) {
          const auto json{ query.value(0).toByteArray() };
          const auto json_doc{ QJsonDocument::fromJson(json) };
          if (json_doc.isObject()) {
            output.append(json_doc.object());
          }
        }

      }
    }
  }
  return output;
}

QJsonObject DatabaseController::
readRow(const QString &table_name, const QString &id) const {
  QJsonObject output;
  if (!table_name.isEmpty() && !id.isEmpty()) {
    QSqlQuery query{ implementation->_database };
    QString sql_statement{ "SELECT json FROM " + table_name + " WHERE id=:id " };
    if (query.prepare(sql_statement)) {
      query.bindValue(":id", QVariant{ id });
      if (query.exec() && query.first()) {
        const auto json{ query.value(0).toByteArray() };
        const auto json_doc { QJsonDocument::fromJson(json) };
        output = json_doc.object();
      }
    }
  }
  return output;
}

bool DatabaseController::
updateRow(const QString&     table_name,
          const QString&     id,
          const QJsonObject& json_object) const
{
  bool ok { !table_name.isEmpty() && !id.isEmpty() && !json_object.isEmpty()};
  if (ok) {
    QSqlQuery query{ implementation->_database };
    QString statement{ "UPDATE " + table_name + " SET json=:json WHERE id=:id" };
    if ((ok = query.prepare(statement))) {
      const auto compact{
        QJsonDocument{ json_object }.toJson(QJsonDocument::Compact)
      };
      query.bindValue(":id",   QVariant{ id });
      query.bindValue(":json", QVariant{ compact });
      ok = query.exec() && query.numRowsAffected();
    }
  }
  return ok;
}

}
}
