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

    FOR(i, 0, Global::contentCurrentMap->m_mirrorAllFoes.size())
    {

        CFoe& foe = Global::contentCurrentMap->m_mirrorAllFoes[i];

        CPoint p = foe.m_coordPosition;

        auto& TILES = Global::contentCurrentMap->m_tilesGrid;
        auto& FLOOR = *TILES[p.m_x][p.m_y]->m_floorsArray[SURFACE_FLOOR];

        if (foe.m_statCurrentHP <= 0)
        {

            unique_ptr<CFoe> foeRespawn = make_unique<CFoe>(CFoe(foe.m_idxFoeType, foe.m_coordSpawn.m_x, foe.m_coordSpawn.m_y));
            foeRespawn->m_tickTimeToRespawn = SDL_GetTicks() + foe.m_spdRespawn;
            Global::contentCurrentMap->AddFoe(move(foeRespawn), SURFACE_FLOOR);


            Global::contentCurrentMap->ClearReferencesToFoe(foe, i, FLOOR);
            Global::contentCurrentMap->AddChangingObject(DataLoading::GetDescriptionIndexByName("ObjectFoeDead"), p, SURFACE_FLOOR);

        }

    }

}