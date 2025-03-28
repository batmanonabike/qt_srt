#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtSrtMainLib/QtSrtMainLib.h>
#include <QtSrtMainLib/CameraController.h>

int main(int argc, char* argv[])
{
    QtSrtMainLib_TestMethod();

    QGuiApplication app(argc, argv);

    // Register the camera controller type for QML
    qmlRegisterType<CameraController>("com.example.camera", 1, 0, "CameraController");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}