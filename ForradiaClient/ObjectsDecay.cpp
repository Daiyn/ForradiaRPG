#include "ObjectsDecay.h"
#include <vector>
#include "CObject.h"
#include "Global_CurrentMap.h"
#include "CMap.h"
#include <SDL2/SDL_timer.h>
#include "CTile.h"

void ObjectsDecay::Update()
{


    int vanishEffectDuration = 3000;
    std::vector<CObject *> objectsToRemove;

    for (auto it = Global::currentMap->m_listChangingObject.begin(); it != Global::currentMap->m_listChangingObject.end(); it++)
    {
        if (SDL_GetTicks() > (*it).m_tickTimeToVanish)
        {
            if (SDL_GetTicks() > (*it).m_tickTimeToVanish + vanishEffectDuration)
            {

                Global::currentMap->m_2DTiles[(*it).m_2DMapX][(*it).m_2DMapY]->m_floorsArray[SURFACE_FLOOR]->DeleteObjectWithId((*it).m_uniqueID);

                Global::currentMap->m_listChangingObject.erase(it);
                break;

            }
            else
            {

                int vanishingEffectAnimIndex = ((SDL_GetTicks() - (*it).m_tickTimeToVanish) % 750) / 125;
                (*it).m_idxVanishingEffect = vanishingEffectAnimIndex;

                int index = Global::currentMap->m_2DTiles[(*it).m_2DMapX][(*it).m_2DMapY]->m_floorsArray[SURFACE_FLOOR]->GetObjectIndexWithId((*it).m_uniqueID);
                if (index != -1)
                    Global::currentMap->m_2DTiles[(*it).m_2DMapX][(*it).m_2DMapY]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[index]->m_idxVanishingEffect = vanishingEffectAnimIndex;

            }
        }
    }
}
