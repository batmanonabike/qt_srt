#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <srt.h> 
#include <QtSrtMainLib.h>

int main(int argc, char *argv[]) {
    srt_startup();
    QtSrtMainLib_TestMethod();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    int result = app.exec();
    srt_cleanup();
    return result;
}
