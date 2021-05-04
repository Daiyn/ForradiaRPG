#include "CPlayer.h"
#include "Utilities.h"
#include "KeyboardInput.h"
#include "Combat.h"
#include "DataLoading.h"
#include "Global_Canvas.h"
#include "Global_CurrentMap.h"
#include "Global_MapSize.h"
#include <SDL2/SDL_timer.h>
#include "Global_Mouse.h"
#include "CMap.h"

using std::min;

CPlayer::CPlayer(int mapSize) : CFightableCharacter(100, CHARACTER_TYPE_PLAYER)
{

    m_posCurrent.m_x = rand() % mapSize;
    m_posCurrent.m_y = rand() % mapSize;

    int indexApple = DataLoading::GetDescriptionIndexByName("ObjectApple");
    int indexStone = DataLoading::GetDescriptionIndexByName("ObjectStone");
    int indexWoodLog = DataLoading::GetDescriptionIndexByName("ObjectWoodLog");
    int indexShovel = DataLoading::GetDescriptionIndexByName("ObjectShovel");
    int indexMatches = DataLoading::GetDescriptionIndexByName("ObjectMatches");

    m_inventory.m_belongingCollection.insert(std::pair<int, CObject*>(0, new CObject(indexApple, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY })));
    m_inventory.m_belongingCollection.insert(std::pair<int, CObject*>(2, new CObject(indexApple, {OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY })));

    m_inventory.m_belongingCollection.insert(std::pair<int, CObject*>(5, new CObject(indexStone, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }, 5)));

    m_inventory.m_belongingCollection.insert(std::pair<int, CObject*>(15, new CObject(indexWoodLog, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY })));

    m_inventory.m_belongingCollection.insert(std::pair<int, CObject*>(17, new CObject(indexShovel, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY })));
    m_inventory.m_belongingCollection.insert(std::pair<int, CObject*>(18, new CObject(indexMatches, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY })));

}

void CPlayer::MouseClickToMove()
{

    m_posMoveDestination = CPoint(HOVERED_TILE);

}

void CPlayer::Update()
{

    UpdateCombatMovement();
    UpdateMouseMovement();
    UpdateKeyboardMovement();
    UpdateJumping();

}

void CPlayer::UpdateMouseMovement()
{
    
    if (Global::currentMap == NULL)
        return;

    if (m_posMoveDestination.m_x == -1 && m_posMoveDestination.m_y == -1)
        return;

    

    Combat::idxTargetedFoe = -1;


    CPoint m_positionNew = m_posCurrent;
        m_positionNew.Translate(Utilities::Normalize(m_posMoveDestination.m_x, m_posCurrent.m_x), Utilities::Normalize(m_posMoveDestination.m_y, m_posCurrent.m_y));

    if (m_positionNew.WithinMap())
    {

        bool isObstacle = false;

        if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor() != NULL)
        {

            for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
            {

                int seenFlorIndex = Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor();

                if (seenFlorIndex == -1)
                    continue;

                auto& it = Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[seenFlorIndex]->m_floorObjectsArr[jjj];

                if (it == nullptr)
                    continue;

                CDataDescription& desc = *DataLoading::descriptions[it->m_idxObjectType];

                if (desc.m_propAttributes["IsObstacle"] == "True")
                {
                    isObstacle = true;
                    break;
                }

            }

        }

        auto d = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_tickLastMove).count();

        bool tileHasObjects = false;

        for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {
            if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] != NULL)
            {
                tileHasObjects = true;
                break;
            }
        }


        if (!tileHasObjects || !isObstacle)
        {
            if (d > m_spdMovement)
            {

                if (m_posCurrent.m_x != m_positionNew.m_x || m_posCurrent.m_y != m_positionNew.m_y)
                {
                    m_tickLastActualMove = Clock::now();
                    m_tickLastMove = Clock::now();

                    if (!Global::currentMap->SeenFloorHasBlockingFoes(m_positionNew.m_x, m_positionNew.m_y))
                    {

                        int mineElevOld = m_elevCurrent;

                        if (Global::currentMap->TileIsMinedAtElev(m_elevCurrent, m_positionNew.m_x, m_positionNew.m_y))
                        {

                        }
                        else if (Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= m_elevCurrent
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x + 1][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                        {
                            m_elevCurrent = SURFACE_FLOOR;
                        }
                        else if (Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] == m_elevCurrent
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y - 1], m_posCurrent.m_x, m_posCurrent.m_y))
                        {
                            m_elevCurrent = SURFACE_FLOOR;
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                            && (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1];
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1];
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y];
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1];
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1];
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1];
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y];
                        }
                        else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y))
                        {
                            m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1];
                        }

                        if (!Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                            && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                            m_elevCurrent = SURFACE_FLOOR;

                        if (m_elevCurrent == SURFACE_FLOOR || Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                            || (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_posCurrent.m_x, m_posCurrent.m_y) && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                                && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y)))
                        {

                            if (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_posCurrent.m_x, m_posCurrent.m_y) && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                                && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                                m_elevCurrent = SURFACE_FLOOR;

                            if (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y))
                                m_elevCurrent = mineElevOld;

                            m_posCurrent.m_x = m_positionNew.m_x;
                            m_posCurrent.m_y = m_positionNew.m_y;

                        }

                    }

                }

                bool tileHasObjects = false;

                for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
                {
                    if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] != NULL) {
                        tileHasObjects = true;
                        break;
                    }
                }

                if (tileHasObjects)
                    if (Global::currentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectStairsUp"), m_posCurrent.m_x, m_posCurrent.m_y, SURFACE_FLOOR))
                        m_coordWorldSubmap.z++;

            }
        }
    }
}


void CPlayer::UpdateKeyboardMovement()
{

    if (Global::currentMap == NULL)
        return;

    auto d = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_tickLastMove).count();

    if (d > m_spdMovement)
    {

        m_posMoveDestination.m_x = -1;
        m_posMoveDestination.m_y = -1;

        CPoint m_positionNew = m_posCurrent;

        if (KeyboardInput::pressedKeys[SDLK_w])
            m_positionNew.m_y--;

        if (KeyboardInput::pressedKeys[SDLK_a])
            m_positionNew.m_x--;

        if (KeyboardInput::pressedKeys[SDLK_s])
            m_positionNew.m_y++;

        if (KeyboardInput::pressedKeys[SDLK_d])
            m_positionNew.m_x++;


        bool isObstacle = false;

        if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor() != NULL)
        {

            for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
            {

                int seenFlorIndex = Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor();

                if (seenFlorIndex == -1)
                    continue;

                auto& it = Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[seenFlorIndex]->m_floorObjectsArr[jjj];

                if (it == nullptr)
                    continue;

                CDataDescription& desc = *DataLoading::descriptions[it->m_idxObjectType];

                if (desc.m_propAttributes["IsObstacle"] == "True")
                {
                    isObstacle = true;
                    break;
                }

            }

        }

        bool tileHasObjects = false;

        for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {
            if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] != NULL) {
                tileHasObjects = true;
                break;
            }
        }

        if (!tileHasObjects || !isObstacle) {

            if (m_posCurrent.m_x != m_positionNew.m_x || m_posCurrent.m_y != m_positionNew.m_y)
            {
                m_tickLastActualMove = Clock::now();
                m_tickLastMove = Clock::now();

                if (!Global::currentMap->SeenFloorHasBlockingFoes(m_positionNew.m_x, m_positionNew.m_y))
                {


                    int mineElevOld = m_elevCurrent;

                    if (Global::currentMap->TileIsMinedAtElev(m_elevCurrent, m_positionNew.m_x, m_positionNew.m_y))
                    {

                    }
                    else if (Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= m_elevCurrent
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x + 1][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                    {
                        m_elevCurrent = SURFACE_FLOOR;
                    }
                    else if (Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] == m_elevCurrent
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y - 1], m_posCurrent.m_x, m_posCurrent.m_y))
                    {
                        m_elevCurrent = SURFACE_FLOOR;
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                        && (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                            || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1];
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1];
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y];
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1];
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1];
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1];
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y];
                    }
                    else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                        || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y))
                    {
                        m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1];
                    }

                    if (!Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                        && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                        && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                        m_elevCurrent = SURFACE_FLOOR;

                    if (m_elevCurrent == SURFACE_FLOOR || Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                        || (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_posCurrent.m_x, m_posCurrent.m_y) && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y)))
                    {

                        if (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_posCurrent.m_x, m_posCurrent.m_y) && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                            && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                            m_elevCurrent = SURFACE_FLOOR;

                        if (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y))
                            m_elevCurrent = mineElevOld;

                        m_posCurrent.m_x = m_positionNew.m_x;
                        m_posCurrent.m_y = m_positionNew.m_y;

                    }
                }

            }

        }

        tileHasObjects = false;

        for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {
            if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] != NULL) {
                tileHasObjects = true;
                break;
            }
        }

        if (tileHasObjects)
            if (Global::currentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectStairsUp"), m_posCurrent.m_x, m_posCurrent.m_y, SURFACE_FLOOR))
                m_coordWorldSubmap.z++;

    }

}

void CPlayer::UpdateCombatMovement()
{

    if (Global::currentMap == NULL)
        return;

    if (Combat::idxTargetedFoe != -1)
    {

        CFoe& targetedFoe = Global::currentMap->m_allFoesArray[Combat::idxTargetedFoe];

        CPoint m_positionNew = m_posCurrent;
        m_positionNew.Translate(Utilities::Normalize(targetedFoe.m_posCurrent.m_x, m_posCurrent.m_x), Utilities::Normalize(targetedFoe.m_posCurrent.m_y, m_posCurrent.m_y));

        if (m_positionNew.WithinMap())
        {

            bool isObstacle = false;

            if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor() != NULL)
            {

                for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
                {

                    int seenFlorIndex = Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->GetIndexForSeenFloor();

                    if (seenFlorIndex == -1)
                        continue;

                    auto& it = Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[seenFlorIndex]->m_floorObjectsArr[jjj];
                    
                    if (it == nullptr)
                        continue;

                    CDataDescription& desc = *DataLoading::descriptions[it->m_idxObjectType];

                    if (desc.m_propAttributes["IsObstacle"] == "True")
                    {
                        isObstacle = true;
                        break;
                    }


                }

            }

            auto d = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_tickLastMove).count();

            bool tileHasObjects = false;

            for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
            {
                if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] != NULL) {
                    tileHasObjects = true;
                    break;
                }
            }

            if (!tileHasObjects || !isObstacle)
            {
                if (d > m_spdMovement)
                {

                    if (m_posCurrent.m_x != m_positionNew.m_x || m_posCurrent.m_y != m_positionNew.m_y)
                    {
                        m_tickLastActualMove = Clock::now();
                        m_tickLastMove = Clock::now();

                        if (!Global::currentMap->SeenFloorHasBlockingFoes(m_positionNew.m_x, m_positionNew.m_y))
                        {

                            int mineElevOld = m_elevCurrent;

                            if (Global::currentMap->TileIsMinedAtElev(m_elevCurrent, m_positionNew.m_x, m_positionNew.m_y))
                            {

                            }
                            else if (Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= m_elevCurrent
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x + 1][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                            {
                                m_elevCurrent = SURFACE_FLOOR;
                            }
                            else if (Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] == m_elevCurrent
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y - 1], m_posCurrent.m_x, m_posCurrent.m_y))
                            {
                                m_elevCurrent = SURFACE_FLOOR;
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                                     && (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                         || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y - 1];
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y - 1];
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y ], m_positionNew.m_x, m_positionNew.m_y)
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y];
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x + 1][m_positionNew.m_y + 1];
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y + 1];
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y)
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1], m_positionNew.m_x, m_positionNew.m_y))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y + 1];
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y];
                            }
                            else if (Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y)
                                     && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y], m_positionNew.m_x, m_positionNew.m_y)
                                     || Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1], m_positionNew.m_x, m_positionNew.m_y))
                            {
                                m_elevCurrent = Global::currentMap->m_2DElevation[m_positionNew.m_x - 1][m_positionNew.m_y - 1];
                            }

                            if (!Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                                && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                                && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                                m_elevCurrent = SURFACE_FLOOR;

                            if (m_elevCurrent == SURFACE_FLOOR || Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y)
                                || (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_posCurrent.m_x, m_posCurrent.m_y) && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                                    && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y)))
                            {

                                if (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_posCurrent.m_x, m_posCurrent.m_y) && Global::currentMap->m_2DElevation[m_positionNew.m_x][m_positionNew.m_y] <= mineElevOld
                                    && Global::currentMap->TileIsMinedAtElev(Global::currentMap->m_2DElevation[m_posCurrent.m_x][m_posCurrent.m_y], m_posCurrent.m_x, m_posCurrent.m_y))
                                    m_elevCurrent = SURFACE_FLOOR;

                                if (Global::currentMap->TileIsMinedAtElev(mineElevOld, m_positionNew.m_x, m_positionNew.m_y))
                                    m_elevCurrent = mineElevOld;

                                m_posCurrent.m_x = m_positionNew.m_x;
                                m_posCurrent.m_y = m_positionNew.m_y;

                            }

                        }

                    }

                    bool tileHasObjects = false;

                    for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
                    {
                        if (Global::currentMap->m_2DTiles[m_positionNew.m_x][m_positionNew.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] != NULL) {
                            tileHasObjects = true;
                            break;
                        }
                    }

                    if (tileHasObjects)
                        if (Global::currentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectStairsUp"), m_posCurrent.m_x, m_posCurrent.m_y, SURFACE_FLOOR))
                            m_coordWorldSubmap.z++;

                }
            }
        }
    }
}

void CPlayer::Jump()
{
    m_tickStartJump = SDL_GetTicks();
}


int CPlayer::GetJumpHeight()
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

void CPlayer::UpdateJumping()
{

    if (KeyboardInput::pressedKeys[SDLK_SPACE] && !IsJumping())
    {

        Jump();
        KeyboardInput::pressedKeys[SDLK_SPACE] = false;

    }

}

bool CPlayer::IsJumping() {
    return SDL_GetTicks() - m_tickStartJump < m_duraJumping;
}

bool CPlayer::ConsumeNRGY(int nrgyAmount)
{
    if (m_nrgyCurrent < nrgyAmount)
        return false;

    m_nrgyCurrent -= nrgyAmount;

    return true;
}

void CPlayer::AddNRGY(double nrgyAmount)
{
    m_nrgyCurrent = min(m_nrgyCurrent + nrgyAmount, m_nrgyMax);
}