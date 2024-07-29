#include "keyboard.h"

/*namespace Keyboard {
void on_key_pressed(QPushButton *button, CHIP8 *chip8){
    auto buttonText = button->text().toStdString();
    if(buttonText == "0"){
        chip8->press_key(CHIP8::KeyStrokes::key_0);
    }
    else if (buttonText == "1"){
        chip8->press_key(CHIP8::KeyStrokes::key_1);
    }
    else if (buttonText == "2")        {
        chip8->press_key(CHIP8::KeyStrokes::key_2);
    }
    else if (buttonText == "3"){
        chip8->press_key(CHIP8::KeyStrokes::key_3);
    }
    else if (buttonText == "4"){
        chip8->press_key(CHIP8::KeyStrokes::key_4);
    }
    else if (buttonText == "5"){
        chip8->press_key(CHIP8::KeyStrokes::key_5);
    }
    else if (buttonText == "6"){
        chip8->press_key(CHIP8::KeyStrokes::key_6);
    }
    else if (buttonText == "7"){
        chip8->press_key(CHIP8::KeyStrokes::key_7);
    }
    else if (buttonText == "8"){
        chip8->press_key(CHIP8::KeyStrokes::key_8);
    }
    else if (buttonText == "9"){
        chip8->press_key(CHIP8::KeyStrokes::key_9);
    }
    else if (buttonText == "A"){
        chip8->press_key(CHIP8::KeyStrokes::key_A);
    }
    else if (buttonText == "B"){
        chip8->press_key(CHIP8::KeyStrokes::key_B);
    }
    else if (buttonText == "C"){
        chip8->press_key(CHIP8::KeyStrokes::key_C);
    }
    else if (buttonText == "D"){
        chip8->press_key(CHIP8::KeyStrokes::key_D);
    }
    else if (buttonText == "E"){
        chip8->press_key(CHIP8::KeyStrokes::key_E);
    }
    else if (buttonText == "F"){
        chip8->press_key(CHIP8::KeyStrokes::key_F);
    }
}

}*/

/*void Keyboard::keyPressEvent(QKeyEvent *event)
{
    std::cout << event->key() << std::endl;

}

CHIP8::KeyStrokes Keyboard::find_key(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_1:
            return CHIP8::KeyStrokes::key_1;
        case Qt::Key_2:
            return CHIP8::KeyStrokes::key_2;
        case Qt::Key_3:
            return CHIP8::KeyStrokes::key_3;
        case Qt::Key_4:
            return CHIP8::KeyStrokes::key_C;
        case Qt::Key_Q:
            return CHIP8::KeyStrokes::key_4;
        case Qt::Key_W:
            return CHIP8::KeyStrokes::key_5;
        case Qt::Key_E:
            return CHIP8::KeyStrokes::key_6;
        case Qt::Key_R:
            return CHIP8::KeyStrokes::key_D;
        case Qt::Key_A:
            return CHIP8::KeyStrokes::key_7;
        case Qt::Key_S:
            return CHIP8::KeyStrokes::key_8;
        case Qt::Key_D:
            return CHIP8::KeyStrokes::key_9;
        case Qt::Key_F:
            return CHIP8::KeyStrokes::key_E;
        case Qt::Key_Z:
            return CHIP8::KeyStrokes::key_A;
        case Qt::Key_X:
            return CHIP8::KeyStrokes::key_0;
        case Qt::Key_C:
            return CHIP8::KeyStrokes::key_B;
        case Qt::Key_V:
            return CHIP8::KeyStrokes::key_F;
        }
    return NULL;
}

void Keyboard::apply_key_action(CHIP8::KeyStrokes key, bool is_pressed){

}*/
