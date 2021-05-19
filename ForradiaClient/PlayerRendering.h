/*+===================================================================
  File:      PLAYERRENDERING.H

  Summary:   Describing namespace members related to rendering the
             player onto the map.

  Classes:   Point

  Functions: RenderPlayer

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_PLAYERRENDERING_H
#define FORRADIAFORMATION_PLAYERRENDERING_H

#include "Point.h"

namespace PlayerRendering
{
    void RenderPlayer(int x, int y, Point pTile);
};


#endif