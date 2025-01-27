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

void DualWindow::execute_frame(){
    // Restart the timer
    timer.restart();

    while (timer.elapsed() < TARGET_FPS_SPEED) {
        if (is_emulation_paused){
            continue;
        }
        // Run a chip8 instruction
        chip8->execute_next_opcode();
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

void DualWindow::keyboard_button_pressed(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    auto buttonText = buttonSender->text().toStdString();
    std::cout << buttonText << std::endl;
    if(buttonText == "0"){
        chip8->press_key(CHIP8::KeyStrokes::key_0);}
    else if (buttonText == "1"){
        chip8->press_key(CHIP8::KeyStrokes::key_1);}
    else if (buttonText == "2")        {
        chip8->press_key(CHIP8::KeyStrokes::key_2);}
    else if (buttonText == "3"){
        chip8->press_key(CHIP8::KeyStrokes::key_3);}
    else if (buttonText == "4"){
        chip8->press_key(CHIP8::KeyStrokes::key_4);}
    else if (buttonText == "5"){
        chip8->press_key(CHIP8::KeyStrokes::key_5);}
    else if (buttonText == "6"){
        chip8->press_key(CHIP8::KeyStrokes::key_6);}
    else if (buttonText == "7"){
        chip8->press_key(CHIP8::KeyStrokes::key_7);}
    else if (buttonText == "8"){
        chip8->press_key(CHIP8::KeyStrokes::key_8);}
    else if (buttonText == "9"){
        chip8->press_key(CHIP8::KeyStrokes::key_9);}
    else if (buttonText == "A"){
        chip8->press_key(CHIP8::KeyStrokes::key_A); }
    else if (buttonText == "B"){
        chip8->press_key(CHIP8::KeyStrokes::key_B);}
    else if (buttonText == "C"){
        chip8->press_key(CHIP8::KeyStrokes::key_C); }
    else if (buttonText == "D"){
        chip8->press_key(CHIP8::KeyStrokes::key_D);}
    else if (buttonText == "E"){
        chip8->press_key(CHIP8::KeyStrokes::key_E);}
    else if (buttonText == "F"){
        chip8->press_key(CHIP8::KeyStrokes::key_F); }

    qDebug() << chip8->get_keyboard();
}

void DualWindow::keyboard_button_released(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    auto buttonText = buttonSender->text().toStdString();
    std::cout << buttonText << std::endl;
    if(buttonText == "0"){
        chip8->release_key(CHIP8::KeyStrokes::key_0);}
    else if (buttonText == "1"){
        chip8->release_key(CHIP8::KeyStrokes::key_1);}
    else if (buttonText == "2"){
        chip8->release_key(CHIP8::KeyStrokes::key_2);}
    else if (buttonText == "3"){
        chip8->release_key(CHIP8::KeyStrokes::key_3);}
    else if (buttonText == "4"){
        chip8->release_key(CHIP8::KeyStrokes::key_4);}
    else if (buttonText == "5"){
        chip8->release_key(CHIP8::KeyStrokes::key_5);}
    else if (buttonText == "6"){
        chip8->release_key(CHIP8::KeyStrokes::key_6);}
    else if (buttonText == "7"){
        chip8->release_key(CHIP8::KeyStrokes::key_7);}
    else if (buttonText == "8"){
        chip8->release_key(CHIP8::KeyStrokes::key_8);}
    else if (buttonText == "9"){
        chip8->release_key(CHIP8::KeyStrokes::key_9);}
    else if (buttonText == "A"){
        chip8->release_key(CHIP8::KeyStrokes::key_A); }
    else if (buttonText == "B"){
        chip8->release_key(CHIP8::KeyStrokes::key_B);}
    else if (buttonText == "C"){
        chip8->release_key(CHIP8::KeyStrokes::key_C); }
    else if (buttonText == "D"){
        chip8->release_key(CHIP8::KeyStrokes::key_D);}
    else if (buttonText == "E"){
        chip8->release_key(CHIP8::KeyStrokes::key_E);}
    else if (buttonText == "F"){
        chip8->release_key(CHIP8::KeyStrokes::key_F); }
}

