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

namespace Global
{
    //inline SDL_Texture* texFullMapOverview = NULL;
    inline SDL_Window* window = NULL;
    inline TTF_Font* Sans = NULL;
    inline SDL_Renderer* rendererFullMapOverview = NULL;
    inline SDL_Renderer* renderer = NULL;
    inline bool isFullscreen;

    SDL_Texture* ConvertSurfaceToTexture(SDL_Surface* surface);
    void DestroySDLObjects();
    void ToggleFullscreen();
}

inline SDL_Texture* Global::ConvertSurfaceToTexture(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(renderer, surface);
}

inline void Global::ToggleFullscreen()
{

    isFullscreen = !isFullscreen;

    if (isFullscreen)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else
        SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE);

}

inline void Global::DestroySDLObjects()
{

    TTF_CloseFont(Sans);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyRenderer(rendererFullMapOverview);

}