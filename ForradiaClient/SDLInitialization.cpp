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
    Global::sdlWindow = SDL_CreateWindow("Forradia",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, 
                                        windowInitWidth,
                                        windowInitHeight,
                                        SDL_WINDOW_RESIZABLE);
    Global::sdlRendererDefault = SDL_CreateRenderer(Global::sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(Global::sdlRendererDefault, SDL_BLENDMODE_BLEND);
    TTF_Init();

}