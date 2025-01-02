#include "dualwindow.h"
#include "ui_dualwindow.h"
#include <QtNetwork>


DualWindow::DualWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DualWindow)
    , pixels {}
    , chip8(new CHIP8)
    , server(new Server)
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

    server->start_server(ui, chip8);
    connect(server->tcp_server, &QTcpServer::newConnection, server, &Server::establish_client_connection);
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

DualWindow::~DualWindow()
{
    delete ui;
    delete chip8;
    delete server;
}
