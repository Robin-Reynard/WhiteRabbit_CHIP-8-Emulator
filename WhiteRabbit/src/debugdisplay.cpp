#include "debugdisplay.h"

DebugDisplay::DebugDisplay(CHIP8* chip8)
{

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return;
    }

    //Create window
    window = SDL_CreateWindow( "WhiteRabbit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return;
    }

    //Create renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return;
    }

    //Clear screen
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );

    this->chip8 = chip8;

    /*int startPos = 0;
            for (int y = 0; y < 8; y++) {
                for (int x = startPos; x < 3; x+=2) {
                        SDL_Rect rect;
                        rect.x = x * 129;
                        rect.y = y * 129;
                        rect.w = 128;
                        rect.h = 128;
                        SDL_SetRenderDrawColor(render, 159, 84, 8, 255);
                        SDL_RenderFillRect(render, &rect);
                }
                startPos = 1 - startPos;
            }*/

    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            //Handle input
            //something.handleEvent( e );
        }

        //Run 1 chip8 instruction
        chip8->emulate_cycle();

        //Render display
        for(int i {0}; i < BOARD_ROWS; i++){
            for(int j {0}; j < BOARD_COLUMNS; j++){
                SDL_Rect pixel;
                pixel.x = j * PIXEL_SIZE;
                pixel.y = i * PIXEL_SIZE;
                pixel.w = PIXEL_SIZE;
                pixel.h = PIXEL_SIZE;
                chip8->get_display()[i*32 + j] ? SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) : SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &pixel);
            }
        }


        //Update screen
        SDL_RenderPresent( renderer );
    }



    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

