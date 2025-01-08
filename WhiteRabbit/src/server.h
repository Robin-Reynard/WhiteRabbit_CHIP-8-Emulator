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
#include "chip8.h"
#include "ui_dualwindow.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void start_server(Ui::DualWindow* ui, CHIP8* chip8);

    QTcpServer *tcp_server = nullptr;

public slots:
    void establish_client_connection();
    void parse_client_request();

private:
    QTcpSocket* client_connection = nullptr;
    Ui::DualWindow *ui = nullptr;
    CHIP8 *chip8 = nullptr;

    void append_message_to_console(QString message);
    void publish_text_to_console(QString message);
};

#endif // SERVER_H
