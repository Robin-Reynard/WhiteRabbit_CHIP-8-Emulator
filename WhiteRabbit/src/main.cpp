#include "mainwindow.h"
#include "screendisplay.h"
#include "chip8.h"
#include "debugdisplay.h"

#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <thread>
#include <chrono>

#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    CHIP8 *mychip = new CHIP8();
    mychip->load_program({"../../white_rabbit.ch8"});
    //mychip->load_program({"/home/robin/Desktop/Chip8 Games/WIPEOFF"});

    //Display using SDL2 library
    //DebugDisplay* display = new DebugDisplay(mychip);

    //Display using QApplication
    /*QApplication a(argc, argv);
    ScreenDisplay *display = new ScreenDisplay(mychip);
    display->show();

    while(display->isVisible())
    {
        a.processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        mychip->emulate_cycle();
        display->updateDisplay(mychip->get_display());
    }*/

    //GameDisplay display;
    //display.show();

    QApplication a(argc, argv);

    for(auto name : QFontDatabase().families()){
        //QFont font("Courier New");
        qDebug() << name;
        QFont font(name);
        font.setStyleHint(QFont::Monospace);
        QApplication::setFont(font);
        MainWindow w;
        w.show();
        a.exec();
    }





}
