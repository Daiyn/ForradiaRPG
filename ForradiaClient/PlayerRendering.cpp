#include "PlayerRendering.h"
#include "ImageLoading.h"
#include <chrono>
#include "Global_Canvas.h"
#include "Global_Player.h"
#include "Global_SDL.h"
#include "Size.h"
#include "Drawing.h"
#include "Player.h"

using namespace std::chrono;

typedef high_resolution_clock Clock;

void PlayerRendering::RenderPlayer(int x, int y, Point pTile)
{

    SDL_Rect rTile = { x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(), Global::GetTileSize() };

    if (pTile.m_x == Global::statePlayer->m_coordPosition.m_x && pTile.m_y == Global::statePlayer->m_coordPosition.m_y)
    {

        Size szPlayer(1.5 * Global::GetTileSize());
        Size szShadow(1.5 * Global::GetTileSize());

        Rectangle rectShadow = {x * Global::GetTileSize() + Global::GetTileSize() / 2 - szShadow.m_w / 2,
                               y * Global::GetTileSize() + Global::GetTileSize() - szShadow.m_h,
                                szShadow.m_w,
                                szShadow .m_h};

        Rectangle rectPlayer = { x * Global::GetTileSize() + Global::GetTileSize() / 2 - szPlayer.m_w / 2,
                               y * Global::GetTileSize() + Global::GetTileSize() - szPlayer.m_h,
                                szPlayer.m_w,
                                szPlayer.m_h };

        rectPlayer.y -= Global::statePlayer->GetJumpHeight();

        Drawing::Image(ImagesIDs::Shadow, rectShadow);
        Drawing::Image(ImagesIDs::PlayerSprite, rectPlayer);

        //if (SDL_GetTicks() - Combat::tickCombatInitiated < Combat::duraShowHitEffect)
        //{

        //    CRectangle rTileHitEffect = {
        //            x * Global::GetTileSize(),
        //            y * Global::GetTileSize(),
        //            Global::GetTileSize(),
        //            Global::GetTileSize()
        //    };

        //    Drawing::Image(kIDHitEffect, rTileHitEffect);

        //}

    }
}