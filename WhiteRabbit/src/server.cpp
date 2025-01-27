#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
}

void Server::start_server(QLabel* image_slot, QPlainTextEdit* console, CHIP8* chip8){
    this->image_slot = image_slot;
    this->console = console;
    this->chip8 = chip8;

    // Start TCP Sever on LocalHost and port 3000
    tcp_server = new QTcpServer(this);
    if (!tcp_server->listen(QHostAddress::LocalHost, 3000)) {
        append_message_to_console(tr("ERROR: Unable to start: %1.").arg(tcp_server->errorString()));
        return;
    }

    // Display server details in the console
    append_message_to_console(tr("Server started on IP: %1, port: %2.")
                              .arg(QHostAddress(QHostAddress::LocalHost).toString())
                              .arg(tcp_server->serverPort()));
    append_message_to_console("Awaiting client connection");

    // Setup server-client connection requests
    connect(tcp_server, SIGNAL(newConnection()), this, SLOT(establish_client_connection()));
}

void Server::establish_client_connection(){
    client_connection = tcp_server->nextPendingConnection();
    append_message_to_console("Client connection established!");

    // Setup server-client communication on query by client
    connect(client_connection, SIGNAL(readyRead()), this, SLOT(parse_client_request()));
}


void Server::parse_client_request(){
    // Set server response communication format
    QByteArray response;
    QDataStream out(&response, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    // Get client request
    QByteArray request_raw = client_connection->readAll();

    // Convert request to JSON
    QJsonParseError parse_error;
    QJsonDocument request_json = QJsonDocument::fromJson(request_raw, &parse_error);

    // Check for parsing errors
    if(parse_error.error != QJsonParseError::NoError){
        append_message_to_console(tr("REQUEST ERROR: %1 in request %2").arg(parse_error.errorString()).arg(QString(request_raw)));
        return;
    }

    // Handle request based on request type
    QJsonObject request_root = request_json.object();
    QString request_type = request_root.value("request").toString();
    if (request_type == "GET_SCREEN_CAPTURE"){
        response = handle_get_screen_capture_request();
    }
    else if (request_type == "GET_CHIP8_INFO"){
        response = handle_get_chip8_info_request();
    }
    else if (request_type == "PUBLISH_COMMAND"){
        response = handle_publish_command_request(request_root);
    }
    else if (request_type == "PUBLISH_TEXT"){
        response = handle_publish_text_request(request_root);
    }
    else if (request_type == "PUBLISH_IMAGE"){
        response = handle_publish_image_request(request_root);
    }
    else{
        response = QString("Request of type " + request_type + " not supported").toUtf8();
    }

    // Send response to client
    client_connection->write(response);
}

QByteArray Server::handle_publish_image_request(QJsonObject request){
    QByteArray image_data = QByteArray::fromBase64(request.value("image").toString().toUtf8());
    QPixmap pixmap;
    if(pixmap.loadFromData(image_data)){
        image_slot->setPixmap(pixmap.scaled(image_slot->size(), Qt::KeepAspectRatio));
        return SUCCESS_RESPONSE;
    }
    else{
        return "ERROR: Failed to load image from data.";
    }
}

QByteArray Server::handle_get_chip8_info_request(){
    QJsonObject jsonObject;
    jsonObject.insert("is_beeping", chip8->is_beeping());
    jsonObject.insert("key_0", chip8->get_keyboard()[0]);
    jsonObject.insert("key_1", chip8->get_keyboard()[1]);
    jsonObject.insert("key_2", chip8->get_keyboard()[2]);
    jsonObject.insert("key_3", chip8->get_keyboard()[3]);
    jsonObject.insert("key_4", chip8->get_keyboard()[4]);
    jsonObject.insert("key_5", chip8->get_keyboard()[5]);
    jsonObject.insert("key_6", chip8->get_keyboard()[6]);
    jsonObject.insert("key_7", chip8->get_keyboard()[7]);
    jsonObject.insert("key_8", chip8->get_keyboard()[8]);
    jsonObject.insert("key_9", chip8->get_keyboard()[9]);
    jsonObject.insert("key_A", chip8->get_keyboard()[10]);
    jsonObject.insert("key_B", chip8->get_keyboard()[11]);
    jsonObject.insert("key_C", chip8->get_keyboard()[12]);
    jsonObject.insert("key_D", chip8->get_keyboard()[13]);
    jsonObject.insert("key_E", chip8->get_keyboard()[14]);
    jsonObject.insert("key_F", chip8->get_keyboard()[15]);
    QJsonDocument doc(jsonObject);
    return doc.toJson();
}

QByteArray Server::handle_get_screen_capture_request(){
    QByteArray response;
    for(int i {0}; i < 2048; i++){
        response.append(chip8->get_display()[i]);
    }
    return response;
}

QByteArray Server::handle_publish_text_request(QJsonObject request){
    console->moveCursor(QTextCursor::End);
    console->appendHtml("<div>" + request.value("text").toString() + "</div>");
    console->moveCursor (QTextCursor::End);
    return SUCCESS_RESPONSE;
}

QByteArray Server::handle_publish_command_request(QJsonObject request){
    QString command_key = request.value("command_key").toString();
    QString command_action = request.value("command_action").toString();
    CHIP8::KeyStrokes key = Utils::convert_to_keystroke(command_key);

    // Making sure that the client didn't send bogus input
    if(key == CHIP8::key_F && command_key != "F"){
        return "ERROR: Command key not recognized";
    }

    if(command_action == "PRESS"){
        chip8->press_key(key);
    }
    else if(command_action == "RELEASE"){
        chip8->release_key(key);
    }
    else{
        return "ERROR: Command action not recognized";
    }

    return SUCCESS_RESPONSE;
}

void Server::append_message_to_console(QString message){
    console->moveCursor(QTextCursor::End);
    console->appendHtml("<div style='color: #8B8000;'> [SERVER] " + message + "</div>");
    console->moveCursor (QTextCursor::End);
}
