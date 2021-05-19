#include "Tile.h"
#include "Global_Player.h"
#include "Player.h"

int Tile::GetIndexForSeenFloor()
{

    if (Global::statePlayer == nullptr)
        return SURFACE_FLOOR;

    if (Global::statePlayer->m_locCurrentElevation == SURFACE_FLOOR)
        return SURFACE_FLOOR;
    else if (m_floorsArray[Global::statePlayer->m_locCurrentElevation] != nullptr)
            return Global::statePlayer->m_locCurrentElevation;

    return -1;

}