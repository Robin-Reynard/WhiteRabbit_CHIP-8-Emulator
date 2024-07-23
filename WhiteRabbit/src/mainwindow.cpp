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
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
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

void MainWindow::on_virtual_keyboard_key_pressed(){

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    switch(event->key()){
    case Qt::Key_1:
        chip8->press_key(CHIP8::KeyStrokes::key_1); ui->key_1->setChecked(true); break;
    case Qt::Key_2:
        chip8->press_key(CHIP8::KeyStrokes::key_2); ui->key_2->setChecked(true); break;
    case Qt::Key_3:
        chip8->press_key(CHIP8::KeyStrokes::key_3); ui->key_3->setChecked(true); break;
    case Qt::Key_4:
        chip8->press_key(CHIP8::KeyStrokes::key_C); ui->key_C->setChecked(true); break;
    case Qt::Key_Q:
        chip8->press_key(CHIP8::KeyStrokes::key_4); ui->key_4->setChecked(true); break;
    case Qt::Key_W:
        chip8->press_key(CHIP8::KeyStrokes::key_5); ui->key_5->setChecked(true); break;
    case Qt::Key_E:
        chip8->press_key(CHIP8::KeyStrokes::key_6); ui->key_6->setChecked(true); break;
    case Qt::Key_R:
        chip8->press_key(CHIP8::KeyStrokes::key_D); ui->key_D->setChecked(true); break;
    case Qt::Key_A:
        chip8->press_key(CHIP8::KeyStrokes::key_7); ui->key_7->setChecked(true); break;
    case Qt::Key_S:
        chip8->press_key(CHIP8::KeyStrokes::key_8); ui->key_8->setChecked(true); break;
    case Qt::Key_D:
        chip8->press_key(CHIP8::KeyStrokes::key_9); ui->key_9->setChecked(true); break;
    case Qt::Key_F:
        chip8->press_key(CHIP8::KeyStrokes::key_E); ui->key_E->setChecked(true); break;
    case Qt::Key_Z:
        chip8->press_key(CHIP8::KeyStrokes::key_A); ui->key_A->setChecked(true); break;
    case Qt::Key_X:
        chip8->press_key(CHIP8::KeyStrokes::key_0); ui->key_0->setChecked(true); break;
    case Qt::Key_C:
        chip8->press_key(CHIP8::KeyStrokes::key_B); ui->key_B->setChecked(true); break;
    case Qt::Key_V:
        chip8->press_key(CHIP8::KeyStrokes::key_F); ui->key_F->setChecked(true); break;
    }
    //QGraphicsView::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    switch(event->key()){
    case Qt::Key_1:
        chip8->release_key(CHIP8::KeyStrokes::key_1); ui->key_1->setChecked(false); break;
    case Qt::Key_2:
        chip8->release_key(CHIP8::KeyStrokes::key_2); ui->key_2->setChecked(false); break;
    case Qt::Key_3:
        chip8->release_key(CHIP8::KeyStrokes::key_3); ui->key_3->setChecked(false); break;
    case Qt::Key_4:
        chip8->release_key(CHIP8::KeyStrokes::key_C); ui->key_C->setChecked(false); break;
    case Qt::Key_Q:
        chip8->release_key(CHIP8::KeyStrokes::key_4); ui->key_4->setChecked(false); break;
    case Qt::Key_W:
        chip8->release_key(CHIP8::KeyStrokes::key_5); ui->key_5->setChecked(false); break;
    case Qt::Key_E:
        chip8->release_key(CHIP8::KeyStrokes::key_6); ui->key_6->setChecked(false); break;
    case Qt::Key_R:
        chip8->release_key(CHIP8::KeyStrokes::key_D); ui->key_D->setChecked(false); break;
    case Qt::Key_A:
        chip8->release_key(CHIP8::KeyStrokes::key_7); ui->key_7->setChecked(false); break;
    case Qt::Key_S:
        chip8->release_key(CHIP8::KeyStrokes::key_8); ui->key_8->setChecked(false); break;
    case Qt::Key_D:
        chip8->release_key(CHIP8::KeyStrokes::key_9); ui->key_9->setChecked(false); break;
    case Qt::Key_F:
        chip8->release_key(CHIP8::KeyStrokes::key_E); ui->key_E->setChecked(false); break;
    case Qt::Key_Z:
        chip8->release_key(CHIP8::KeyStrokes::key_A); ui->key_A->setChecked(false); break;
    case Qt::Key_X:
        chip8->release_key(CHIP8::KeyStrokes::key_0); ui->key_0->setChecked(false); break;
    case Qt::Key_C:
        chip8->release_key(CHIP8::KeyStrokes::key_B); ui->key_B->setChecked(false); break;
    case Qt::Key_V:
        chip8->release_key(CHIP8::KeyStrokes::key_F); ui->key_F->setChecked(false); break;
    }
    //QGraphicsView::keyReleaseEvent(event);
}
