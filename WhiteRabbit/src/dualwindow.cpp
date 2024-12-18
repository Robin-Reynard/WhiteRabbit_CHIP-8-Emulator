#include "dualwindow.h"
#include "ui_dualwindow.h"

DualWindow::DualWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DualWindow)
{
    ui->setupUi(this);
}

DualWindow::~DualWindow()
{
    delete ui;
}
