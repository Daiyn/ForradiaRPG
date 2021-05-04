/*+===================================================================
  File:      TILEEFFECTSRENDERING.H

  Summary:   Describes namespace member related to rendering effects
             connected to specific tiles.

  Classes:   CPoint

  Functions: RenderTileEffects

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_TILEEFFECTSRENDERING_H
#define FORRADIAFORMATION_TILEEFFECTSRENDERING_H

#include "CPoint.h"

namespace TileEffectsRendering
{
    void RenderTileEffects(int x, int y, CPoint pTile);
};


#endif
