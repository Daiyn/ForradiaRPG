#include "CTile.h"
#include "Global_Player.h"
#include "CPlayer.h"


int CTile::GetIndexForSeenFloor()
{

    if (Global::player == nullptr)
        return SURFACE_FLOOR;

    if (Global::player->m_elevCurrent == SURFACE_FLOOR)
        return SURFACE_FLOOR;
    else if (m_floorsArray[Global::player->m_elevCurrent] != nullptr)
            return Global::player->m_elevCurrent;

    return -1;

}