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
#include "keyboard.h"
#include "assets.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void keyPressEvent(QKeyEvent* event) override;
    //void keyReleaseEvent(QKeyEvent *event) override;
    void run_emulator();

public slots:
    void load_new_program();
    void set_delay(int delay);
    //void on_virtual_keyboard_key_pressed();
    //void on_virtual_keyboard_key_released();


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
    void set_program_speed_message(int ms_delay);
    void on_keyboard_key_event(QKeyEvent *event, bool is_key_pressed);

    void set_button_pressed(QPushButton *button);
    void set_button_released(QPushButton *button);

    void set_rabbit_quote(const QString quote);
    void set_rabbit_icon(const QString icon);
};
#endif // MAINWINDOW_H
