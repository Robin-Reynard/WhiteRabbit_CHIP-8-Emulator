#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMessageBox>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QString>
#include <QList>
#include <QtNetwork>
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QPlainTextEdit>
#include "utils.h"
#include "chip8.h"
#include "ui_dualwindow.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    const QByteArray SUCCESS_RESPONSE = ":3";

    void start_server(QLabel* image_slot, QPlainTextEdit* console, CHIP8* chip8);

    QTcpServer *tcp_server = nullptr;

public slots:
    void establish_client_connection();
    void parse_client_request();

private:
    QTcpSocket* client_connection {nullptr};
    CHIP8* chip8 {nullptr};
    QLabel* image_slot {nullptr};
    QPlainTextEdit* console {nullptr};



    QByteArray handle_get_screen_capture_request();
    QByteArray handle_get_chip8_info_request();
    QByteArray handle_publish_image_request(QJsonObject request);
    QByteArray handle_publish_text_request(QJsonObject request);
    QByteArray handle_publish_command_request(QJsonObject request);


    void append_message_to_console(QString message);
};

#endif // SERVER_H
