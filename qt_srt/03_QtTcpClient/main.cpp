#include <QCoreApplication>
#include <QTimer>
#include <QThread>
#include "TcpClient.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    TcpClient client;

    QThread::sleep(10);
    client.connectToServer("127.0.0.1", 1234);

    QTimer::singleShot(1000, [&client]() {
        client.sendData("Hello, Server!");
        });
    //QTimer::singleShot(5000, &a, &QCoreApplication::quit);

    return a.exec();
}

