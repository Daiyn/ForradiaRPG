/*+===================================================================
  File:      TEXTRENDERING.H

  Summary:   Describes namespace members related to rendering text.

  Classes:   Point

  Functions: Initialize
             DrawString
             GetTextWidth
             GetTextHeight

  Origin:    Written by Andreas �kerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_TEXTRENDERING_H
#define FORRADIAFORMATION_TEXTRENDERING_H

#include <string>
#include <SDL2/SDL_pixels.h>
#include "Point.h"

#define BOTTOM_CENTER 0

using std::string;

namespace TextRendering
{
    int GetTextHeight();
    int GetTextWidth(string str);
    void Initialize();
    void DrawString(string str, SDL_Color color, Point p);
    void DrawString(string str, SDL_Color color, int x, int y);
    void DrawString(string str, SDL_Color color, int position);
};


#endif
