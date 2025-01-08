#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
}

void Server::start_server(Ui::DualWindow* ui, CHIP8* chip8){
    this->ui = ui;
    this->chip8 = chip8;


    tcp_server = new QTcpServer(this);
    if (!tcp_server->listen()) {
        append_message_to_console(tr("ERROR: Unable to start Server: %1.").arg(tcp_server->errorString()));
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

    append_message_to_console(tr("Server started on IP: %1, port: %2.").arg(ipAddress).arg(tcp_server->serverPort()));
    append_message_to_console("Awaiting client connection");
}

void Server::establish_client_connection(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_6_5);

    client_connection = tcp_server->nextPendingConnection();

    connect(client_connection, SIGNAL(readyRead()), this, SLOT(parse_client_request()));
    append_message_to_console("Client connection established!");
}


void Server::parse_client_request(){
    QByteArray data = client_connection->readAll();
    qDebug() << "|||||||||||READYREAD SOCKET--------";
    qDebug() << data;
    //client_connection->write(":3");


    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        append_message_to_console(tr("REQUEST ERROR: %1 at index %2 in %3").arg(parseError.errorString()).arg(parseError.offset).arg(QString(data)));
        return;
    }

    QJsonObject rootObject = jsonDoc.object();
    QString requestType = rootObject.value("request").toString();

    if(requestType == "GET_IMAGE"){
        QByteArray array;

        //client_connection->write(QByteArray(chip8->get_display()));
        for(int i {0}; i < 2048; i++){
            array.append(chip8->get_display()[i]);
        }

        //array.append(ch);
        client_connection->write(array);
        qDebug() << "Get image";
    }
    else if(requestType == "GET_CHIP8_INFO"){
        qDebug() << "Get chip8 info";
        client_connection->write(":3");
    }
    else if(requestType == "PUBLISH_COMMAND"){
        qDebug() << "publish command";
        client_connection->write(":3");
    }
    else if(requestType == "PUBLISH_TEXT"){
        publish_text_to_console(rootObject.value("text").toString());
        client_connection->write(":3");
    }
    else if(requestType == "PUBLISH_IMAGE"){
        qDebug() << "publish image";
        client_connection->write(":3");
    }
    else{
        append_message_to_console("Invalid request");
        client_connection->write(":3");
    }
}

void Server::publish_text_to_console(QString message){
    ui->console->moveCursor(QTextCursor::End);
    ui->console->appendHtml("<div>" + message + "</div>");
    ui->console->moveCursor (QTextCursor::End);
}

void Server::append_message_to_console(QString message){
    ui->console->moveCursor(QTextCursor::End);
    ui->console->appendHtml("<div style='color: #8B8000;'> [SERVER] " + message + "</div>");
    ui->console->moveCursor (QTextCursor::End);
}
