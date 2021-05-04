/*+===================================================================
  File:      NPCRENDERING.H

  Summary:   Describes namespace members related to rendering NPCs
             in the map.

  Classes:   CPoint

  Functions: RenderNpcs

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_NPCRENDERING_H
#define FORRADIAFORMATION_NPCRENDERING_H

#include "CPoint.h"

namespace NPCRendering
{
    void RenderNpcs(int x, int y, CPoint pTile);
};


#endif