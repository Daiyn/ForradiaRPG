#include "Player.h"
#include "Utilities.h"
#include "KeyboardInput.h"
#include "DataLoading.h"
#include "Global_Canvas.h"
#include "Global_CurrentMap.h"
#include "Global_MapSize.h"
#include <SDL2/SDL_timer.h>
#include "Global_Mouse.h"
#include "Map.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::min;
using std::pair;

Player::Player(int mapSize)
{

    m_coordPosition.m_x = rand() % mapSize;
    m_coordPosition.m_y = rand() % mapSize;

    

}

void Player::MouseClickToMove()
{

    m_coordMoveDestination = Point(HOVERED_TILE);

}

void Player::Update()
{

    UpdateMouseMovement();
    UpdateKeyboardMovement();
    UpdateJumping();

}

void Player::UpdateMouseMovement()
{
    
    if (Global::contentCurrentMap == NULL)
        return;

    if (m_coordMoveDestination.m_x == -1 && m_coordMoveDestination.m_y == -1)
        return;


    Point m_positionNew = m_coordPosition;
        m_positionNew.Translate(Utilities::Normalize(m_coordMoveDestination.m_x, m_coordPosition.m_x), Utilities::Normalize(m_coordMoveDestination.m_y, m_coordPosition.m_y));

    if (m_positionNew.WithinMap())
    {

        bool isObstacle = false;

        if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor() != NULL)
        {

            for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
            {

                int seenFlorIndex = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor();

                if (seenFlorIndex == -1)
                    continue;

                auto& it = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[seenFlorIndex]->m_containedObjects[jjj];

                if (it == nullptr)
                    continue;

                DataDescription& desc = *DataLoading::libDescriptions[it->m_idxObjectType];

                if (desc.m_propAttributes["IsObstacle"] == "true")
                {
                    isObstacle = true;
                    break;
                }

            }

        }

        auto d = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_tickLastMove).count();

        bool tileHasObjects = false;

        for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {
            if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] != NULL)
            {
                tileHasObjects = true;
                break;
            }
        }


        if (!tileHasObjects || !isObstacle)
        {
            if (d > m_spdMovement)
            {

                if (m_coordPosition.m_x != m_positionNew.m_x || m_coordPosition.m_y != m_positionNew.m_y)
                {
                    m_tickLastActualMove = Clock::now();
                    m_tickLastMove = Clock::now();

                    //if (!Global::contentCurrentMap->SeenFloorHasBlockingFoes(m_positionNew.m_x, m_positionNew.m_y))
                    //{

                        int mineElevOld = m_locCurrentElevation;

                        if (Global::contentCurrentMap->TileIsMinedAtElev(m_locCurrentElevation, m_positionNew.m_x, m_positionNew.m_y))
                        {

                        }
                        else if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= m_locCurrentElevation
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x + 1][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                        {
                            m_locCurrentElevation = SURFACE_FLOOR;
                        }
                        else if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight == m_locCurrentElevation
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y - 1]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                        {
                            m_locCurrentElevation = SURFACE_FLOOR;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                                || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight;
                        }
                        else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight;
                        }

                        if (!Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                            m_locCurrentElevation = SURFACE_FLOOR;

                        if (m_locCurrentElevation == SURFACE_FLOOR || Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                            || (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_coordPosition.m_x, m_coordPosition.m_y) && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
                                && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y)))
                        {

                            if (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_coordPosition.m_x, m_coordPosition.m_y) && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
                                && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                                m_locCurrentElevation = SURFACE_FLOOR;

                            if (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y))
                                m_locCurrentElevation = mineElevOld;

                            m_coordPosition.m_x = m_positionNew.m_x;
                            m_coordPosition.m_y = m_positionNew.m_y;

                        }

                    //}

                }

                bool tileHasObjects = false;

                for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
                {
                    if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] != NULL) {
                        tileHasObjects = true;
                        break;
                    }
                }

                if (tileHasObjects)
                    if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectStairsUp"), m_coordPosition.m_x, m_coordPosition.m_y, SURFACE_FLOOR))
                        m_coordWorldSubmap.m_z++;

            }
        }
    }
}


void Player::UpdateKeyboardMovement()
{

    if (Global::contentCurrentMap == NULL)
        return;

    auto d = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_tickLastMove).count();

    if (d > m_spdMovement)
    {

        m_coordMoveDestination.m_x = -1;
        m_coordMoveDestination.m_y = -1;

        Point m_positionNew = m_coordPosition;

        if (KeyboardInput::statesPressedKeys[SDLK_w])
            m_positionNew.m_y--;

        if (KeyboardInput::statesPressedKeys[SDLK_a])
            m_positionNew.m_x--;

        if (KeyboardInput::statesPressedKeys[SDLK_s])
            m_positionNew.m_y++;

        if (KeyboardInput::statesPressedKeys[SDLK_d])
            m_positionNew.m_x++;


        bool isObstacle = false;

        if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor() != NULL)
        {

            for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
            {

                int seenFlorIndex = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor();

                if (seenFlorIndex == -1)
                    continue;

                auto& it = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[seenFlorIndex]->m_containedObjects[jjj];

                if (it == nullptr)
                    continue;

                DataDescription& desc = *DataLoading::libDescriptions[it->m_idxObjectType];

                if (desc.m_propAttributes["IsObstacle"] == "true")
                {
                    isObstacle = true;
                    break;
                }

            }

        }

        bool tileHasObjects = false;

        for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {
            if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] != NULL) {
                tileHasObjects = true;
                break;
            }
        }

        if (!tileHasObjects || !isObstacle) {

            if (m_coordPosition.m_x != m_positionNew.m_x || m_coordPosition.m_y != m_positionNew.m_y)
            {
                m_tickLastActualMove = Clock::now();
                m_tickLastMove = Clock::now();

                //if (!Global::contentCurrentMap->SeenFloorHasBlockingFoes(m_positionNew.m_x, m_positionNew.m_y))
                //{


                    int mineElevOld = m_locCurrentElevation;

                    if (Global::contentCurrentMap->TileIsMinedAtElev(m_locCurrentElevation, m_positionNew.m_x, m_positionNew.m_y))
                    {

                    }
                    else if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= m_locCurrentElevation
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x + 1][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                    {
                        m_locCurrentElevation = SURFACE_FLOOR;
                    }
                    else if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight == m_locCurrentElevation
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y - 1]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                    {
                        m_locCurrentElevation = SURFACE_FLOOR;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                            || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight;
                    }
                    else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
                        || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight;
                    }

                    if (!Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
                        && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                        m_locCurrentElevation = SURFACE_FLOOR;

                    if (m_locCurrentElevation == SURFACE_FLOOR || Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                        || (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_coordPosition.m_x, m_coordPosition.m_y) && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y)))
                    {

                        if (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_coordPosition.m_x, m_coordPosition.m_y) && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
                            && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
                            m_locCurrentElevation = SURFACE_FLOOR;

                        if (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y))
                            m_locCurrentElevation = mineElevOld;

                        m_coordPosition.m_x = m_positionNew.m_x;
                        m_coordPosition.m_y = m_positionNew.m_y;

                    }
                //}

            }

        }

        tileHasObjects = false;

        for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {
            if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] != NULL) {
                tileHasObjects = true;
                break;
            }
        }

        if (tileHasObjects)
            if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectStairsUp"), m_coordPosition.m_x, m_coordPosition.m_y, SURFACE_FLOOR))
                m_coordWorldSubmap.m_z++;

    }

}

//void CPlayer::UpdateCombatMovement()
//{
//
//    if (Global::contentCurrentMap == NULL)
//        return;
//
//    if (Combat::idxTargetedFoe != -1)
//    {
//
//        CAnimal& targetedFoe = Global::contentCurrentMap->m_mirrorAllFoes[Combat::idxTargetedFoe];
//
//        Point m_positionNew = m_coordPosition;
//        m_positionNew.Translate(Utilities::Normalize(targetedFoe.m_coordPosition.m_x, m_coordPosition.m_x), Utilities::Normalize(targetedFoe.m_coordPosition.m_y, m_coordPosition.m_y));
//
//        if (m_positionNew.WithinMap())
//        {
//
//            bool isObstacle = false;
//
//            if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor() != NULL)
//            {
//
//                for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
//                {
//
//                    int seenFlorIndex = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor();
//
//                    if (seenFlorIndex == -1)
//                        continue;
//
//                    auto& it = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[seenFlorIndex]->m_containedObjects[jjj];
//                    
//                    if (it == nullptr)
//                        continue;
//
//                    CDataDescription& desc = *DataLoading::libDescriptions[it->m_idxObjectType];
//
//                    if (desc.m_propAttributes["IsObstacle"] == "true")
//                    {
//                        isObstacle = true;
//                        break;
//                    }
//
//
//                }
//
//            }
//
//            auto d = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_tickLastMove).count();
//
//            bool tileHasObjects = false;
//
//            for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
//            {
//                if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] != NULL) {
//                    tileHasObjects = true;
//                    break;
//                }
//            }
//
//            if (!tileHasObjects || !isObstacle)
//            {
//                if (d > m_spdMovement)
//                {
//
//                    if (m_coordPosition.m_x != m_positionNew.m_x || m_coordPosition.m_y != m_positionNew.m_y)
//                    {
//                        m_tickLastActualMove = Clock::now();
//                        m_tickLastMove = Clock::now();
//
//                        if (!Global::contentCurrentMap->SeenFloorHasBlockingFoes(m_positionNew.m_x, m_positionNew.m_y))
//                        {
//
//                            int mineElevOld = m_locCurrentElevation;
//
//                            if (Global::contentCurrentMap->TileIsMinedAtElev(m_locCurrentElevation, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//
//                            }
//                            else if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= m_locCurrentElevation
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x + 1][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
//                            {
//                                m_locCurrentElevation = SURFACE_FLOOR;
//                            }
//                            else if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight == m_locCurrentElevation
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y - 1]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
//                            {
//                                m_locCurrentElevation = SURFACE_FLOOR;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                         || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y - 1]->m_elevationHeight;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y - 1]->m_elevationHeight;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y ]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y]->m_elevationHeight;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x + 1][m_positionNew.m_y + 1]->m_elevationHeight;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y + 1]->m_elevationHeight;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y + 1]->m_elevationHeight;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y]->m_elevationHeight;
//                            }
//                            else if (Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y)
//                                     || Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight, m_positionNew.m_x, m_positionNew.m_y))
//                            {
//                                m_locCurrentElevation = Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x - 1][m_positionNew.m_y - 1]->m_elevationHeight;
//                            }
//
//                            if (!Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
//                                && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
//                                && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
//                                m_locCurrentElevation = SURFACE_FLOOR;
//
//                            if (m_locCurrentElevation == SURFACE_FLOOR || Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
//                                || (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_coordPosition.m_x, m_coordPosition.m_y) && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
//                                    && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y)))
//                            {
//
//                                if (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_coordPosition.m_x, m_coordPosition.m_y) && Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_elevationHeight <= mineElevOld
//                                    && Global::contentCurrentMap->TileIsMinedAtElev(Global::contentCurrentMap->m_tilesGrid[m_coordPosition.m_x][m_coordPosition.m_y]->m_elevationHeight, m_coordPosition.m_x, m_coordPosition.m_y))
//                                    m_locCurrentElevation = SURFACE_FLOOR;
//
//                                if (Global::contentCurrentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y))
//                                    m_locCurrentElevation = mineElevOld;
//
//                                m_coordPosition.m_x = m_positionNew.m_x;
//                                m_coordPosition.m_y = m_positionNew.m_y;
//
//                            }
//
//                        }
//
//                    }
//
//                    bool tileHasObjects = false;
//
//                    for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
//                    {
//                        if (Global::contentCurrentMap->m_tilesGrid[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] != NULL) {
//                            tileHasObjects = true;
//                            break;
//                        }
//                    }
//
//                    if (tileHasObjects)
//                        if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectStairsUp"), m_coordPosition.m_x, m_coordPosition.m_y, SURFACE_FLOOR))
//                            m_coordWorldSubmap.m_z++;
//
//                }
//            }
//        }
//    }
//}

void Player::Jump()
{
    m_tickStartJump = SDL_GetTicks();
}


int Player::GetJumpHeight()
{

    if (IsJumping())
    {

        int delta = SDL_GetTicks() - m_tickStartJump;
        delta -= m_duraJumping / 2;
        int m = (m_duraJumping / 2) * (m_duraJumping / 2) / 100;
        int y = -delta * delta / 100 + m;
        y /= 10;

        return y;

    }

    return 0;
}

void Player::UpdateJumping()
{

    if (KeyboardInput::statesPressedKeys[SDLK_SPACE] && !IsJumping())
    {

        Jump();
        KeyboardInput::statesPressedKeys[SDLK_SPACE] = false;

    }

}

bool Player::IsJumping() {
    return SDL_GetTicks() - m_tickStartJump < m_duraJumping;
}

bool Player::ConsumeNRGY(int nrgyAmount)
{
    if (m_statCurrentNRGY < nrgyAmount)
        return false;

    m_statCurrentNRGY -= nrgyAmount;

    return true;
}

void Player::AddNRGY(double nrgyAmount)
{
    m_statCurrentNRGY = min(m_statCurrentNRGY + nrgyAmount, m_statMaxNRGY);
}