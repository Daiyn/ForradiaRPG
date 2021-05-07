#include "AnimalsRendering.h"
#include "ImageLoading.h"
#include "PlayerActions.h"
#include "Global_Canvas.h"
#include "Global_CurrentMap.h"
#include "Global_SDL.h"
#include <SDL2/SDL_timer.h>
#include "Drawing.h"
#include "Colors.h"
#include "CAnimal.h"
#include "CMap.h"
#include "CTileFloor.h"
#include "CTile.h"

void AnimalsRendering::RenderTileFoes(int x, int y, CPoint pTile)
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

        CAnimal& foe = *Global::contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_containedFoes[i];


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

    }
}