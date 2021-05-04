/*+===================================================================
  File:      TRAINRENDERING.H

  Summary:   Describes namespace member related to rendering the train
             onto the map.

  Classes:   CPoint

  Functions: RenderTrainLocomotive
             RenderTrainCarriages

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_TRAINRENDERING_H
#define FORRADIAFORMATION_TRAINRENDERING_H

#include "CPoint.h"

namespace TrainRendering
{
    void RenderTrainCarriages(int x, int y, CPoint pTile);
    void RenderTrainLocomotive(int x, int y, CPoint pTile);
};


#endif