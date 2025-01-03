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
    client_connection->write(":3");


    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        append_message_to_console(tr("REQUEST ERROR: %1 at index %2 in %3").arg(parseError.errorString()).arg(parseError.offset).arg(QString(data)));
        return;
    }

    QJsonObject rootObject = itemDoc.object();
    QString requestType = rootObject.value("request").toString();
    if(requestType == "PUBLISH_TEXT"){
        qDebug() << "Publish";
    }
    else{
        qDebug() << "No such request";
    }


    /*QJsonDocument itemDoc = QJsonDocument::fromJson(data);
    QJsonObject rootObject = itemDoc.object();
    qDebug() << itemDoc.toJson(QJsonDocument::Compact);
    qDebug() << rootObject.value("request");

    if(rootObject.value("request").toString() == "PUBLISH_TEXT"){
        qDebug() << "Publish";
    }
    else{
        qDebug() << "No such request";
    }*/



    /*QJsonParseError err;

    auto doc = QJsonDocument::fromJson(QString(client_connection->readAll().toBase64()), &err );
    auto objects = doc.array();
    qDebug() << objects[0].toObject();

    if ( err.error != QJsonParseError::NoError )
    {
        qDebug() << err.errorString();
    }

    /*for( auto obj_val : objects )
    {
        qDebug() << obj_val.toObject();
        auto obj = obj_val.toObject();

        auto contacts = obj.value( "contacts" ).toArray();

        for ( auto contact_val : contacts )
        {
            auto cotact_str = contact_val.toString();

            qDebug() << cotact_str;
        }
    }*/


    /*QStringList parts = QString(client_connection->readAll().toBase64()).split("|");
            /*if (parts.size() < 2) {
                sendResponse(socket, "ERROR: Invalid request");
                return;
            }

            QString command = parts[0];
            QString data = parts[1];
    qDebug() << parts[0];*/
}

void Server::append_message_to_console(QString message){
    ui->console->moveCursor(QTextCursor::End);
    ui->console->appendHtml("<div style='color: #8B8000;'> [SERVER]:" + message + "</div>");
    ui->console->moveCursor (QTextCursor::End);
}
