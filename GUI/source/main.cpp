#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <controllers/master_controller.h>

int main(int argc, char *argv[]) {
  const QUrl url(QStringLiteral("qrc:/views/master_view"));
  using MasterController     = cm::controllers::MasterController;
  using NavigationController = cm::controllers::NavigationController;
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  MasterController master_controller;
  QGuiApplication app(argc, argv);


  qmlRegisterType<MasterController>("CM", 1, 0, "MasterController");
  qmlRegisterType<NavigationController>("CM", 1, 0, "NavigationController");

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
