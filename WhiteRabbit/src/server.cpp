#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
}

void Server::start_server(Ui::DualWindow* ui, CHIP8* chip8){
    qDebug() << chip8->get_display();
    this->ui = ui;
    this->chip8 = chip8;


    tcp_server = new QTcpServer(this);
    if (!tcp_server->listen()) {
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
                .arg(ipAddress).arg(tcp_server->serverPort());
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

    append_message_to_console(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                                 "Run the Fortune Client example now.")
                              .arg(ipAddress).arg(tcp_server->serverPort()));
    append_message_to_console("READY");

    /*ui->console->moveCursor(QTextCursor::End);
    ui->console->insertPlainText (tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                                     "Run the Fortune Client example now.")
                                  .arg(ipAddress).arg(tcp_server->serverPort()));
    ui->console->moveCursor (QTextCursor::End);*/
}

void Server::establish_client_connection(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_6_5);

    client_connection = tcp_server->nextPendingConnection();

    connect(client_connection, SIGNAL(readyRead()), this, SLOT(parse_client_request()));

    //out << clientConnection->readAll();
           //fortunes[QRandomGenerator::global()->bounded(fortunes.size())];
    //client_connection->write("Not in the ready read function");
    //clientConnection->disconnectFromHost();

}


void Server::parse_client_request(){
    QByteArray data = client_connection->readAll();
    qDebug() << "|||||||||||READYREAD SOCKET--------";
    qDebug() << data;
    client_connection->write(":3");
}

void Server::append_message_to_console(QString message){
    ui->console->moveCursor(QTextCursor::End);
    ui->console->appendPlainText("[SERVER]:" + message);
    ui->console->moveCursor (QTextCursor::End);
}
