/*+===================================================================
  File:      TILERENDERING.H

  Summary:   Describes namespace members related to rendering tiles,
             i.e. the ground and some effects.

  Classes:   CMap
             Point

  Functions: CheckUnseenTiles
             CoverUnseenTiles
             RenderTileGround
             RenderTileHoveringEffect

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_TILERENDERING_H
#define FORRADIAFORMATION_TILERENDERING_H

#include "Map.h"
#include <memory>

using std::unique_ptr;

namespace TileRendering
{
    bool CheckUnseenTiles(int x, int y, Point pTile);
    void CoverUnseenTiles(int x, int y, Point pTile);
    void RenderTileGround(double tileSize, int x, int y, Point pTile);
    void RenderTileHoveringEffect(int x, int y, Point pTile);
};





#endif //FORRADIAFORMATION_TILERENDERING_H
