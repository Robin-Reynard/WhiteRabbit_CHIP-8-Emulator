#include "mainwindow.h"
#include "screendisplay.h"
#include "chip8.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    CHIP8 *mychip = new CHIP8();
    mychip->load_program({"/home/robin/Desktop/Chip8 Games/test_opcode.ch8"});

    ScreenDisplay *display = new ScreenDisplay(mychip);
    display->show();


    for(int i {0}; i < 900; i++){
        mychip->emulate_cycle();
        display->updateDisplay(mychip->get_display());
    }

    //GameDisplay display;
    //display.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
