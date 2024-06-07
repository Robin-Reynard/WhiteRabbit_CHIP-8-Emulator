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
    SDL_Window* window {NULL};
    SDL_Renderer* renderer {NULL};
    bool quit {false};
    SDL_Event e;
    SDL_Rect pixels [32*64] {};
};

#endif // DEBUGDISPLAY_H
