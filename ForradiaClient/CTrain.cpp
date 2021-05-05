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
        if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEW"), 0, y, SURFACE_FLOOR)) {
            railStartX = 0;
            railStartY = y;
            break;
        }
    }

    int railx = railStartX;
    int raily = railStartY;

    m_propStationSize = 0;

    while (railx != Global::mapSize - 1)
    {

        if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEWStationS"), railx, raily, SURFACE_FLOOR)) {
            m_propStationSize++;
        }

        railx++;
    }

    m_propNumberCarriages = m_propStationSize / 4;

    if (m_coordPosition.x == -1 && m_coordPosition.y == -1)
    {

        m_coordPosition = {railStartX, railStartY};

        m_containedNPCsOnTrain.clear();

        if (m_counterNumberCreatedNpcs < 6)
        {

            for (int i = 0; i < m_propStationSize / 2 - 1; i++)
            {
                m_containedNPCsOnTrain.push_back(make_unique<CNPC>(CNPC("NPC0", -1, -1, Global::mapSize)));
                m_counterNumberCreatedNpcs++;
            }

        }

    }
    else
    {

        if (SDL_GetTicks() - m_tickLastTimeTrainMove > m_spdMovement) 
        {

            bool pauseAtStation = false;

            if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEWStationS"), m_coordPosition.x, m_coordPosition.y, SURFACE_FLOOR)
                && Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEW"), m_coordPosition.x + 1, m_coordPosition.y, SURFACE_FLOOR))
            {

                if (SDL_GetTicks() - m_tickLastTimeTrainMove < m_propStopAtStationDuration)
                {

                    pauseAtStation = true;

                    int i = 1;

                    for (auto it = m_containedNPCsOnTrain.begin(); it != m_containedNPCsOnTrain.end(); it++)
                    {

                        (*it)->m_coordMapX = m_coordPosition.x - i * 2 - 2;
                        (*it)->m_coordMapY = m_coordPosition.y + 2;
                        (*it)->m_stateCurrentActivity = CNPC::NPCActivites::FindingFreeSpotInPlaza;
                        Global::contentCurrentMap->m_mirrorAllNPCs.push_back(*(*it));
                        Global::contentCurrentMap->m_tilesGrid[(*it)->m_coordMapX][(*it)->m_coordMapY]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.push_back(move(*it));

                        i++;

                    }

                    m_containedNPCsOnTrain.clear();
                }
            }

            if (!pauseAtStation)
            {

                m_coordPosition.x++;
                m_tickLastTimeTrainMove = SDL_GetTicks();
                m_coordsCarriagePositions.clear();

                for (int i = 1; i <= m_propNumberCarriages; i++)
                    m_coordsCarriagePositions.push_back({ m_coordPosition.x - i * 4, m_coordPosition.y });

            }
        }
    }

    if (m_coordPosition.x >= Global::mapSize)
        m_coordPosition = {-1, -1};

}


