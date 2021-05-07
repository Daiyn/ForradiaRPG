#include "CAnimal.h"
#include <cstdlib>
#include <SDL2/SDL_timer.h>

int CAnimal::s_idCountFoes = 0;

CAnimal::CAnimal(int _foeType, int _mapx, int _mapy)
{

    m_idxFoeType = _foeType;
    m_coordPosition = { _mapx, _mapy };
    m_coordSpawn.m_x = _mapx;
    m_coordSpawn.m_y = _mapy;
    m_uniqueID = s_idCountFoes;

    s_idCountFoes++;

}
