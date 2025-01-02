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
    void start_server();

    QTcpServer *tcp_server = nullptr;


public slots:
    void establish_client_connection();
    void parse_client_request();

private:
    QTcpSocket* client_connection = nullptr;
};

#endif // SERVER_H
