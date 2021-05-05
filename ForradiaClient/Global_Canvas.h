/*+===================================================================
  File:      GLOBAL_CANVAS.H

  Summary:   Describes general functions and a free function related
             to the canvas rendering.

  Classes:   

  Functions: GetCanvasWidth
             GetCanvasHeight
             GetScalingHorizontal
             GetScalingVertical
             GetScalingAverage
             GetTileSize
             GetNumberOfColumns

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include "Global_SDL.h"

namespace Global
{
	const int tilesNumberOfRows = 27;

    int GetCanvasHeight();
	int GetCanvasWidth();
    int GetNumberOfColumns();
    double GetScalingAverage();
    double GetScalingHorizontal();
    double GetScalingVertical();
	int GetTileSize();
}

inline int Global::GetCanvasWidth()
{

    if (Global::stateFullscreen)
    {
        int sw = 0;
        int sh = 0;
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);

        return DM.w;
    }
    else
    {
        int w, h;
        SDL_GetWindowSize(sdlWindow, &w, &h);

        return w;
    }


}

inline int Global::GetCanvasHeight()
{

    if (Global::stateFullscreen)
    {
        int sw = 0;
        int sh = 0;
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);

        return DM.h;
    }
    else
    {
        int w, h;
        SDL_GetWindowSize(sdlWindow, &w, &h);

        return h;
    }
}

inline double Global::GetScalingHorizontal()
{
    return 1.0 / 1600.0 * Global::GetCanvasWidth();
}

inline double Global::GetScalingVertical()
{
    return 1.0 / 900.0 * Global::GetCanvasHeight();
}

inline double Global::GetScalingAverage()
{
    return (GetScalingHorizontal() + GetScalingVertical()) / 2.0;
}

inline int Global::GetTileSize() { return GetCanvasHeight() / Global::tilesNumberOfRows; }

inline int Global::GetNumberOfColumns() { return GetCanvasWidth() / GetTileSize(); }