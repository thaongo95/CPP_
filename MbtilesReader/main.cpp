#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mbtileswrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qCritical() << "SQLite driver not available!";
        return -1;
    }
    MBTilesWrapper wrapper;

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("mbtiles"), wrapper.provider());
    engine.rootContext()->setContextProperty("mbtilesWrapper", &wrapper);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
