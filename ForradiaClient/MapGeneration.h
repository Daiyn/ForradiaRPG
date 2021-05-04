/*+===================================================================
  File:      MAPGENERATION.H

  Summary:   Describes free variables and functions related to 
             randomized procedural generation of maps.

  Classes:   CMap

  Functions: GenerateMap
             GenerateAll
             GenerateRiversFromMountainTop

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_MAPGENERATION_H
#define FORRADIAFORMATION_MAPGENERATION_H

#include "CMap.h"
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace MapGeneration
{
    inline unordered_map<string, int> usedObjects;
    inline unordered_map<string, int> usedTiles;
    inline unordered_map<string, int> parameters;

    void GenerateAll(CMap& map);
    void GenerateMap(CMap& map);
    void GenerateRiversFromMountainTop(CMap& map, int mapx, int mapy);
};

#endif
