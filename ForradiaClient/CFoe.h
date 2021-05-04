/*+===================================================================
  File:      CFOE.H

  Summary:   Describes class for which represent all enemy characters
             that the player can fight.

  Classes:   CFoe
             CFightableCharacter

  Functions: 

  Origin:    Written by Andreas �kerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_FOE_H
#define FORRADIAFORMATION_FOE_H

#include <SDL2/SDL_rect.h>
#include "CFightableCharacter.h"
#include "CPoint.h"
#include <chrono>

using namespace std::chrono;

typedef high_resolution_clock Clock;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CFightableCharacter

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

class CFoe : public CFightableCharacter
{
public:

    CPoint m_posCurrent = { -1, -1 };
    CPoint m_posSpawn = { -1, -1 };
    int m_idxFoeType = -1;
    int m_spdMovement = 500;
    int m_hpMax = 10;
    int m_uniqueId;
    int m_tickTimeToRespawn = 0;
    int m_spdRespawn = 16000;
    Clock::time_point m_tickLastMove = Clock::now();

    static int s_idCountFoes;

    CFoe(int _foeType, int _mapx, int _mapy);

    bool IsAlive();

protected:

private:

};


#endif
