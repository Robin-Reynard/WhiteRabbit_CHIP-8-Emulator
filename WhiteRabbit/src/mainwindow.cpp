#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chip8.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    


    CHIP8 mychip = CHIP8();
    mychip.load_program({"/home/robin/Desktop/Chip8 Games/INVADERS"});
    for(int i {0}; i < 200; i++){
        std::cout << i << std::endl;
        mychip.emulate_cycle();
    }

    ui->label->setText("Hello World\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

