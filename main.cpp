#include <QGuiApplication>
#include "raindrops_qml_application_engine.h"


#include <QDebug>
#include "raindrops_drop.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    raindrops::qml_application_engine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("math_raindrops", "Main");

    return app.exec();
}
