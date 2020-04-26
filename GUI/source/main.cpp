#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <controllers/master_controller.h>
#include <controllers/command_controller.h>

int main(int argc, char *argv[]) {
  const QUrl url(QStringLiteral("qrc:/views/master_view"));
  using namespace cm::controllers;
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  MasterController master_controller;
  QGuiApplication app(argc, argv);


  qmlRegisterType<MasterController>("CM", 1, 0, "MasterController");
  qmlRegisterType<NavigationController>("CM", 1, 0, "NavigationController");
  qmlRegisterType<CommandController>("CM", 1, 0, "CommandController");
  qmlRegisterType<cm::framework::Command>("CM", 1, 0, "Command");

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
