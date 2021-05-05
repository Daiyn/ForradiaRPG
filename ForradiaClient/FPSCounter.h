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
#include "CTimer.h"

namespace FPSCounter
{
    const int msOneSec = 1000;
    inline int framesCountForOneSec = 0;
    inline int tickSinceLastSecond = SDL_GetTicks();
    inline int resultFPS = 0;
    inline CTimer tmrFPSSave(msOneSec);

    void Render();
    void Update();
};


#endif
