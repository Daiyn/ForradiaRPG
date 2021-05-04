#include "CNPC.h"
#include "NPCNameGeneration.h"
#include "CMap.h"
#include <SDL2/SDL_timer.h>
#include "CNPCDialog.h"
#include "CNPCDialogPhrase.h"
#include "CNPCDialogPhraseAnswerOption.h"
#include "CPoint.h"
#include "CTile.h"
#include <memory>

using std::move;
using std::make_unique;

int CNPC::s_cntMaxNPCID = 0;


CNPC::CNPC(string _imageName, int _mapx, int _mapy, int mapSize)
{

    m_nameCharacter = NPCNameGeneration::GenerateName();
    m_nameImage = _imageName;
    m_2DMapX = _mapx;
    m_2DMapY = _mapy;
    m_uniqueID = s_cntMaxNPCID;

    m_2DHouseMapX = rand() % mapSize;
    m_2DHouseMapY = rand() % mapSize;

    CNPCDialogPhrase phrase0;
    CNPCDialogPhrase phrase1;

    phrase0.m_txtblockTextLines.push_back("Hello!");
    phrase0.m_txtblockTextLines.push_back("");
    phrase0.m_txtblockTextLines.push_back("Can you help me build a house?");
    phrase0.m_txtblockTextLines.push_back("I will pay you good.");

    phrase0.m_optAnswers.push_back(CNPCDialogPhraseAnswerOption("No", -1));
    CNPCDialogPhraseAnswerOption answerYes("Yes, of course!", 1);

    answerYes.m_instructObjectCreation = std::tuple<int, int, int>(m_2DHouseMapX, m_2DHouseMapY, 18);

    phrase0.m_optAnswers.push_back(answerYes);

    phrase1.m_txtblockTextLines.push_back("Great!");
    phrase1.m_txtblockTextLines.push_back("The house needs to be built at");
    phrase1.m_txtblockTextLines.push_back("coordinate (" + std::to_string(m_2DHouseMapX) + ", " + std::to_string(m_2DHouseMapY) + ").");

    phrase1.m_optAnswers.push_back(CNPCDialogPhraseAnswerOption("Ok, bye", -1));

    m_talkCurrentDialog = make_unique<CNPCDialog>(CNPCDialog());

    m_talkCurrentDialog->m_talkPhrases.push_back(phrase0);
    m_talkCurrentDialog->m_talkPhrases.push_back(phrase1);

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
            x = parentMap->m_posPlaza.m_x + 1 + rand() % (parentMap->m_sizePlaza - 2);
            y = parentMap->m_posPlaza.m_y + 1 + rand() % (parentMap->m_sizePlaza - 2);

            int numNPCsInSpot = 0;

            numNPCsInSpot += parentMap->m_2DTiles[x][y]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x + 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x + 1][y]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x + 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x - 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x - 1][y]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
            numNPCsInSpot += parentMap->m_2DTiles[x - 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();

            if (numNPCsInSpot <= 1)
            {
                suitableSpotFound = true;
            }
        }

        m_posMoveDestination = {x, y};
        m_stateCurrentActivity = NPCActivites::GoingToSpotInPlaza;

    }

    if (m_stateCurrentActivity == NPCActivites::GoingToSpotInPlaza)
    {

        int x = m_posMoveDestination.x;
        int y = m_posMoveDestination.y;

        int numNPCsInSpot = 0;

        numNPCsInSpot += parentMap->m_2DTiles[x][y]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x + 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x + 1][y]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x + 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x - 1][y + 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x - 1][y]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();
        numNPCsInSpot += parentMap->m_2DTiles[x - 1][y - 1]->m_floorsArray[SURFACE_FLOOR]->m_npcs.size();

        if (numNPCsInSpot <= 1)
        {

            if (SDL_GetTicks() - m_tickLastMove > m_spdMovement)
            {

                m_tickLastMove = SDL_GetTicks();

                int dx = m_posMoveDestination.x - m_2DMapX;
                int dy = m_posMoveDestination.y - m_2DMapY;

                int absdx = abs(dx);
                int absdy = abs(dy);

                int normx = 0;
                int normy = 0;

                if (dx != 0)
                    normx = dx / absdx;

                if (dy != 0)
                    normy = dy / absdy;

                int xNew = m_2DMapX + normx;
                int yNew = m_2DMapY + normy;

                if (xNew != m_2DMapX || yNew != m_2DMapY)
                {

                    int oldx = m_2DMapX;
                    int oldy = m_2DMapY;

                    m_2DMapX = xNew;
                    m_2DMapY = yNew;

                    if (m_2DMapX == m_posMoveDestination.x && m_2DMapY == m_posMoveDestination.y)
                    {
                        m_stateCurrentActivity = NPCActivites::StandingInPlazaTalkable;
                    }


                    for (auto jt = parentMap->m_2DTiles[oldx][oldy]->m_floorsArray[SURFACE_FLOOR]->m_npcs.begin();
                         jt != parentMap->m_2DTiles[oldx][oldy]->m_floorsArray[SURFACE_FLOOR]->m_npcs.end(); jt++)
                    {
                        if ((*this).m_uniqueID == (*jt)->m_uniqueID)
                        {
                            unique_ptr<CNPC> npc = move(*jt);
                            parentMap->m_2DTiles[oldx][oldy]->m_floorsArray[SURFACE_FLOOR]->m_npcs.erase(jt);
                            parentMap->m_2DTiles[xNew][yNew]->m_floorsArray[SURFACE_FLOOR]->m_npcs.push_back(move(npc));

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