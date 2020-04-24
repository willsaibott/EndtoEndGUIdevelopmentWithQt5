#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <controllers/master_controller.h>

int main(int argc, char *argv[])
{
  const QUrl url(QStringLiteral("qrc:/views/master_view.qml"));
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  qmlRegisterType<cm::controllers::MasterController>("CM",
                                                     1,
                                                     0,
                                                     "MasterController");
  cm::controllers::MasterController master_controller;
  QQmlApplicationEngine engine;
  engine.rootContext()
        ->setContextProperty("master_controller", &master_controller);

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
