/*+===================================================================
  File:      FPSCOUNTER.H

  Summary:   Describes the small FPS counter component that is being 
             showed (at least for now) at all times during all scenes 
             of the game.

  Classes:   

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_FPSCOUNTER_H
#define FORRADIAFORMATION_FPSCOUNTER_H

#include <SDL2/SDL_timer.h>

namespace FPSCounter
{
    inline int frames = 0;
    inline int tickSinceLastSecond = SDL_GetTicks();
    inline int fps = 0;

    void Render();
    void Update();
};


#endif
