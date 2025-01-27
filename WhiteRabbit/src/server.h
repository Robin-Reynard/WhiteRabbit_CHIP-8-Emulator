#ifndef SERVER_H
#define SERVER_H

#include <QLabel>
#include <QMessageBox>
#include <QTcpServer>
#include <QtNetwork>
#include <QPlainTextEdit>
#include "utils.h"
#include "chip8.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    // This might be a bit silly like response but I love it :3
    const QByteArray SUCCESS_RESPONSE = ":3";

    // Creates TCP server and awaits client connection
    void start_server(QLabel* image_slot, QPlainTextEdit* console, CHIP8* chip8);

public slots:
    // Handles inital client connection and awaits client request
    void establish_client_connection();
    // Handles client requests and returns response
    void parse_client_request();

private:
    QTcpServer *tcp_server {nullptr};
    QTcpSocket* client_connection {nullptr};
    CHIP8* chip8 {nullptr};
    // Display-related objects
    QLabel* image_slot {nullptr};
    QPlainTextEdit* console {nullptr};

    /* Handlers for every type of request */
    // Responds with the chip8's current graphics information as a 1D array
    QByteArray handle_get_screen_capture_request();
    // Responds with the chip8's keyboard and sound information
    QByteArray handle_get_chip8_info_request();
    // Handles a chip8 button press/release
    QByteArray handle_publish_command_request(QJsonObject request);

    // Displays incoming image from the client
    QByteArray handle_publish_image_request(QJsonObject request);
    // Displays incoming text from the client
    QByteArray handle_publish_text_request(QJsonObject request);

    // Displays server message on screen
    void append_message_to_console(QString message);
};

#endif // SERVER_H
