#include "FoesRendering.h"
#include "Combat.h"
#include "ImageLoading.h"
#include "PlayerActions.h"
#include "Global_Canvas.h"
#include "Global_CurrentMap.h"
#include "Global_SDL.h"
#include <SDL2/SDL_timer.h>
#include "Drawing.h"
#include "Colors.h"
#include "CFoe.h"
#include "CMap.h"
#include "CTileFloor.h"
#include "CTile.h"

void FoesRendering::RenderTileFoes(int x, int y, CPoint pTile)
{

    int seenFloorIndex = Global::currentMap->m_2DTiles[pTile.m_x][pTile.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    if (!Global::currentMap->SeenFloorHasFoes(pTile.m_x, pTile.m_y))
        return;

    CRectangle rTile = { x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(), Global::GetTileSize() };

    for (int i = 0; i < CTileFloor::MAX_FOES_ON_FLOOR; i++)
    {

        if (Global::currentMap->m_2DTiles[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_floorFoesArr[i] == nullptr)
            continue;

        CFoe& foe = *Global::currentMap->m_2DTiles[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_floorFoesArr[i];

        if (!foe.IsAlive())
            continue;

        if (Combat::idxTargetedFoe != -1)
        {

            CFoe& targetedFoe = Global::currentMap->m_allFoesArray[Combat::idxTargetedFoe];

            if (foe.m_uniqueId == targetedFoe.m_uniqueId)
                Drawing::Image(ID_TILE_TARGET_EFFECT, rTile);

        }

        int imgWidth = 1 * Global::GetTileSize();
        int imgHeight = 1 * Global::GetTileSize();

        int shadowWidth = 1.5 * Global::GetTileSize();
        int shadowHeight = 1.5 * Global::GetTileSize();

        CRectangle rectShadow = { x * Global::GetTileSize() + Global::GetTileSize() / 2 - shadowWidth / 2,
                              y * Global::GetTileSize() + Global::GetTileSize() - shadowHeight, shadowWidth,
                              shadowHeight };

        Drawing::Image(ID_SHADOW, rectShadow);

        int foeTypeIndex;

        switch (foe.m_idxFoeType)
        {
        case 1:
        case 2:

            imgWidth = 1.5 * Global::GetTileSize();
            imgHeight = 1.5 * Global::GetTileSize();

            foeTypeIndex = ID_FOE;

            break;

        case ID_BUTTERFLY:

            imgWidth = 1.5 * Global::GetTileSize();
            imgHeight = 1.5 * Global::GetTileSize();

            foeTypeIndex = ID_BUTTERFLY;

            break;

        case ID_PINKSLIME:

            imgWidth = 1.5 * Global::GetTileSize();
            imgHeight = 1.5 * Global::GetTileSize();

            foeTypeIndex = ID_PINKSLIME;

            break;

        }

        rTile = {
                    x * Global::GetTileSize() + Global::GetTileSize() / 2 - imgWidth / 2,
                    y * Global::GetTileSize() + Global::GetTileSize() - imgHeight,
                    imgWidth,
                    imgHeight
        };

        Drawing::Image(foeTypeIndex, rTile);

        if (Combat::idxTargetedFoe != -1)
        {

            CFoe& targetedFoe = Global::currentMap->m_allFoesArray[Combat::idxTargetedFoe];

            if (foe.m_uniqueId == targetedFoe.m_uniqueId)
            {

                CRectangle rTileHitEffect = {
                        x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(),
                        Global::GetTileSize()
                };

                if (SDL_GetTicks() - Combat::tickCombatInitiated < Combat::duraShowHitEffect)
                {

                    Drawing::Image(ID_HIT_EFFECT, rTileHitEffect);

                }

            }

        }

        if (SDL_GetTicks() - foe.m_tickTimeToRespawn < 240)
        {
            int animIndex3 = (SDL_GetTicks() - foe.m_tickTimeToRespawn) / 80;


            imgWidth = 1.5 * Global::GetTileSize();
            imgHeight = 1.5 * Global::GetTileSize();

            rTile = { x * Global::GetTileSize() + Global::GetTileSize() / 2 - imgWidth / 2,
                    y * Global::GetTileSize() + Global::GetTileSize() - imgHeight,
                    imgWidth,
                    imgHeight };

            switch (animIndex3)
            {
            case 0:
                Drawing::Image(ID_SPAWN_EFFECT_0, rTile);
                break;
            case 1:
                Drawing::Image(ID_SPAWN_EFFECT_1, rTile);
                break;
            case 2:
                Drawing::Image(ID_SPAWN_EFFECT_2, rTile);
                break;
            }

        }

        if (pTile.m_x == PlayerActions::hoveredTile.m_x && pTile.m_y == PlayerActions::hoveredTile.m_y
            || (Combat::idxTargetedFoe != -1 && foe.m_uniqueId == Global::currentMap->m_allFoesArray[Combat::idxTargetedFoe].get().m_uniqueId))
        {
            int foeHpBarHeight = 10;
            int foeHpBarWidth = 1.5 * Global::GetTileSize();
            int foeHeight = (int)(3.0f * Global::GetTileSize());

            CRectangle rect = { x * Global::GetTileSize() + Global::GetTileSize() / 2 - foeHpBarWidth / 2,
                             y * Global::GetTileSize() + Global::GetTileSize() + Global::GetTileSize() / 2,
                             foeHpBarWidth, foeHpBarHeight };

            Drawing::FilledRect(BLACK, rect);

            if (foe.m_hpCurrent > 0)
            {
                int foeHpBarFilledWidth = (int)((float)foe.m_hpCurrent / foe.m_hpMax * foeHpBarWidth);

                rect = {
                        x * Global::GetTileSize() + Global::GetTileSize() / 2 - foeHpBarWidth / 2,
                        y * Global::GetTileSize() + Global::GetTileSize() + Global::GetTileSize() / 2,
                        foeHpBarFilledWidth, foeHpBarHeight
                };

                Drawing::FilledRect(GREEN, rect);
            }
        }
    }
}