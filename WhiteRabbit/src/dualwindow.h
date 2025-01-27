#ifndef DUALWINDOW_H
#define DUALWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include "chip8.h"
#include "server.h"

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
    void on_load_button_clicked();
    void on_play_pause_button_clicked();
    void on_delay_spin_valueChanged(int arg1);
    void on_reset_button_clicked();
    void keyboard_button_pressed();
    void keyboard_button_released();

private:
    Ui::DualWindow *ui;
    QGraphicsRectItem *pixels [32*64];
    QGraphicsScene* scene;
    CHIP8 *chip8;
    Server *server;
    QElapsedTimer timer;

    static const int TARGET_FPS_SPEED = 16;

    int board_rows {32};
    int board_columns {64};
    int pixel_size {8};

    bool is_emulation_paused {false};
    uint ms_delay_between_instructions {0};

    std::string current_chip8_program_path {"../../white_rabbit.ch8"};


    void run_next_instruction();
    void draw_pixels_to_screen();
};

#endif // DUALWINDOW_H
