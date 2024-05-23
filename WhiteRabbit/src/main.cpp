#include "mainwindow.h"
#include "screendisplay.h"
#include "chip8.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenDisplay display;
    display.show();


    CHIP8 mychip = CHIP8();
    mychip.load_program({"/home/robin/Desktop/Chip8 Games/INVADERS"});
    for(int i {0}; i < 200; i++){
        std::cout << i << std::endl;
        mychip.emulate_cycle();
    }
    display.updateDisplay(mychip.get_display());
    //GameDisplay display;
    //display.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
