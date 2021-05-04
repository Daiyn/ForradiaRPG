#include "ItemMoving.h"
#include "CPlayer.h"
#include "ImageLoading.h"
#include "DataLoading.h"
#include "Global_Player.h"
#include "Global_CurrentMap.h"
#include "Global_Mouse.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Drawing.h"
#include "CMap.h"
#include <memory>
#include "Global_MapSize.h"

using std::move;

void RenderItemMoving()
{
    ItemMoving::Render();
}

bool ItemMoving::TryStartDragingObjectFromGround(int mapx, int mapy)
{

    if (mapx < 0 || mapy < 0 || mapx >= Global::mapSize || mapy >= Global::mapSize)
        return false;

    int seenFloorIndex = Global::currentMap->m_2DTiles[mapx][mapy]->GetIndexForSeenFloor();
    
    if (seenFloorIndex == -1)
        return false;

    int dist = std::max(abs(mapx - Global::player->m_posCurrent.m_x), abs(mapy - Global::player->m_posCurrent.m_y));

    if (dist <= 1)
    {

        bool tileHasObjects = Global::currentMap->m_2DTiles[mapx][mapy]->m_floorsArray[seenFloorIndex]->HoldsObjects();

        if (!tileHasObjects)
            return false;

        auto topObject = Global::currentMap->GetTopObject(mapx, mapy);

        if (topObject != nullptr)
        {
            int objectType = topObject->m_idxObjectType;

            if (DataLoading::descriptions[objectType]->m_propAttributes["Movable"] == "True")
            {

                objectInAir = move(topObject);
                objectInAir->m_2DMapX = OBJECT_IN_AIR_OR_INVENTORY;
                objectInAir->m_2DMapY = OBJECT_IN_AIR_OR_INVENTORY;

            }

            return true;

        }

    }

    return false;
}

void ItemMoving::DropObjectInAirIfExists(int mapx, int mapy)
{

    if (mapx < 0 || mapy < 0 || mapx >= Global::mapSize || mapy >= Global::mapSize)
        return;

    int seenFloorIndex = Global::currentMap->m_2DTiles[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    if (objectInAir != NULL)
    {
        objectInAir->m_2DMapX = mapx;
        objectInAir->m_2DMapY = mapy;

        for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        {
            if (Global::currentMap->m_2DTiles[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_floorObjectsArr[jj] != NULL)
            {
                if (Global::currentMap->m_2DTiles[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_floorObjectsArr[jj]->m_idxObjectType == objectInAir->m_idxObjectType)
                {
                    Global::currentMap->m_2DTiles[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_floorObjectsArr[jj]->m_qtyCurrent += objectInAir->m_qtyCurrent;
                    break;
                }
                
            }
            else
            {
                Global::currentMap->m_2DTiles[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_floorObjectsArr[jj] = move(objectInAir);
                break;
            }
        }

        objectInAir = NULL;
    }

}

void ItemMoving::Render()
{

    if (objectInAir == NULL)
        return;

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    CRectangle rectObjectInAir = {mx - Global::GetTileSize(), my - Global::GetTileSize(), 2*Global::GetTileSize(), 2*Global::GetTileSize()};

    Drawing::Image(objectInAir->m_idxObjectType, rectObjectInAir);


}