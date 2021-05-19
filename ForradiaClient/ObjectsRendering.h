/*+===================================================================
  File:      OBJECTSRENDERING.H

  Summary:   Describing namespace members related to rendering objects
             being placed on tiles of the map.

  Classes:   CMap
             Point

  Functions: RenderTileObjects

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_OBJECTSRENDERING_H
#define FORRADIAFORMATION_OBJECTSRENDERING_H

#include "Map.h"
#include <memory>

using std::unique_ptr;

namespace ObjectsRendering
{
    void RenderTileObjects(double tileSize, int x, int y, Point pTile);
};


#endif