#include <QDebug>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>

class TcpServer : public QObject
{
    Q_OBJECT

public:
    TcpServer(QObject* parent = nullptr);

private slots:
    void newConnection();
    void readData();

private:
    QTcpServer* server;
    QTcpSocket* clientSocket;
};

TcpServer::TcpServer(QObject* parent) : QObject(parent), server(new QTcpServer(this)), clientSocket(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection);

    if (!server->listen(QHostAddress::Any, 1234)) {
        qCritical() << "Unable to start the server:" << server->errorString();
        return;
    }

    qDebug() << "Server started, listening on port" << server->serverPort();
}

void TcpServer::newConnection()
{
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::readData);
    qDebug() << "New client connected from" << clientSocket->peerAddress().toString();
}

void TcpServer::readData()
{
    QByteArray data = clientSocket->readAll();
    qDebug() << "Received data:" << data;
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer server;

    qDebug() << "Qt is working";
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);

    return a.exec();
}

// Include the Meta-Object Compiler (MOC) generated code.
#include "main.moc"
