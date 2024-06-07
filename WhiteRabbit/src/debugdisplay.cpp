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
    setup_pixels();

    this->chip8 = chip8;

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

        //Run chip8 instruction
        chip8->emulate_cycle();

        //Clear screen
        //SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        //SDL_RenderClear( renderer );

        // Update display
        for(int i {0}; i < 32*64; i++){
            chip8->get_display()[i] ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) : SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, pixels[i]);
        }

        //Update screen
        SDL_RenderPresent( renderer );
    }



    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    for(int i {0}; i < 32*64; i++){
        delete pixels[i];
    }

    //Quit SDL subsystems
    SDL_Quit();
}

void DebugDisplay::setup_pixels(){
    for(int row{0}; row < BOARD_ROWS; row++){
        for(int column {0}; column < BOARD_COLUMNS; column++){
            SDL_Rect* pixel = new SDL_Rect();
            pixel->h = PIXEL_SIZE;
            pixel->w = PIXEL_SIZE;
            pixel->x = PIXEL_SIZE * column;
            pixel->y = PIXEL_SIZE * row;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, pixel);
            pixels[row * 64 + column] = pixel;
        }
    }
    SDL_RenderPresent(renderer);
}

