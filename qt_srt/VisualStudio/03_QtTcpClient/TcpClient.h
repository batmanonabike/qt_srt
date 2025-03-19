#pragma once

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject* parent = nullptr);

    void connectToServer(const QString& host, quint16 port);
    void sendData(const QByteArray& data);

private slots:
    void onConnected();
    void onReadyRead();

private:
    QTcpSocket* socket;
};
