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
#include "CMap.h"

using std::unique_ptr;

namespace Global
{
    const int worldMapCols = 1;
    const int worldMapRows = 1;
    const int worldMapLevels = 1;
    inline unique_ptr<CMap> worldMap[worldMapCols][worldMapRows][worldMapLevels];
}
