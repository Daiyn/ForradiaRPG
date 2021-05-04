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

    vector<SDL_Point> m_trainCarriagePositions;
    vector<unique_ptr<CNPC>> m_npcsOnTrain;
    SDL_Point m_trainPosition = { -1, -1 };
    int m_tickLastTimeTrainMove = 0;
    int m_trainMoveSpeed = 200;
    int m_numCarriages = -1;
    int m_stopAtStationDuration = 8000;
    int m_stationSize = 0;
    int m_numCreatedNpcs = 0;

    void Update();

protected:

private:

};


#endif
