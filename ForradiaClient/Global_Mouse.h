/*+===================================================================
  File:      GLOBAL_MOUSE.H

  Summary:   Describes functions to easily get mouse position on the
             screen.

  Classes:   CPoint

  Functions: GetMousePoint
             GetMouseX
             GetMouseY

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include "CPoint.h"
#include <SDL2/SDL_mouse.h>

namespace Global
{
    CPoint GetMousePoint();
	int GetMouseX();
	int GetMouseY();
}

inline CPoint Global::GetMousePoint()
{
    int mx;
    int my;

    SDL_GetMouseState(&mx, &my);

    return { mx, my };
}

inline int Global::GetMouseX()
{
    int mx;
    int my;

    SDL_GetMouseState(&mx, &my);

    return mx;
}

inline int Global::GetMouseY()
{
    int mx;
    int my;

    SDL_GetMouseState(&mx, &my);

    return my;
}