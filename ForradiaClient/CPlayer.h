/*+===================================================================
  File:      CPLAYER.H

  Summary:   Describes essential CPlayer class which is used in most
             of the different areas of the game.

  Classes:   CPlayer
             CFightableCharacter
             CPoint
             CInventory

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_PLAYER_H
#define FORRADIAFORMATION_PLAYER_H

#include <map>
#include <chrono>
#include "CTile.h"
#include "CInventory.h"
#include "CPoint3D.h"

using namespace std::chrono;


typedef high_resolution_clock Clock;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CPlayer

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

class CPlayer : public CFightableCharacter
{
public:

    Clock::time_point m_tickLastMove = Clock::now();
    Clock::time_point m_tickLastActualMove = Clock::now();
    CInventory m_inventory;
    CPoint m_posCurrent = { -1, -1 };
    CPoint m_posMoveDestination = {-1, -1};
    int m_spdMovement = 70;
    int m_tickStartJump = 0;
    int m_duraJumping = 1000;
    int m_hpMax = 100;
    int m_elevCurrent = SURFACE_FLOOR;
    CPoint3D m_coordWorldSubmap = { 0, 0, 0 };
    int m_tickLastSkillCastEnded = 0;
    int m_spdSkillCasting = 300;
    double m_nrgyMax = 100;
    double m_nrgyCurrent = 100;

    CPlayer(int mapSize);

    int GetJumpHeight();
    bool IsJumping();
    void Jump();
    void MouseClickToMove();
    void Update();
    void UpdateCombatMovement();
    void UpdateJumping();
    void UpdateKeyboardMovement();
    void UpdateMouseMovement();
    bool ConsumeNRGY(int nrgyAmount);
    void AddNRGY(double nrgyAmount);

protected:

private:

};


#endif
