#include "mainwindow.h"
#include "screendisplay.h"
#include "chip8.h"
#include "debugdisplay.h"

#include <QApplication>
#include <thread>
#include <chrono>

#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    CHIP8 *mychip = new CHIP8();
    mychip->load_program({"/home/robin/Desktop/Chip8 Games/INVADERS"});

    //Display using SDL2 library
    //DebugDisplay* display = new DebugDisplay(mychip);

    //Display using QApplication
    QApplication a(argc, argv);
    ScreenDisplay *display = new ScreenDisplay(mychip);
    display->show();

    while(display->isVisible())
    {
        a.processEvents();
        std::this_thread::sleep_for(std::chrono::nanoseconds(500000));
        mychip->emulate_cycle();
        display->updateDisplay(mychip->get_display());
    }

    //GameDisplay display;
    //display.show();
    //MainWindow w;
    //w.show();

}
