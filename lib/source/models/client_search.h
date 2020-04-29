#pragma once

#include <lib_global.h>
#include <controllers/idatabase_controller.h>
#include <models/client.h>

namespace cm {
namespace models {

class CMLIBSHARED_EXPORT ClientSearch : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY( cm::data::StringDecorator* ui_search_text READ search_text CONSTANT )
    Q_PROPERTY( QQmlListProperty<cm::models::Client> ui_search_results
                READ search_results NOTIFY searchResultsChanged )

public:
    ClientSearch(QObject*                          parent             = nullptr,
                 controllers::IDatabaseController* databaseController = nullptr);
    ~ClientSearch();

    data::StringDecorator* search_text();
    QQmlListProperty<Client> search_results();
    void search();

    static const QString NAME;
    static const QString SEARCH_TEXT;
    static const QString SEARCH_RESULT;
    static const QString SEARCH_TEXT_LABEL;
    static const QString SEARCH_RESULT_LABEL;

signals:
    void searchResultsChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}

