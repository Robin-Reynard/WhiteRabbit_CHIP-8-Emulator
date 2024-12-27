#include "dualwindow.h"
#include "ui_dualwindow.h"
#include <QtNetwork>


DualWindow::DualWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DualWindow)
    , pixels {}
    , chip8(new CHIP8)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->display);

    ui->display->setScene(scene);

    for(int i {0}; i < board_rows; i++){
      for(int j {0}; j < board_columns; j++){
          pixels[i * 64 + j] = scene ->addRect(j * pixel_size, i * pixel_size, pixel_size, pixel_size, QPen(), QBrush(Qt::yellow));
      }
    }
    ui->display->setFixedSize(pixel_size * board_columns + 2, pixel_size * board_rows + 2);
    chip8->load_program({"../../white_rabbit.ch8"});

    initServer();
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
                 << tr("You've got to think about tomorrow.")
                 << tr("You will be surprised by a loud noise.")
                 << tr("You will feel hungry again in another hour.")
                 << tr("You might have mail.")
                 << tr("You cannot kill time without injuring eternity.")
                 << tr("Computers are not intelligent. They only think they are.");
    connect(tcpServer, &QTcpServer::newConnection, this, &DualWindow::sendFortune);
}

void DualWindow::run_emulator(){
    run_next_instruction();
}

void DualWindow::run_next_instruction(){
    chip8->emulate_cycle();
    //ui->display->updateDisplay(chip8->get_display());
    for(int i {0}; i < 2048; i++){
        if(chip8->get_display()[i] == 0){
            pixels[i]->setBrush(Qt::black);
        }
        else{
            pixels[i]->setBrush(Qt::white);
        }
    }
}

void DualWindow::initServer(){
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
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
    ui->image_output->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the Fortune Client example now.")
                         .arg(ipAddress).arg(tcpServer->serverPort()));
}

void DualWindow::sendFortune(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_6_5);

    out << fortunes[QRandomGenerator::global()->bounded(fortunes.size())];

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}

DualWindow::~DualWindow()
{
    delete ui;
    delete chip8;
}
