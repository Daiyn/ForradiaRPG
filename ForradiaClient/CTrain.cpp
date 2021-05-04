#include "CTrain.h"
#include "DataLoading.h"
#include "Global_MapSize.h"
#include "Global_CurrentMap.h"
#include <SDL2/SDL_timer.h>
#include "CTile.h"
#include "CMap.h"
#include <memory>

using std::make_unique;

void CTrain::Update()
{

    int railStartX;
    int railStartY;

    for (int y = 0; y < Global::mapSize; y++)
    {
        if (Global::currentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEW"), 0, y, SURFACE_FLOOR)) {
            railStartX = 0;
            railStartY = y;
            break;
        }
    }

    int railx = railStartX;
    int raily = railStartY;

    m_stationSize = 0;

    while (railx != Global::mapSize - 1)
    {

        if (Global::currentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEWStationS"), railx, raily, SURFACE_FLOOR)) {
            m_stationSize++;
        }

        railx++;
    }

    m_numCarriages = m_stationSize / 4;


    if (m_trainPosition.x == -1 && m_trainPosition.y == -1)
    {

        m_trainPosition = {railStartX, railStartY};

        m_npcsOnTrain.clear();

        if (m_numCreatedNpcs < 6)
        {

            for (int i = 0; i < m_stationSize / 2 - 1; i++)
            {
                m_npcsOnTrain.push_back(make_unique<CNPC>(CNPC("NPC0", -1, -1, Global::mapSize)));
                m_numCreatedNpcs++;
            }

        }

    }
    else
    {

        if (SDL_GetTicks() - m_tickLastTimeTrainMove > m_trainMoveSpeed) 
        {

            bool pauseAtStation = false;

            if (Global::currentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEWStationS"), m_trainPosition.x, m_trainPosition.y, SURFACE_FLOOR)
                && Global::currentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEW"), m_trainPosition.x + 1, m_trainPosition.y, SURFACE_FLOOR))
            {

                if (SDL_GetTicks() - m_tickLastTimeTrainMove < m_stopAtStationDuration)
                {

                    pauseAtStation = true;

                    int i = 1;

                    for (auto it = m_npcsOnTrain.begin(); it != m_npcsOnTrain.end(); it++)
                    {

                        (*it)->m_2DMapX = m_trainPosition.x - i * 2 - 2;
                        (*it)->m_2DMapY = m_trainPosition.y + 2;
                        (*it)->m_stateCurrentActivity = CNPC::NPCActivites::FindingFreeSpotInPlaza;
                        Global::currentMap->m_listAllNPCs.push_back(*(*it));
                        Global::currentMap->m_2DTiles[(*it)->m_2DMapX][(*it)->m_2DMapY]->m_floorsArray[SURFACE_FLOOR]->m_npcs.push_back(move(*it));

                        i++;

                    }

                    m_npcsOnTrain.clear();
                }
            }

            if (!pauseAtStation)
            {

                m_trainPosition.x++;
                m_tickLastTimeTrainMove = SDL_GetTicks();
                m_trainCarriagePositions.clear();

                for (int i = 1; i <= m_numCarriages; i++)
                    m_trainCarriagePositions.push_back({ m_trainPosition.x - i * 4, m_trainPosition.y });

            }
        }
    }

    if (m_trainPosition.x >= Global::mapSize)
        m_trainPosition = {-1, -1};

}


