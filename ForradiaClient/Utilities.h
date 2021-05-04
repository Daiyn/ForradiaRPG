/*+===================================================================
  File:      UTILITIES.H

  Summary:   Describes namespace members consisting of help functions
             used in other areas of the game.

  Classes:   

  Functions: Normalize
             GenerateAnimationFrameIndex
             GenerateTileCorrelatedAnimationFrameIndex
             GetHoveredScreenMapx
             GetHoveredScreenMapy
             GetHoveredMapx
             GetHoveredMapy
             InMapIncludingEdges
             InMapExcludingEdges

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_UTILITIES_H
#define FORRADIAFORMATION_UTILITIES_H

namespace Utilities
{
    int GenerateAnimationFrameIndex(int numberOfFrames, int animationSpeed);
    int GenerateTileCorrelatedAnimationFrameIndex(int numberOfFrames, int animationSpeed, int mapx, int mapy);
    int GetHoveredMapx();
    int GetHoveredMapy();
    int GetHoveredScreenMapx();
    int GetHoveredScreenMapy();
    bool InMapExcludingEdges(int mapx, int mapy);
    bool InMapIncludingEdges(int mapx, int mapy);
    int Normalize(int a, int b);
    bool DoTickCheck(int& tickVariable, int threshold);
};


#endif