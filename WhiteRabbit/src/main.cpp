#include "mainwindow.h"
#include "screendisplay.h"
#include "chip8.h"

#include <QApplication>
#include <thread>
#include <chrono>

#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int BOARD_ROWS {32};
    const int BOARD_COLUMNS {64};
    const int PIXEL_SIZE {20};

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    /*QApplication a(argc, argv);
    CHIP8 *mychip = new CHIP8();
    mychip->load_program({"/home/robin/Desktop/Chip8 Games/test_opcode.ch8"});

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
