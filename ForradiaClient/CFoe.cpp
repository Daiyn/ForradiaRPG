#include "CFoe.h"
#include <cstdlib>
#include <SDL2/SDL_timer.h>

int CFoe::s_idCountFoes = 0;

CFoe::CFoe(int _foeType, int _mapx, int _mapy) : CFightableCharacter(10, CHARACTER_TYPE_FOE)
{

    m_idxFoeType = _foeType;
    m_coordPosition = { _mapx, _mapy };
    m_coordSpawn.m_x = _mapx;
    m_coordSpawn.m_y = _mapy;
    m_uniqueID = s_idCountFoes;

    s_idCountFoes++;

}

bool CFoe::IsAlive()
{

    return SDL_GetTicks() > m_tickTimeToRespawn && m_statCurrentHP > 0;

}
