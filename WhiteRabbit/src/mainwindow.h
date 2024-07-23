#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <string>
#include <thread>
#include <chrono>
#include "chip8.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void run_emulator();

public slots:
    void load_new_program();
    void on_virtual_keyboard_key_pressed();


private:
    Ui::MainWindow *ui;
    QGraphicsRectItem *pixels [32*64];
    QGraphicsScene* scene;
    CHIP8 *chip8;

    int board_rows {32};
    int board_columns {64};
    int pixel_size {13};

    void run_next_instruction();
    void set_current_program_label(QString program_name);
};
#endif // MAINWINDOW_H
