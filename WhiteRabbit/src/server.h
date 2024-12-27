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

private slots:
    void sendFortune();

private:
    QTcpServer *tcpServer = nullptr;
    QList<QString> fortunes;

};

#endif // SERVER_H
