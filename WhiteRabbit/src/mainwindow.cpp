#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chip8.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ui->label->setText("Hello World\n");


    CHIP8 mychip = CHIP8();
    mychip.load_program();
}

MainWindow::~MainWindow()
{
    delete ui;
}

