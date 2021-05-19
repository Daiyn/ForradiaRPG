/*+===================================================================
  File:      GLOBAL_SDL.H

  Summary:   Brief summary of the file contents and purpose.

  Classes:   Describes free variables and functions related to the
             SDL-dependent parts of the game.

  Functions: ConvertSurfaceToTexture
             ToggleFullscreen
             DestroySDLObjects

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/



#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>

namespace Global
{
    inline SDL_Window* sdlWindow = NULL;
    inline TTF_Font* fontFreesans = NULL;
    inline SDL_Renderer* sdlRendererFullMapRender = NULL;
    inline SDL_Renderer* sdlRendererDefault = NULL;
    inline bool stateFullscreen;

    SDL_Texture* ConvertSurfaceToTexture(SDL_Surface* surface);
    void DestroySDLObjects();
    void ToggleFullscreen();
}

inline SDL_Texture* Global::ConvertSurfaceToTexture(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(sdlRendererDefault, surface);
}

inline void Global::ToggleFullscreen()
{

    stateFullscreen = !stateFullscreen;

    if (stateFullscreen)
        SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else
        SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_RESIZABLE);

}

inline void Global::DestroySDLObjects()
{

    TTF_CloseFont(fontFreesans);

    SDL_DestroyRenderer(sdlRendererDefault);
    SDL_DestroyRenderer(sdlRendererFullMapRender);
    SDL_DestroyWindow(sdlWindow);

}