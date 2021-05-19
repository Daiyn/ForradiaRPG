/*+===================================================================
  File:      GLOBAL_WORLDMAP.H

  Summary:   Describes the globally accessed world map structure.

  Classes:   CMap

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <memory>
#include "Map.h"

using std::unique_ptr;

namespace Global
{
    const int maxWorldmapCols = 1;
    const int maxWorldmapRows = 1;
    const int maxWorldmapFloors = 1;
    inline unique_ptr<Map> contentWorldmap[maxWorldmapCols][maxWorldmapRows][maxWorldmapFloors];
}
