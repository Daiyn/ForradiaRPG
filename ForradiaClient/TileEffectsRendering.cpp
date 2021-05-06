#include "TileEffectsRendering.h"
#include "PlayerActions.h"
#include "ImageLoading.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include <SDL2/SDL_timer.h>



void TileEffectsRendering::RenderTileEffects(int x, int y, CPoint pTile)
{

    SDL_Rect rTile = { x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(), Global::GetTileSize() };

    for (auto it = PlayerActions::coordsSkillAffectedTiles.begin();
         it != PlayerActions::coordsSkillAffectedTiles.end(); it++)
    {

        if (pTile.m_x == it->x && pTile.m_y == it->y)
        {

            SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDSkillEffectA], NULL, &rTile);

            SDL_Rect rectSkill = {x * Global::GetTileSize() + Global::GetTileSize() / 2 - Global::GetTileSize(),
                                  y * Global::GetTileSize() + Global::GetTileSize() - 4 * Global::GetTileSize(),
                                  2 * Global::GetTileSize(), 4 * Global::GetTileSize()};

            int skillEffectAnim = (SDL_GetTicks() - PlayerActions::tickStartSkillPerform) / 50;

            if (skillEffectAnim <= 3)
            {

                switch (skillEffectAnim)
                {
                case 0:
                    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDSkillEffectB0], NULL, &rectSkill);
                    break;
                case 1:
                    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDSkillEffectB1], NULL, &rectSkill);
                    break;
                case 2:
                    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDSkillEffectB2], NULL, &rectSkill);
                    break;
                }

            }

            break;

        }
    }
}