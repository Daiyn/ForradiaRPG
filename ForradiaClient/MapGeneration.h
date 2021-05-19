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

#include "Map.h"
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace MapGeneration
{
    inline unordered_map<string, int> idxsUsedObjects;
    inline unordered_map<string, int> idxsUsedTiles;
    inline unordered_map<string, int> paramsGenerationInput;

    inline double k0;
    inline double k1;
    inline double k2;
    inline double k3;
    inline double k4;
    inline double k5;
    inline double k6;
    inline double k7;
    inline double k8;
    inline double k9;
    inline double k10;
    inline double k11;
    inline double k12;
    inline double k13;

    void GenerateAll(Map& map);
    void GenerateMap(Map& map);
    void GenerateRiversFromMountainTop(Map& map, int mapx, int mapy);
    void SetAllTilesToGrass(Map& map, int mapx, int mapy);
    void GenerateElevation(Map& map, int mapx, int mapy);
    void GenerateRockTiles(Map& map, int mapx, int mapy);
    void GenerateWater(Map& map, int mapx, int mapy);
    void GenerateSand(Map& map, int mapx, int mapy);
    void GenerateTree1(Map& map, int mapx, int mapy);
    void GenerateTree2(Map& map, int mapx, int mapy);
};

#endif
