/*+===================================================================
  File:      CPLAYER.H

  Summary:   Describes essential CPlayer class which is used in most
             of the different areas of the game.

  Classes:   CPlayer
             CFightableCharacter
             Point
             CInventory

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_PLAYER_H
#define FORRADIAFORMATION_PLAYER_H

#include <map>
#include <chrono>
#include "Tile.h"
#include "Inventory.h"
#include "Point.h"

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

class Player
{
public:

    Clock::time_point m_tickLastMove = Clock::now();
    Clock::time_point m_tickLastActualMove = Clock::now();
    Inventory m_inventory;
    Point m_coordPosition = { -1, -1 };
    Point m_coordMoveDestination = {-1, -1};
    int m_spdMovement = 130;
    int m_tickStartJump = 0;
    int m_duraJumping = 1000;
    int m_statMaxHP = 100;
    int m_locCurrentElevation = SURFACE_FLOOR;
    Point3D m_coordWorldSubmap = { 0, 0, 0 };
    int m_tickLastSkillCastEnded = 0;
    int m_spdSkillCasting = 300;
    double m_statMaxNRGY = 100;
    double m_statCurrentNRGY = 100;

    Player(int mapSize);

    int GetJumpHeight();
    bool IsJumping();
    void Jump();
    void MouseClickToMove();
    void Update();
    void UpdateJumping();
    void UpdateKeyboardMovement();
    void UpdateMouseMovement();
    bool ConsumeNRGY(int nrgyAmount);
    void AddNRGY(double nrgyAmount);

protected:

private:

};


#endif
