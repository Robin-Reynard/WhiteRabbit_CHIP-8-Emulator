#include "mainwindow.h"
#include "screendisplay.h"
#include "chip8.h"
#include "debugdisplay.h"

#include <QApplication>
#include <thread>
#include <chrono>

#include <SDL2/SDL.h>

int main()
{
    CHIP8 *mychip = new CHIP8();
    mychip->load_program({"/home/robin/Desktop/Chip8 Games/INVADERS"});

    DebugDisplay* display = new DebugDisplay(mychip);
    /*QApplication a(argc, argv);


    ScreenDisplay *display = new ScreenDisplay(mychip);
    display->show();

    for(int i {0}; i < 100; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
        mychip->emulate_cycle();
        display->updateDisplay(mychip->get_display());
        display->update();

    }

    //GameDisplay display;
    //display.show();
    //MainWindow w;
    //w.show();
    return a.exec();*/
}
