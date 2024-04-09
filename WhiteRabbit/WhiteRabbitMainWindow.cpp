#include "WhiteRabbitMainWindow.h"
#include "ui_WhiteRabbitMainWindow.h"
#include "chip8.h"

WhiteRabbitMainWindow::WhiteRabbitMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WhiteRabbitMainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Hello World\n");


    CHIP8 mychip = CHIP8();
}

WhiteRabbitMainWindow::~WhiteRabbitMainWindow()
{
    delete ui;
}

