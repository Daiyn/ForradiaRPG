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

    for (auto it = Global::contentCurrentMap->m_objectsWithUpdateNeed.begin(); it != Global::contentCurrentMap->m_objectsWithUpdateNeed.end(); it++)
    {
        if (SDL_GetTicks() > (*it).m_tickTimeToVanish)
        {
            if (SDL_GetTicks() > (*it).m_tickTimeToVanish + vanishEffectDuration)
            {

                Global::contentCurrentMap->m_tilesGrid[(*it).m_coordMapX][(*it).m_coordMapY]->m_floorsArray[SURFACE_FLOOR]->DeleteObjectWithId((*it).m_uniqueID);

                Global::contentCurrentMap->m_objectsWithUpdateNeed.erase(it);
                break;

            }
            else
            {

                int vanishingEffectAnimIndex = ((SDL_GetTicks() - (*it).m_tickTimeToVanish) % 750) / 125;
                (*it).m_idxVanishingEffect = vanishingEffectAnimIndex;

                int index = Global::contentCurrentMap->m_tilesGrid[(*it).m_coordMapX][(*it).m_coordMapY]->m_floorsArray[SURFACE_FLOOR]->GetObjectIndexWithId((*it).m_uniqueID);
                if (index != -1)
                    Global::contentCurrentMap->m_tilesGrid[(*it).m_coordMapX][(*it).m_coordMapY]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[index]->m_idxVanishingEffect = vanishingEffectAnimIndex;

            }
        }
    }
}
