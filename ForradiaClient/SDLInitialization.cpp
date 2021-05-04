#include "SDLInitialization.h"
#include <SDL2/SDL.h>
#include "Global_SDL.h"
#include <SDL2/SDL_ttf.h>


void SDLInitialization::Initialize()
{

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    int windowInitWidth = dm.w*3/4;
    int windowInitHeight = dm.h*3/4;
    Global::window = SDL_CreateWindow("Forradia",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, 
                                        windowInitWidth,
                                        windowInitHeight,
                                        SDL_WINDOW_RESIZABLE);
    Global::renderer = SDL_CreateRenderer(Global::window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(Global::renderer, SDL_BLENDMODE_BLEND);
    SDL_ShowCursor(SDL_DISABLE);
    TTF_Init();

}