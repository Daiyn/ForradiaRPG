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

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    if (!Global::contentCurrentMap->SeenFloorHasFoes(pTile.m_x, pTile.m_y))
        return;

    CRectangle rTile = { x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(), Global::GetTileSize() };

    for (int i = 0; i < CTileFloor::MAX_FOES_ON_FLOOR; i++)
    {

        if (Global::contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_containedFoes[i] == nullptr)
            continue;

        CFoe& foe = *Global::contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_containedFoes[i];

        if (!foe.IsAlive())
            continue;

        if (Combat::idxTargetedFoe != -1)
        {

            CFoe& targetedFoe = Global::contentCurrentMap->m_mirrorAllFoes[Combat::idxTargetedFoe];

            if (foe.m_uniqueID == targetedFoe.m_uniqueID)
                Drawing::Image(kIDTileTargetEffect, rTile);

        }

        int imgWidth = 1 * Global::GetTileSize();
        int imgHeight = 1 * Global::GetTileSize();

        int shadowWidth = 1.5 * Global::GetTileSize();
        int shadowHeight = 1.5 * Global::GetTileSize();

        CRectangle rectShadow = { x * Global::GetTileSize() + Global::GetTileSize() / 2 - shadowWidth / 2,
                              y * Global::GetTileSize() + Global::GetTileSize() - shadowHeight, shadowWidth,
                              shadowHeight };

        Drawing::Image(kIDShadow, rectShadow);

        int foeTypeIndex;

        switch (foe.m_idxFoeType)
        {
        case 1:
        case 2:

            imgWidth = 1.5 * Global::GetTileSize();
            imgHeight = 1.5 * Global::GetTileSize();

            foeTypeIndex = kIDFoe;

            break;

        case kIDButterfly:

            imgWidth = 1.5 * Global::GetTileSize();
            imgHeight = 1.5 * Global::GetTileSize();

            foeTypeIndex = kIDButterfly;

            break;

        case kIDPinkSlime:

            imgWidth = 1.5 * Global::GetTileSize();
            imgHeight = 1.5 * Global::GetTileSize();

            foeTypeIndex = kIDPinkSlime;

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

            CFoe& targetedFoe = Global::contentCurrentMap->m_mirrorAllFoes[Combat::idxTargetedFoe];

            if (foe.m_uniqueID == targetedFoe.m_uniqueID)
            {

                CRectangle rTileHitEffect = {
                        x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(),
                        Global::GetTileSize()
                };

                if (SDL_GetTicks() - Combat::tickCombatInitiated < Combat::duraShowHitEffect)
                {

                    Drawing::Image(kIDHitEffect, rTileHitEffect);

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
                Drawing::Image(kIDSpawnEffect0, rTile);
                break;
            case 1:
                Drawing::Image(kIDSpawnEffect1, rTile);
                break;
            case 2:
                Drawing::Image(kIDSpawnEffect2, rTile);
                break;
            }

        }

        if (pTile.m_x == PlayerActions::coordHoveredTile.m_x && pTile.m_y == PlayerActions::coordHoveredTile.m_y
            || (Combat::idxTargetedFoe != -1 && foe.m_uniqueID == Global::contentCurrentMap->m_mirrorAllFoes[Combat::idxTargetedFoe].get().m_uniqueID))
        {
            int foeHpBarHeight = 10;
            int foeHpBarWidth = 1.5 * Global::GetTileSize();
            int foeHeight = (int)(3.0f * Global::GetTileSize());

            CRectangle rect = { x * Global::GetTileSize() + Global::GetTileSize() / 2 - foeHpBarWidth / 2,
                             y * Global::GetTileSize() + Global::GetTileSize() + Global::GetTileSize() / 2,
                             foeHpBarWidth, foeHpBarHeight };

            Drawing::FilledRect(BLACK, rect);

            if (foe.m_statCurrentHP > 0)
            {
                int foeHpBarFilledWidth = (int)((float)foe.m_statCurrentHP / foe.m_statMaxHP * foeHpBarWidth);

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