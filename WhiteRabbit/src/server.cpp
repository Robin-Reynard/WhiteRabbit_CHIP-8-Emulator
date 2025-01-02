#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}

void Server::initServer(){
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        /*QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));*/
        qDebug() << "Unable to start server";
        //close();
        return;
    }
    QString ipAddress;
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (const QHostAddress &entry : ipAddressesList) {
        if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
            ipAddress = entry.toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                   "Run the Fortune Client example now.")
                .arg(ipAddress).arg(tcpServer->serverPort());
    /*ui->image_output->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the Fortune Client example now.")
                         .arg(ipAddress).arg(tcpServer->serverPort()));*/

    /*fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
                 << tr("You've got to think about tomorrow.")
                 << tr("You will be surprised by a loud noise.")
                 << tr("You will feel hungry again in another hour.")
                 << tr("You might have mail.")
                 << tr("You cannot kill time without injuring eternity.")
                 << tr("Computers are not intelligent. They only think they are.");*/
}

void Server::sendFortune(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_6_5);

    clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readSocket()));

    //out << clientConnection->readAll();
           //fortunes[QRandomGenerator::global()->bounded(fortunes.size())];
    clientConnection->write("Not in the ready read function");
    //clientConnection->disconnectFromHost();

}

void Server::readyRead(){
   //qDebug() << "|||||||||||READYREAD SLOT--------";
   //qDebug() << "||||||||" << clientConnection->readAll();
    clientConnection->write("Hello there!");
    clientConnection->disconnectFromHost();

}

void Server::readSocket(){
    QByteArray data = clientConnection->readAll();
    qDebug() << "|||||||||||READYREAD SOCKET--------";
    qDebug() << data;
     clientConnection->write(":3");

}
