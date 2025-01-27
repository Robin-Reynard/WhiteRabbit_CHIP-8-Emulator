#include "dualwindow.h"
#include "ui_dualwindow.h"

DualWindow::DualWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DualWindow)
    , pixels {}
    , chip8(new CHIP8)
    , server(new Server)
{
    ui->setupUi(this);
    setup_keyboard_signals();

    // Set emulator visuals
    scene = new QGraphicsScene(ui->display);
    ui->display->setScene(scene);
    ui->display->setFixedSize(PIXEL_SIZE * BOARD_COLUMNS + 2, PIXEL_SIZE * BOARD_ROWS + 2);
    for(int i {0}; i < BOARD_ROWS; i++){
      for(int j {0}; j < BOARD_COLUMNS; j++){
          pixels[i * 64 + j] = scene ->addRect(j * PIXEL_SIZE, i * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, QPen(), QBrush(Qt::black));
      }
    }

    // Load default chip8 program
    chip8 = new CHIP8({current_chip8_program_path});

    // Start server
    server->start_server(ui->image_output, ui->console, chip8);
}

void DualWindow::emulate_next_instruction(){
    if (is_emulation_paused){
        return;
    }

    // Run a chip8 instruction
    chip8->execute_next_opcode();

    // Draw to screen if available
    if (chip8->new_drawing_available){
        draw_pixels_to_screen();
        chip8->new_drawing_available = false;
    }

    // Sleep by user-set amount to control emulation speed
    std::this_thread::sleep_for(std::chrono::milliseconds(ms_delay_between_instructions));
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

//////////////////////// BUTTONS EVENTS ////////////////////////
void DualWindow::on_load_button_clicked()
{
    // Opens the file selection screen
    QString program_name {QFileDialog::getOpenFileName(this, "Select a CHIP8 ROM")};
    if(program_name.isEmpty()){
        return;
    }

    try{
        // Load new file
        current_chip8_program_path = program_name.toStdString();
        chip8 = new CHIP8({current_chip8_program_path});
        ui->chip_title->setText("Running " + QFileInfo(program_name).fileName());
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

void DualWindow::setup_keyboard_signals()
{
    connect(ui->button_0, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_1, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_2, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_3, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_4, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_5, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_6, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_7, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_8, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_9, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_A, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_B, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_C, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_D, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_E, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_F, SIGNAL(pressed()), this, SLOT(keyboard_button_pressed()));
    connect(ui->button_0, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_1, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_2, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_3, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_4, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_5, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_6, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_7, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_8, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_9, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_A, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_B, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_C, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_D, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_E, SIGNAL(released()), this, SLOT(keyboard_button_released()));
    connect(ui->button_F, SIGNAL(released()), this, SLOT(keyboard_button_released()));
}

void DualWindow::keyboard_button_pressed(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Utils::register_key_press(buttonSender->text(), chip8);
}

void DualWindow::keyboard_button_released(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    Utils::register_key_release(buttonSender->text(), chip8);
}
