#ifndef DUALWINDOW_H
#define DUALWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QString>
#include <QList>
#include <string>
#include <thread>
#include <chrono>
#include "chip8.h"
namespace Ui {
class DualWindow;
}

class DualWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DualWindow(QWidget *parent = nullptr);
    ~DualWindow();
    void run_emulator();

private slots:
    void sendFortune();

private:
    Ui::DualWindow *ui;
    QGraphicsRectItem *pixels [32*64];
    QGraphicsScene* scene;
    CHIP8 *chip8;
    QTcpServer *tcpServer = nullptr;

    int board_rows {32};
    int board_columns {64};
    int pixel_size {6};
    QList<QString> fortunes;

    void run_next_instruction();
    void initServer();
};

#endif // DUALWINDOW_H
