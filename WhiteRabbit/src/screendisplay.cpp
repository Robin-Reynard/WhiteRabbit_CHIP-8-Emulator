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
            pixels[i * 64 + j] = scene ->addRect(j * pixel_size, i * pixel_size, board_columns, board_rows, QPen(), QBrush(Qt::yellow));
        }
    }

    scene -> setSceneRect(0,0,pixel_size * board_columns, pixel_size * board_rows);
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
            chip8->press_key(CHIP8::KeyStrokes::num_1);
            break;
    }
    QGraphicsView::keyPressEvent(event);
}
