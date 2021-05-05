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

    if (mapx < 0 || mapy < 0 || mapx >= Global::tilesMapSize || mapy >= Global::tilesMapSize)
        return false;

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();
    
    if (seenFloorIndex == -1)
        return false;

    int dist = std::max(abs(mapx - Global::statePlayer->m_coordPosition.m_x), abs(mapy - Global::statePlayer->m_coordPosition.m_y));

    if (dist <= 1)
    {

        bool tileHasObjects = Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->HoldsObjects();

        if (!tileHasObjects)
            return false;

        auto topObject = Global::contentCurrentMap->GetTopObject(mapx, mapy);

        if (topObject != nullptr)
        {
            int objectType = topObject->m_idxObjectType;

            if (DataLoading::libDescriptions[objectType]->m_propAttributes["Movable"] == "True")
            {

                nodupMovedObject = move(topObject);
                nodupMovedObject->m_coordMapX = OBJECT_IN_AIR_OR_INVENTORY;
                nodupMovedObject->m_coordMapY = OBJECT_IN_AIR_OR_INVENTORY;

            }

            return true;

        }

    }

    return false;
}

void ItemMoving::DropnodupMovedObjectIfExists(int mapx, int mapy)
{

    if (mapx < 0 || mapy < 0 || mapx >= Global::tilesMapSize || mapy >= Global::tilesMapSize)
        return;

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    if (nodupMovedObject != NULL)
    {
        nodupMovedObject->m_coordMapX = mapx;
        nodupMovedObject->m_coordMapY = mapy;

        for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        {
            if (Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[jj] != NULL)
            {
                if (Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[jj]->m_idxObjectType == nodupMovedObject->m_idxObjectType)
                {
                    Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[jj]->m_propCurrentQuantity += nodupMovedObject->m_propCurrentQuantity;
                    break;
                }
                
            }
            else
            {
                Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[jj] = move(nodupMovedObject);
                break;
            }
        }

        nodupMovedObject = NULL;
    }

}

void ItemMoving::Render()
{

    if (nodupMovedObject == NULL)
        return;

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    CRectangle rectnodupMovedObject = {mx - Global::GetTileSize(), my - Global::GetTileSize(), 2*Global::GetTileSize(), 2*Global::GetTileSize()};

    Drawing::Image(nodupMovedObject->m_idxObjectType, rectnodupMovedObject);


}