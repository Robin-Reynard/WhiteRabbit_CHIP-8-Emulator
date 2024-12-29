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
    QTcpServer *tcpServer = nullptr;


public slots:
    void sendFortune();

private:
    QList<QString> fortunes;

};

#endif // SERVER_H
