#include "dualwindow.h"
#include "ui_dualwindow.h"
#include <QtNetwork>


DualWindow::DualWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DualWindow)
    , pixels {}
    , chip8(new CHIP8)
    , server(new Server)
{
    ui->setupUi(this);

    // Set emulator visuals
    scene = new QGraphicsScene(ui->display);
    ui->display->setScene(scene);
    ui->display->setFixedSize(pixel_size * board_columns + 2, pixel_size * board_rows + 2);
    for(int i {0}; i < board_rows; i++){
      for(int j {0}; j < board_columns; j++){
          pixels[i * 64 + j] = scene ->addRect(j * pixel_size, i * pixel_size, pixel_size, pixel_size, QPen(), QBrush(Qt::black));
      }
    }

    // Load default chip8 program
    chip8 = new CHIP8({current_chip8_program_path});

    // Start the timer that ensures CHIP8 runs at 60FPS
    timer.start();

    // Start server
    server->start_server(ui->image_output, ui->console, chip8);
}

void DualWindow::run_emulator(){
    run_next_instruction();
}

void DualWindow::run_next_instruction(){
    // Restart the timer
    timer.restart();

    while (timer.elapsed() < TARGET_FPS_SPEED) {
        if (is_emulation_paused){
            continue;
        }
        // Run a chip8 instruction
        chip8->emulate_cycle();
        // Draw to screen if available
        if (chip8->new_drawing_available){
            draw_pixels_to_screen();
            chip8->new_drawing_available = false;
        }
        // Sleep by user-set amount
        std::this_thread::sleep_for(std::chrono::milliseconds(ms_delay_between_instructions));
    }
}

void DualWindow::draw_pixels_to_screen(){
    for(int i {0}; i < 2048; i++){
        if(chip8->get_display()[i] == 0){
            pixels[i]->setBrush(Qt::black);
        }
        else{
            pixels[i]->setBrush(Qt::white);
        }
    }
}

DualWindow::~DualWindow()
{
    delete ui;
    delete chip8;
    delete server;
}
/////////////////// BUTTONS
void DualWindow::on_load_button_clicked()
{
    QString program_name {QFileDialog::getOpenFileName(this, "Select a CHIP8 ROM")};
    if(program_name.isEmpty()){
        return;
    }

    try{
        // TODO
        const QFileInfo info(program_name);
        current_chip8_program_path = program_name.toStdString();
        chip8 = new CHIP8({current_chip8_program_path});
        ui->chip_title->setText("Running " + QString(info.fileName()));
    }
    catch(const char* error_message){
        QMessageBox::warning(this, "Warning", "WhiteRabbit cannot open file (╥﹏╥): " + *error_message);
    }
}

void DualWindow::on_play_pause_button_clicked()
{
    if(is_emulation_paused){
        ui->play_pause_button->setText("Pause");
        is_emulation_paused = false;
    }
    else{
        ui->play_pause_button->setText("Play");
        is_emulation_paused = true;
    }
}

void DualWindow::on_delay_spin_valueChanged(int arg1)
{
    ms_delay_between_instructions = arg1;
}

void DualWindow::on_reset_button_clicked()
{
    chip8 = new CHIP8({current_chip8_program_path});
}
