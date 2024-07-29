#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pixels {}
    , chip8(new CHIP8)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->display);

    ui->display->setScene(scene);
    connect(ui->select_new_program_button, SIGNAL(clicked()), this, SLOT(load_new_program()));
    connect(ui->delay_spin, SIGNAL(valueChanged(int)), this, SLOT(set_delay(int)));

    /*connect(ui->key_0, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_1, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_2, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_3, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_4, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_5, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_6, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_7, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_8, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_9, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_A, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_B, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_C, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_D, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_E, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));
    connect(ui->key_F, SIGNAL(pressed()), this, SLOT(on_virtual_keyboard_key_pressed()));

    connect(ui->key_0, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_1, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_2, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_3, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_4, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_5, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_6, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_7, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_8, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_9, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_A, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_B, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_C, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_D, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_E, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));
    connect(ui->key_F, SIGNAL(released()), this, SLOT(on_virtual_keyboard_key_released()));*/




    //QGraphicsScene* scene = new QGraphicsScene(0,0,300,300, ui->display);
    //scene = new QGraphicsScene(this);
    //setScene(scene);

    for(int i {0}; i < board_rows; i++){
        for(int j {0}; j < board_columns; j++){
            pixels[i * 64 + j] = scene ->addRect(j * pixel_size, i * pixel_size, pixel_size, pixel_size, QPen(), QBrush(Qt::yellow));
        }
    }

    ui->display->setFixedSize(pixel_size * board_columns + 2, pixel_size * board_rows + 2);

    //ui->display->setSceneRect(0, 0, pixel_size * board_columns + 2, pixel_size * board_rows + 2);
    //ui->display->fitInView(0, 0, pixel_size * board_columns + 2, pixel_size * board_rows + 2, Qt::KeepAspectRatio);

    chip8->load_program({"../../white_rabbit.ch8"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_emulator(){
    run_next_instruction();
    //std::this_thread::sleep_for(std::chrono::milliseconds(3));
}

void MainWindow::run_next_instruction(){
    chip8->emulate_cycle();
    //ui->display->updateDisplay(chip8->get_display());
    for(int i {0}; i < 2048; i++){
        if(chip8->get_display()[i] == 0){
            pixels[i]->setBrush(Qt::black);
        }
        else{
            pixels[i]->setBrush(Qt::white);
        }
    }
}

void MainWindow::load_new_program(){
    QString program_name {QFileDialog::getOpenFileName(this, "Select a new program to run")};
    if(program_name.isEmpty()){
        return;
    }

    try{
        const QFileInfo info(program_name);
        //TODO REMOVE
        delete chip8;
        chip8 = new CHIP8();
        chip8->load_program(program_name.toStdString());
        set_current_program_label(QString(info.fileName()));
    }
    catch(const char* error_message){
        QMessageBox::warning(this, "Warning", "WhiteRabbit cannot open file (╥﹏╥): " + *error_message);
    }
}

void MainWindow::set_current_program_label(QString program_name){
    ui->title_label->setText("Running " + program_name);
}

void MainWindow::set_delay(int delay){
    chip8->set_delay_between_instructions(delay);
}

/*
void MainWindow::on_virtual_keyboard_key_pressed(){
    Keyboard::on_key_pressed(qobject_cast<QPushButton*>(sender()));
    /*QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
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
}

void MainWindow::on_virtual_keyboard_key_released(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    auto buttonText = buttonSender->text().toStdString();
    std::cout << buttonText << std::endl;
    if(buttonText == "0"){
        chip8->release_key(CHIP8::KeyStrokes::key_0);}
    else if (buttonText == "1"){
        chip8->release_key(CHIP8::KeyStrokes::key_1);}
    else if (buttonText == "2")        {
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

void MainWindow::keyPressEvent(QKeyEvent *event){
    on_keyboard_key_event(event, true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    on_keyboard_key_event(event, false);
}

void MainWindow::on_keyboard_key_event(QKeyEvent *event, bool is_key_pressed){
    /*switch(event->key()){
    case Qt::Key_1:
        if(is_key_pressed){
            chip8->press_key(CHIP8::KeyStrokes::key_1);
            set_button_pressed(ui->key_1);
        }
        else{
            chip8->release_key(CHIP8::KeyStrokes::key_1);
            set_button_released(ui->key_1);
        }
        break;
    case Qt::Key_2:
        if(is_key_pressed){
            chip8->press_key(CHIP8::KeyStrokes::key_2);
            set_button_pressed(ui->key_2);
        }
        else{
            chip8->release_key(CHIP8::KeyStrokes::key_2);
            set_button_released(ui->key_2);
        }
        break;
    case Qt::Key_3:
        if(is_key_pressed){
            chip8->press_key(CHIP8::KeyStrokes::key_3);
            set_button_pressed(ui->key_3);
        }
        else{
            chip8->release_key(CHIP8::KeyStrokes::key_3);
            set_button_released(ui->key_3);
        }
        break;
    case Qt::Key_4:
        if(is_key_pressed){
            chip8->press_key(CHIP8::KeyStrokes::key_4);
            set_button_pressed(ui->key_4);
        }
        else{
            chip8->release_key(CHIP8::KeyStrokes::key_4);
            set_button_released(ui->key_4);
        }
        break;
    case Qt::Key_Q:
        chip8->release_key(CHIP8::KeyStrokes::key_4); ui->key_4->setEnabled(!is_key_pressed); break;
    case Qt::Key_W:
        chip8->release_key(CHIP8::KeyStrokes::key_5); ui->key_5->setEnabled(!is_key_pressed); break;
    case Qt::Key_E:
        chip8->release_key(CHIP8::KeyStrokes::key_6); ui->key_6->setEnabled(!is_key_pressed); break;
    case Qt::Key_R:
        chip8->release_key(CHIP8::KeyStrokes::key_D); ui->key_D->setEnabled(!is_key_pressed); break;
    case Qt::Key_A:
        chip8->release_key(CHIP8::KeyStrokes::key_7); ui->key_7->setEnabled(!is_key_pressed); break;
    case Qt::Key_S:
        chip8->release_key(CHIP8::KeyStrokes::key_8); ui->key_8->setEnabled(!is_key_pressed); break;
    case Qt::Key_D:
        chip8->release_key(CHIP8::KeyStrokes::key_9); ui->key_9->setEnabled(!is_key_pressed); break;
    case Qt::Key_F:
        chip8->release_key(CHIP8::KeyStrokes::key_E); ui->key_E->setEnabled(!is_key_pressed); break;
    case Qt::Key_Z:
        chip8->release_key(CHIP8::KeyStrokes::key_A); ui->key_A->setEnabled(!is_key_pressed); break;
    case Qt::Key_X:
        chip8->release_key(CHIP8::KeyStrokes::key_0); ui->key_0->setEnabled(!is_key_pressed); break;
    case Qt::Key_C:
        chip8->release_key(CHIP8::KeyStrokes::key_B); ui->key_B->setEnabled(!is_key_pressed); break;
    case Qt::Key_V:
        chip8->release_key(CHIP8::KeyStrokes::key_F); ui->key_F->setEnabled(!is_key_pressed); break;
    }
}
/*
void MainWindow::set_button_pressed(QPushButton *button){
    button->setCheckable(true);
    button->setChecked(true);
}

void MainWindow::set_button_relased(QPushButton *button){
    button->setChecked(false);
    button->setCheckable(false);
}
*/
