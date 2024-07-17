#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chip8.h"
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    CHIP8 *mychip = new CHIP8();
    mychip->load_program({"../../white_rabbit.ch8"});

    for(int i {0}; i< 50; i++ )
    {
        mychip->emulate_cycle();
        //display->updateDisplay(mychip->get_display());
    }

    //ui->label->setText("Hello World\n");
    QMessageBox::warning(this, "Warning", "Cannot open file: ");


    QGraphicsScene* scene = new QGraphicsScene(0,0,300,300, ui->graphicsView);
    ui->graphicsView->setScene(scene);
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
MainWindow::~MainWindow()
{
    delete ui;
}

