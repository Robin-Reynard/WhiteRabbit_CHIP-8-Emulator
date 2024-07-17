#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chip8.h"
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pixels {}
    , chip8(new CHIP8)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->display);
    ui->display->setScene(scene);

    //QGraphicsScene* scene = new QGraphicsScene(0,0,300,300, ui->display);
    //scene = new QGraphicsScene(this);
    //setScene(scene);

    for(int i {0}; i < board_rows; i++){
        for(int j {0}; j < board_columns; j++){
            pixels[i * 64 + j] = scene ->addRect(j * pixel_size, i * pixel_size, pixel_size, pixel_size, QPen(), QBrush(Qt::yellow));
        }
    }

    ui->display->setFixedSize(pixel_size * board_columns + 2, pixel_size * board_rows + 2);
    //ui->display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //ui->display->setSceneRect(0, 0, pixel_size * board_columns + 2, pixel_size * board_rows + 2);
    //ui->display->fitInView(0, 0, pixel_size * board_columns + 2, pixel_size * board_rows + 2, Qt::KeepAspectRatio);

    //setFixedSize(pixel_size * board_columns + 2, pixel_size * board_rows + 2);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    chip8->load_program({"../../white_rabbit.ch8"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_next_instruction(){
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

/*void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}*/
//QMessageBox::warning(this, "Warning", "Cannot open file: ");
