#include "FoeMovement.h"
#include "Global_CurrentMap.h"
#include "Global_MapSize.h"
#include "DataLoading.h"
#include <SDL2/SDL_timer.h>
#include <chrono>
#include "CMap.h"
#include "Constants.h"
#include "CFoe.h"
#include "CTile.h"

#define FOR(x,y,z) for (int x = y; x < z; x++)

using namespace std::chrono;

typedef high_resolution_clock Clock;

void FoeMovement::Update() {

    srand(SDL_GetTicks());

    FOR(i, 0, Global::currentMap->m_allFoesArray.size())
    {

        CFoe& foe = Global::currentMap->m_allFoesArray[i];

        if (!foe.IsAlive())
            continue;

        CPoint p = foe.m_posCurrent;
        int uniqueID = foe.m_uniqueId;

        Clock::time_point t0 = Clock::now();
        Clock::time_point t1 = Clock::now();

        auto d = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - foe.m_tickLastMove).count();


        if (d > foe.m_spdMovement)
        {

            srand(SDL_GetTicks() + p.m_x * p.m_y);

            auto ms = std::chrono::milliseconds(rand() % foe.m_spdMovement);

            foe.m_tickLastMove = Clock::now() + ms;


            if (rand() % 10 < 5)
                continue;

            CPoint pNew;

            int distanceFromSpawn;

            do
            {
                pNew = p;

                pNew.Translate(rand() % 2 - rand()% 2, rand() % 2 - rand()% 2);

                int dx = pNew.m_x - foe.m_posSpawn.m_x;
                int dy = pNew.m_y - foe.m_posSpawn.m_y;

                distanceFromSpawn = sqrt(dx * dx + dy * dy);

                if (foe.m_idxFoeType == ID_BUTTERFLY || foe.m_idxFoeType == ID_PINKSLIME)
                    break;

            } while (distanceFromSpawn > 5);


            if (pNew.WithinMap())
            {

                if (Global::currentMap->m_2DTiles[pNew.m_x][pNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_groundType != DataLoading::GetDescriptionIndexByName("TileWater")
                    && Global::currentMap->m_2DNPCOwnedLand[pNew.m_x][pNew.m_y] == false)
                {

                    if (!pNew.Equals(p))
                        Global::currentMap->TranslateFoe(uniqueID, p, pNew, SURFACE_FLOOR);
                }
            }
        }
    }
}
