#ifndef DUALWINDOW_H
#define DUALWINDOW_H

#include <QGraphicsRectItem>
#include <QFileDialog>
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

    // Decode and execute instruction & updates the CHIP8 display
    void emulate_next_instruction();


private slots:
    // Allows user to select a new CHIP8 ROM to run
    void on_load_button_clicked();

    // Allows to start/stop emulation
    void on_play_pause_button_clicked();

    // Allows the user to select a delay between instructions
    void on_delay_spin_valueChanged(int arg1);

    // Resets the current emulation
    void on_reset_button_clicked();

    // Keyboard events handlers
    void keyboard_button_pressed();
    void keyboard_button_released();

private:
    Ui::DualWindow *ui;
    QGraphicsRectItem *pixels [32*64];
    QGraphicsScene* scene;
    CHIP8 *chip8;
    Server *server;

    // Consts for CHIP8 display
    static const int BOARD_ROWS {32};
    static const int BOARD_COLUMNS {64};
    static const int PIXEL_SIZE {8};

    // User emulation setting variables
    bool is_emulation_paused {false};
    uint ms_delay_between_instructions {0};
    std::string current_chip8_program_path {"../../white_rabbit.ch8"};

    // Sets up all pressed() and released() signals and slots
    void setup_keyboard_signals();
    // Draws the value of the CHIP8 graphics onto the display
    void draw_pixels_to_screen();
};

#endif // DUALWINDOW_H
