#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "clientmodel.hpp"

int main(int   _argc,
         char *_p_argv[]) {
    QGuiApplication       app(_argc, _p_argv);
    QQmlApplicationEngine engine;
    const QUrl            url(u"qrc:/ISY/qml/main.qml"_qs);
    qmlRegisterType<ClientModel>("ClientModel", 0, 1, "ClientModel");
    engine.rootContext()->setContextProperty("client", &g_client);
    QQuickStyle::setStyle("Material");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
         [url](QObject    *_p_obj,
               const QUrl &_obj_url) {
             if (!_p_obj && url == _obj_url)
                 QCoreApplication::exit(-1);
         },
         Qt::QueuedConnection
    );
    engine.load(url);
    return app.exec();
}
