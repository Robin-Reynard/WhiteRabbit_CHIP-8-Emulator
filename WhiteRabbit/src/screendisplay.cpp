#include "screendisplay.h"

ScreenDisplay::ScreenDisplay(CHIP8* chip8, QWidget* parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    int board_rows {32};
    int board_columns {64};
    int pixel_size {20};

    for(int i {0}; i < board_rows; i++){
        for(int j {0}; j < board_columns; j++){
            pixels[i * 64 + j] = scene ->addRect(j * pixel_size, i * pixel_size, pixel_size, pixel_size, QPen(), QBrush(Qt::yellow));
        }
    }

    setFixedSize(pixel_size * board_columns + 2, pixel_size * board_rows + 2);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->chip8 = chip8;
}

void ScreenDisplay::updateDisplay(bool chip8_graphics[]){
    for(int i {0}; i < 2048; i++){
        if(chip8_graphics[i] == 0){
            pixels[i]->setBrush(Qt::black);
        }
        else{
            pixels[i]->setBrush(Qt::white);
        }
    }
}

void ScreenDisplay::keyPressEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    switch(event->key()){
    case Qt::Key_1:
        chip8->key_pressed(CHIP8::KeyStrokes::num_1); break;
    case Qt::Key_2:
        chip8->key_pressed(CHIP8::KeyStrokes::num_2); break;
    case Qt::Key_3:
        chip8->key_pressed(CHIP8::KeyStrokes::num_3); break;
    case Qt::Key_4:
        chip8->key_pressed(CHIP8::KeyStrokes::C); break;
    case Qt::Key_Q:
        chip8->key_pressed(CHIP8::KeyStrokes::num_4); break;
    case Qt::Key_W:
        chip8->key_pressed(CHIP8::KeyStrokes::num_5); break;
    case Qt::Key_E:
        chip8->key_pressed(CHIP8::KeyStrokes::num_6); break;
    case Qt::Key_R:
        chip8->key_pressed(CHIP8::KeyStrokes::D); break;
    case Qt::Key_A:
        chip8->key_pressed(CHIP8::KeyStrokes::num_7); break;
    case Qt::Key_S:
        chip8->key_pressed(CHIP8::KeyStrokes::num_8); break;
    case Qt::Key_D:
        chip8->key_pressed(CHIP8::KeyStrokes::num_9); break;
    case Qt::Key_F:
        chip8->key_pressed(CHIP8::KeyStrokes::E); break;
    case Qt::Key_Z:
        chip8->key_pressed(CHIP8::KeyStrokes::A); break;
    case Qt::Key_X:
        chip8->key_pressed(CHIP8::KeyStrokes::num_0); break;
    case Qt::Key_C:
        chip8->key_pressed(CHIP8::KeyStrokes::B); break;
    case Qt::Key_V:
        chip8->key_pressed(CHIP8::KeyStrokes::F); break;
    }
    QGraphicsView::keyPressEvent(event);
}

void ScreenDisplay::keyReleaseEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    switch(event->key()){
    case Qt::Key_1:
        chip8->key_lifted(CHIP8::KeyStrokes::num_1); break;
    case Qt::Key_2:
        chip8->key_lifted(CHIP8::KeyStrokes::num_2); break;
    case Qt::Key_3:
        chip8->key_lifted(CHIP8::KeyStrokes::num_3); break;
    case Qt::Key_4:
        chip8->key_lifted(CHIP8::KeyStrokes::C); break;
    case Qt::Key_Q:
        chip8->key_lifted(CHIP8::KeyStrokes::num_4); break;
    case Qt::Key_W:
        chip8->key_lifted(CHIP8::KeyStrokes::num_5); break;
    case Qt::Key_E:
        chip8->key_lifted(CHIP8::KeyStrokes::num_6); break;
    case Qt::Key_R:
        chip8->key_lifted(CHIP8::KeyStrokes::D); break;
    case Qt::Key_A:
        chip8->key_lifted(CHIP8::KeyStrokes::num_7); break;
    case Qt::Key_S:
        chip8->key_lifted(CHIP8::KeyStrokes::num_8); break;
    case Qt::Key_D:
        chip8->key_lifted(CHIP8::KeyStrokes::num_9); break;
    case Qt::Key_F:
        chip8->key_lifted(CHIP8::KeyStrokes::E); break;
    case Qt::Key_Z:
        chip8->key_lifted(CHIP8::KeyStrokes::A); break;
    case Qt::Key_X:
        chip8->key_lifted(CHIP8::KeyStrokes::num_0); break;
    case Qt::Key_C:
        chip8->key_lifted(CHIP8::KeyStrokes::B); break;
    case Qt::Key_V:
        chip8->key_lifted(CHIP8::KeyStrokes::F); break;
    }
    QGraphicsView::keyReleaseEvent(event);
}
