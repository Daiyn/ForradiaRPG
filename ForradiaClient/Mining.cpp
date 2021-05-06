#include "Mining.h"
#include "Global_Player.h"
#include "Global_CurrentMap.h"
#include "DataLoading.h"
#include "CMap.h"
#include "CPlayer.h"
#include <SDL2/SDL_timer.h>

using std::make_unique;

void Mining::MineTile(CPoint p)
{

    int tileCaveFloor = DataLoading::GetDescriptionIndexByName("TileCaveFloor");
    int objectIronOre = DataLoading::GetDescriptionIndexByName("ObjectIronOre");
    int objectStone = DataLoading::GetDescriptionIndexByName("ObjectStone");
    int objectCoal = DataLoading::GetDescriptionIndexByName("ObjectCoal");

    if (Global::statePlayer->m_locCurrentElevation != SURFACE_FLOOR)
    {

        Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_checkMinedTiles.push_back(Global::statePlayer->m_locCurrentElevation);

        unique_ptr<CTileFloor> tfMinedCave = make_unique<CTileFloor>(CTileFloor(p.m_x, p.m_y, tileCaveFloor));

        if (Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight != Global::statePlayer->m_locCurrentElevation)
        {

            srand(SDL_GetTicks());

            const double mineIronOreSuccessRate = 0.4;
            const double mineCoalSuccessRate = 0.4;

            double dice = ((double)rand()) / RAND_MAX;

            if (dice <= mineIronOreSuccessRate)
                tfMinedCave->AddObject(objectIronOre);
            else if (dice <= mineIronOreSuccessRate + mineCoalSuccessRate)
                tfMinedCave->AddObject(objectCoal);
            else
                tfMinedCave->AddObject(objectStone);

        }

        Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[Global::statePlayer->m_locCurrentElevation] = move(tfMinedCave);

    }
    else
    {

        int entranceElevation = INVALID_ELVATION;

        if (Global::contentCurrentMap->m_tilesGrid[p.m_x + 1][p.m_y]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight)
            entranceElevation = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight;

        if (Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y - 1]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight)
            entranceElevation = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight;

        if (Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[p.m_x + 1][p.m_y]->m_elevationHeight)
            entranceElevation = Global::contentCurrentMap->m_tilesGrid[p.m_x + 1][p.m_y]->m_elevationHeight;

        if (Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y - 1]->m_elevationHeight)
            entranceElevation = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y - 1]->m_elevationHeight;

        if (entranceElevation != INVALID_ELVATION)
        {
            unique_ptr<CTileFloor> tfMinedCave = make_unique<CTileFloor>(CTileFloor(p.m_x, p.m_y, tileCaveFloor));
            Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_checkMinedTiles.push_back(entranceElevation);
            Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[entranceElevation] = move(tfMinedCave);
        }

    }


}