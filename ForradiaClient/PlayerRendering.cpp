#include "PlayerRendering.h"
#include "ImageLoading.h"
#include "Combat.h"
#include <chrono>
#include "Global_Canvas.h"
#include "Global_Player.h"
#include "Global_SDL.h"
#include "CSize.h"
#include "Drawing.h"
#include "CPlayer.h"

using namespace std::chrono;

typedef high_resolution_clock Clock;

void PlayerRendering::RenderPlayer(int x, int y, CPoint pTile)
{

    SDL_Rect rTile = { x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(), Global::GetTileSize() };

    if (pTile.m_x == Global::statePlayer->m_coordPosition.m_x && pTile.m_y == Global::statePlayer->m_coordPosition.m_y)
    {

        CSize szPlayer(1.5 * Global::GetTileSize());
        CSize szShadow(1.5 * Global::GetTileSize());

        CRectangle rectShadow = {x * Global::GetTileSize() + Global::GetTileSize() / 2 - szShadow.m_w / 2,
                               y * Global::GetTileSize() + Global::GetTileSize() + Global::GetTileSize() / 2 - szShadow.m_h,
                                szShadow.m_w,
                                szShadow .m_h};

        CRectangle rectPlayer = { x * Global::GetTileSize() + Global::GetTileSize() / 2 - szPlayer.m_w / 2,
                               y * Global::GetTileSize() + Global::GetTileSize() - szPlayer.m_h,
                                szPlayer.m_w,
                                szPlayer.m_h };

        rectPlayer.y -= Global::statePlayer->GetJumpHeight();

        Drawing::Image(ID_SHADOW, rectShadow);
        Drawing::Image(ID_PLAYER, rectPlayer);

        if (SDL_GetTicks() - Combat::tickCombatInitiated < Combat::duraShowHitEffect)
        {

            CRectangle rTileHitEffect = {
                    x * Global::GetTileSize(),
                    y * Global::GetTileSize(),
                    Global::GetTileSize(),
                    Global::GetTileSize()
            };

            Drawing::Image(ID_HIT_EFFECT, rTileHitEffect);

        }

    }
}