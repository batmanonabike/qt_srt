#include "TcpClient.h"
#include <QDebug>

TcpClient::TcpClient(QObject* parent) : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer(const QString& host, quint16 port)
{
    socket->connectToHost(host, port);
}

void TcpClient::sendData(const QByteArray& data)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data);
    }
    else {
        qWarning() << "Not connected to server";
    }
}

void TcpClient::onConnected()
{
    qDebug() << "Connected to server";
}

void TcpClient::onReadyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << "Received data from server:" << data;
}

// #include "main.moc"
