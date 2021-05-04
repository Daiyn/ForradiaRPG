/*+===================================================================
  File:      FOESRENDERING.H

  Summary:   Describes the function responsible for rendering all
             foes.

  Classes:   CPoint

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_FOESRENDERING_H
#define FORRADIAFORMATION_FOESRENDERING_H

class CPoint;

namespace FoesRendering
{
    void RenderTileFoes(int x, int y, CPoint pTile);
};


#endif