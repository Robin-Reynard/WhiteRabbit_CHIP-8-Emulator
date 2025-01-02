#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMessageBox>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QString>
#include <QList>
#include <QtNetwork>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void initServer();
    void readyRead();

    QTcpServer *tcpServer = nullptr;


public slots:
    void sendFortune();
    void readSocket();

private:
    QList<QString> fortunes;
    QTcpSocket* clientConnection = nullptr;

};

#endif // SERVER_H
