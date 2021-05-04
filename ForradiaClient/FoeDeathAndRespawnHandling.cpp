#include "FoeDeathAndRespawnHandling.h"
#include <vector>
#include "Global_CurrentMap.h"
#include "DataLoading.h"
#include "CMap.h"
#include <SDL2/SDL_timer.h>
#include "CFoe.h"
#include "CTile.h"
#include <memory>

#define FOR(x,y,z) for (int x = y; x < z; x++)

using std::make_unique;

void FoeDeathAndRespawnHandling::Update()
{

    FOR(i, 0, Global::currentMap->m_allFoesArray.size())
    {


        CFoe& foe = Global::currentMap->m_allFoesArray[i];

        CPoint p = foe.m_posCurrent;

        auto& TILES = Global::currentMap->m_2DTiles;
        auto& FLOOR = *TILES[p.m_x][p.m_y]->m_floorsArray[SURFACE_FLOOR];

        if (foe.m_hpCurrent <= 0)
        {

            unique_ptr<CFoe> foeRespawn = make_unique<CFoe>(CFoe(foe.m_idxFoeType, foe.m_posSpawn.m_x, foe.m_posSpawn.m_y));
            foeRespawn->m_tickTimeToRespawn = SDL_GetTicks() + foe.m_spdRespawn;
            Global::currentMap->AddFoe(move(foeRespawn), SURFACE_FLOOR);


            Global::currentMap->ClearReferencesToFoe(foe, i, FLOOR);
            Global::currentMap->AddChangingObject(DataLoading::GetDescriptionIndexByName("ObjectFoeDead"), p, SURFACE_FLOOR);

        }

    }

}