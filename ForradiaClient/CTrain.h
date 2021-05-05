/*+===================================================================
  File:      CTRAIN.H

  Summary:   Describes the class responsible for everything related
             to the train except the rendering part.

  Classes:   CTrain
             CNPC

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_TRAIN_H
#define FORRADIAFORMATION_TRAIN_H

#include <vector>
#include <SDL2/SDL_rect.h>
#include <memory>

using std::vector;
using std::unique_ptr;

class CNPC;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CTrain

  Summary:  Short summary of purpose and content of CMyClass.
            Short summary of purpose and content of CMyClass.

  Methods:  MyMethodOne
              Short description of MyMethodOne.
            MyMethodTwo
              Short description of MyMethodTwo.
            CMyClass
              Constructor.
            ~CMyClass
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

class CTrain
{
public:

    vector<SDL_Point> m_coordsCarriagePositions;
    vector<unique_ptr<CNPC>> m_containedNPCsOnTrain;
    SDL_Point m_coordPosition = { -1, -1 };
    int m_tickLastTimeTrainMove = 0;
    int m_spdMovement = 200;
    int m_propNumberCarriages = -1;
    int m_propStopAtStationDuration = 8000;
    int m_propStationSize = 0;
    int m_counterNumberCreatedNpcs = 0;

    void Update();

protected:

private:

};


#endif
