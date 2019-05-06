#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include "RemoteImage.h"
#include "RemoteSocketImage.h"


int main(int argc, char *argv[]){
  QGuiApplication app(argc, argv);

  app.setOrganizationName("zsh");
  app.setOrganizationDomain("zshbox.com");
  app.setApplicationName("RPI Cam Viewer");

  // Register custom types with the QML
  qmlRegisterType<RemoteImage>("Rpi", 1, 0, "RemoteImage");
  qmlRegisterType<RemoteSocketImage>("Rpi", 1, 0, "RemoteSocketImage");

  QQmlApplicationEngine engine;
  qreal pdpi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
  qreal dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
  engine.rootContext()->setContextProperty("SPD", pdpi*dpr);
  engine.load(QUrl("qrc:///src/app.qml"));

  return app.exec();
}
