/*+===================================================================
  File:      CNPC.H

  Summary:   Describes the NPC (Non Player Character) class, which is
             a major gameplay element, with which the player interacts
             through dialogs to help them build their houses. The NPCs
             arrive with train to the plaza in the start of the game.
             When a house has been built for a NPC it will move in
             there and may take on a profession and start to walk 
             around the map on built roads interacting with other
             NPCs and the player.

  Classes:   CNPC
             NPCActivites
             CNPCDialog
             CNPCDialog

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_NPC_H
#define FORRADIAFORMATION_NPC_H

#include <string>
#include <SDL2/SDL_rect.h>
#include <memory>
#include "CNPCDialog.h"

using std::string;
using std::unique_ptr;

class CMap;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CNPC

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

class CNPC
{
public:

    enum NPCActivites
    {
        NotDefined,
        FindingFreeSpotInPlaza,
        GoingToSpotInPlaza,
        StandingInPlazaTalkable
    };

    string m_nameCharacter;
    string m_nameImage;
    SDL_Point m_posMoveDestination = { -1, -1 };
    int m_2DMapX = -1;
    int m_2DMapY = -1;
    int m_tickLastMove = 0;
    int m_spdMovement = 400;
    int m_uniqueID;
    int m_2DHouseMapX = -1;
    int m_2DHouseMapY = -1;
    unique_ptr<CNPCDialog> m_talkCurrentDialog;
    NPCActivites m_stateCurrentActivity = NotDefined;

    static int s_cntMaxNPCID;

    CNPC(string _imageName, int _mapx, int _mapy, int mapSize);

    void Update(CMap *parentMap);

protected:

private:

};


#endif
