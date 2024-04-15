#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chip8.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ui->label->setText("Hello World\n");


    CHIP8 mychip = CHIP8();
    mychip.load_program({"/home/robin/Desktop/Chip8 Games/INVADERS"});
    mychip.emulate_cycle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

