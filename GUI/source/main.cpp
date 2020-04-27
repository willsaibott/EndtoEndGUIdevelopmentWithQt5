#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <controllers/master_controller.h>
#include <controllers/command_controller.h>

#include <data/datetime_decorator.h>
#include <data/integer_decorator.h>
#include <data/string_decorator.h>
#include <data/enumerator_decorator.h>
#include <data/entity.h>
#include <models/address.h>
#include <models/appointment.h>
#include <models/client.h>
#include <models/contact.h>


inline void
register_qml_types() {
  qmlRegisterType<cm::controllers::MasterController>("CM", 1, 0, "MasterController");
  qmlRegisterType<cm::controllers::NavigationController>("CM", 1, 0, "NavigationController");
  qmlRegisterType<cm::controllers::CommandController>("CM", 1, 0, "CommandController");

  qmlRegisterType<cm::framework::Command>("CM", 1, 0, "Command");

  qmlRegisterType<cm::data::DateTimeDecorator>("CM", 1, 0, "DateTimeDecorator");
  qmlRegisterType<cm::data::EnumeratorDecorator>("CM", 1, 0, "EnumeratorDecorator");
  qmlRegisterType<cm::data::IntegerDecorator>("CM", 1, 0, "IntegerDecorator");
  qmlRegisterType<cm::data::StringDecorator>("CM", 1, 0, "StringDecorator");

  qmlRegisterType<cm::models::Address>("CM", 1, 0, "Address");
  qmlRegisterType<cm::models::Appointment>("CM", 1, 0, "Appointment");
  qmlRegisterType<cm::models::Client>("CM", 1, 0, "Client");
  qmlRegisterType<cm::models::Contact>("CM", 1, 0, "Contact");
}


int main(int argc, char *argv[]) {
  const QUrl url(QStringLiteral("qrc:/views/master_view"));
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  cm::controllers::MasterController master_controller;
  QGuiApplication app(argc, argv);

  register_qml_types();

  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/");
  engine.rootContext()
        ->setContextProperty("master_controller", &master_controller);

  QObject::connect(&engine,
                   &QQmlApplicationEngine::objectCreated,
                   &app,
                   [url](QObject *obj, const QUrl &objUrl) {
                       if (!obj && url == objUrl)
                         QCoreApplication::exit(-1);
                   },
                   Qt::QueuedConnection);

  engine.load(url);

  return app.exec();
}
