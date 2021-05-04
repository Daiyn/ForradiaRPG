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

    if (Global::player->m_elevCurrent != SURFACE_FLOOR)
    {

        Global::currentMap->m_2DMinedTiles[p.m_x][p.m_y].push_back(Global::player->m_elevCurrent);

        unique_ptr<CTileFloor> tfMinedCave = make_unique<CTileFloor>(CTileFloor(p.m_x, p.m_y, tileCaveFloor));

        if (Global::currentMap->m_2DElevation[p.m_x][p.m_y] != Global::player->m_elevCurrent)
        {

            srand(SDL_GetTicks());

            const double mineIronOreSuccessRate = 0.4;

            if (((double)rand()) / RAND_MAX <= mineIronOreSuccessRate)
                tfMinedCave->AddObject(objectIronOre);
            else
                tfMinedCave->AddObject(objectStone);

        }

        Global::currentMap->m_2DTiles[p.m_x][p.m_y]->m_floorsArray[Global::player->m_elevCurrent] = move(tfMinedCave);

    }
    else
    {

        int entranceElevation = INVALID_ELVATION;

        if (Global::currentMap->m_2DElevation[p.m_x + 1][p.m_y] > Global::currentMap->m_2DElevation[p.m_x][p.m_y])
            entranceElevation = Global::currentMap->m_2DElevation[p.m_x][p.m_y];

        if (Global::currentMap->m_2DElevation[p.m_x][p.m_y - 1] > Global::currentMap->m_2DElevation[p.m_x][p.m_y])
            entranceElevation = Global::currentMap->m_2DElevation[p.m_x][p.m_y];

        if (Global::currentMap->m_2DElevation[p.m_x][p.m_y] > Global::currentMap->m_2DElevation[p.m_x + 1][p.m_y])
            entranceElevation = Global::currentMap->m_2DElevation[p.m_x + 1][p.m_y];

        if (Global::currentMap->m_2DElevation[p.m_x][p.m_y] > Global::currentMap->m_2DElevation[p.m_x][p.m_y - 1])
            entranceElevation = Global::currentMap->m_2DElevation[p.m_x][p.m_y - 1];

        if (entranceElevation != INVALID_ELVATION)
        {
            unique_ptr<CTileFloor> tfMinedCave = make_unique<CTileFloor>(CTileFloor(p.m_x, p.m_y, tileCaveFloor));
            Global::currentMap->m_2DMinedTiles[p.m_x][p.m_y].push_back(entranceElevation);
            Global::currentMap->m_2DTiles[p.m_x][p.m_y]->m_floorsArray[entranceElevation] = move(tfMinedCave);
        }

    }


}