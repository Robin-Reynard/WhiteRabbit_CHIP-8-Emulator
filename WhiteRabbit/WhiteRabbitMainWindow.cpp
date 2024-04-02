#include "WhiteRabbitMainWindow.h"
#include "ui_WhiteRabbitMainWindow.h"

WhiteRabbitMainWindow::WhiteRabbitMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WhiteRabbitMainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Hello World\n");
}

WhiteRabbitMainWindow::~WhiteRabbitMainWindow()
{
    delete ui;
}

