#ifndef DEBUGDISPLAY_H
#define DEBUGDISPLAY_H

#include <SDL2/SDL.h>
#include "chip8.h"

class DebugDisplay
{
public:
    const int BOARD_ROWS {32};
    const int BOARD_COLUMNS {64};
    const int PIXEL_SIZE {20};
    const int SCREEN_WIDTH {BOARD_COLUMNS * PIXEL_SIZE};
    const int SCREEN_HEIGHT {BOARD_ROWS * PIXEL_SIZE};
    DebugDisplay(CHIP8* chip8);
private:
    CHIP8* chip8;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect* pixels [32*64];
    SDL_Event e;

    void setup_pixels();

    //TODO remove
    bool quit {false};
};

#endif // DEBUGDISPLAY_H
