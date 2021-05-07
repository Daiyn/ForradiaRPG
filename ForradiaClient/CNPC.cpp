#include "CNPC.h"
#include "NPCNameGeneration.h"
#include "CMap.h"
#include <SDL2/SDL_timer.h>
#include "CNPCDialog.h"
#include "CPoint.h"
#include "CTile.h"
#include <memory>

using std::move;
using std::make_unique;

int CNPC::s_cntMaxNPCID = 0;

CNPC::CNPC(string _imageName, int _mapx, int _mapy, int mapSize)
{

    m_readableCharacterName = NPCNameGeneration::GenerateName();
    m_nameImage = _imageName;
    m_coordMapX = _mapx;
    m_coordMapY = _mapy;
    m_uniqueID = s_cntMaxNPCID;

    m_coordHouseMapX = rand() % mapSize;
    m_coordHouseMapY = rand() % mapSize;

    CNPCDialogPhrase phrase0;
    CNPCDialogPhrase phrase1;

    phrase0.m_textblockTextLines.push_back("Hello!");
    phrase0.m_textblockTextLines.push_back("");
    phrase0.m_textblockTextLines.push_back("Can you help me build a house?");
    phrase0.m_textblockTextLines.push_back("I will pay you good.");

    phrase0.m_optAnswers.push_back(CNPCDialogPhraseAnswerOption("No", -1));
    CNPCDialogPhraseAnswerOption answerYes("Yes, of course!", 1);

    answerYes.m_instructObjectCreation = std::tuple<int, int, int>(m_coordHouseMapX, m_coordHouseMapY, 18);

    phrase0.m_optAnswers.push_back(answerYes);

    phrase1.m_textblockTextLines.push_back("Great!");
    phrase1.m_textblockTextLines.push_back("The house needs to be built at");
    phrase1.m_textblockTextLines.push_back("coordinate (" + std::to_string(m_coordHouseMapX) + ", " + std::to_string(m_coordHouseMapY) + ").");

    phrase1.m_optAnswers.push_back(CNPCDialogPhraseAnswerOption("Ok, bye", -1));

    m_interactiveCurrentDialog = make_unique<CNPCDialog>(CNPCDialog());

    m_interactiveCurrentDialog->m_talkingPhrases.push_back(phrase0);
    m_interactiveCurrentDialog->m_talkingPhrases.push_back(phrase1);

    s_cntMaxNPCID++;
}

void CNPC::Update(CMap *parentMap)
{

    if (m_stateCurrentActivity == NPCActivites::FindingFreeSpotInPlaza)
    {
        bool suitableSpotFound = false;
        int x;
        int y;

        while (!suitableSpotFound)
        {
            x = parentMap->m_coordPlazaPosition.m_x + 1 + rand() % (parentMap->m_tilesNumPlazaSize - 2);
            y = parentMap->m_coordPlazaPosition.m_y + 1 + rand() % (parentMap->m_tilesNumPlazaSize - 2);

            int numNPCsInSpot = 0;

            numNPCsInSpot += parentMap->m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x + 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x + 1][y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x + 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x - 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x - 1][y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
            numNPCsInSpot += parentMap->m_tilesGrid[x - 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();

            if (numNPCsInSpot <= 1)
            {
                suitableSpotFound = true;
            }
        }

        m_coordMoveDestination = {x, y};
        m_stateCurrentActivity = NPCActivites::GoingToSpotInPlaza;

    }

    if (m_stateCurrentActivity == NPCActivites::GoingToSpotInPlaza)
    {

        int x = m_coordMoveDestination.x;
        int y = m_coordMoveDestination.y;

        int numNPCsInSpot = 0;

        numNPCsInSpot += parentMap->m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x + 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x + 1][y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x + 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x - 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x - 1][y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();
        numNPCsInSpot += parentMap->m_tilesGrid[x - 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size();

        if (numNPCsInSpot <= 1)
        {

            if (m_tmrMovementUpdate.TimeForUpdate())
            {

                int dx = m_coordMoveDestination.x - m_coordMapX;
                int dy = m_coordMoveDestination.y - m_coordMapY;

                int absdx = abs(dx);
                int absdy = abs(dy);

                int normx = 0;
                int normy = 0;

                if (dx != 0)
                    normx = dx / absdx;

                if (dy != 0)
                    normy = dy / absdy;

                int xNew = m_coordMapX + normx;
                int yNew = m_coordMapY + normy;

                if (xNew != m_coordMapX || yNew != m_coordMapY)
                {

                    int oldx = m_coordMapX;
                    int oldy = m_coordMapY;

                    m_coordMapX = xNew;
                    m_coordMapY = yNew;

                    if (m_coordMapX == m_coordMoveDestination.x && m_coordMapY == m_coordMoveDestination.y)
                    {
                        m_stateCurrentActivity = NPCActivites::StandingInPlazaTalkable;
                    }


                    for (auto jt = parentMap->m_tilesGrid[oldx][oldy]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.begin();
                         jt != parentMap->m_tilesGrid[oldx][oldy]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.end(); jt++)
                    {
                        if ((*this).m_uniqueID == (*jt)->m_uniqueID)
                        {
                            unique_ptr<CNPC> npc = move(*jt);
                            parentMap->m_tilesGrid[oldx][oldy]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.erase(jt);
                            parentMap->m_tilesGrid[xNew][yNew]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.push_back(move(npc));

                            break;
                        }
                    }
                }
            }
        }
        else
        {
            m_stateCurrentActivity = NPCActivites::FindingFreeSpotInPlaza;
        }
    }
}