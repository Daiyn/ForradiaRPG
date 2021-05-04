#include "CFoe.h"
#include <cstdlib>
#include <SDL2/SDL_timer.h>

int CFoe::s_idCountFoes = 0;

CFoe::CFoe(int _foeType, int _mapx, int _mapy) : CFightableCharacter(10, CHARACTER_TYPE_FOE)
{

    m_idxFoeType = _foeType;
    m_posCurrent = { _mapx, _mapy };
    m_posSpawn.m_x = _mapx;
    m_posSpawn.m_y = _mapy;
    m_uniqueId = s_idCountFoes;

    s_idCountFoes++;

}

bool CFoe::IsAlive() {

    return SDL_GetTicks() > m_tickTimeToRespawn && m_hpCurrent > 0;

}
