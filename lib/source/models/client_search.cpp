#include "client_search.h"
#include <QObject>
#include <QDebug>

namespace cm {
namespace models {
using namespace controllers;
using namespace data;

const QString ClientSearch::NAME{ "client_search"};
const QString ClientSearch::SEARCH_TEXT{ "search_text" };
const QString ClientSearch::SEARCH_RESULT{ "search_result" };
const QString ClientSearch::SEARCH_TEXT_LABEL{ "Search Text" };
const QString ClientSearch::SEARCH_RESULT_LABEL{ "Search Result" };

class ClientSearch::Implementation {
public:
  Implementation(ClientSearch* client_search, IDatabaseController* db_controller)
    : client_search{ client_search }, db_controller{ db_controller }
  {

  }

  ClientSearch*                   client_search{ nullptr };
  IDatabaseController*            db_controller{ nullptr };
  data::StringDecorator*          search_text{ nullptr };
  data::EntityCollection<Client>* search_results{ nullptr };
};

ClientSearch::
ClientSearch(QObject *                             parent,
             cm::controllers::IDatabaseController* database_controller)
  : Entity{ parent, NAME }
{
  implementation.reset(new Implementation(this, database_controller));
  implementation->search_text =
      static_cast<StringDecorator*>(add_data_item(
          new StringDecorator(this, SEARCH_TEXT, SEARCH_TEXT_LABEL)
      ));
  implementation->search_results =
      static_cast<EntityCollection<Client>*>(
          add_child_collection(
            new EntityCollection<Client>(this, SEARCH_RESULT)
          ));
  connect(implementation->search_results,
          &EntityCollection<Client>::collectionChanged,
          this,
          &ClientSearch::searchResultsChanged);

}

ClientSearch::
~ClientSearch() {

}

data::StringDecorator *ClientSearch::
search_text() {
  return implementation->search_text;
}

QQmlListProperty<Client> ClientSearch::
search_results() {
  return QQmlListProperty<Client>(this, implementation->search_results->derived_entities());
}

void ClientSearch::
search() {
  const auto& term{ implementation->search_text->value() };
  qDebug() << "Searching for " << term << "...";

  const auto results{ implementation->db_controller->find(Client::NAME, term) };
  implementation->search_results->update(results);

  qDebug() << "Found " << implementation->search_results->base_entities().size()
           << " matches";
}

}
}

