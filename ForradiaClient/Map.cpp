#include "Map.h"
#include "MapGeneration.h"
#include "ImageLoading.h"
#include "Drawing.h"
#include <algorithm>
#include "Global_MapPreviewSize.h"
#include "Global_SDL.h"
#include "Global_MapSize.h"
#include "Utilities.h"
#include "TileRendering.h"
#include "ObjectsRendering.h"
#include "Global_CurrentMap.h"
#include <memory>
#include "Tile.h"

#define FOR(x,y,z) for (int x = y; x < z; x++)

using std::move;
using std::make_unique;

Map::Map(int mapSize)
{

    FOR(i, 0, mapSize)
    {
        m_tilesGrid.push_back(vector<unique_ptr<Tile>>());
    }

    FOR(y, 0, mapSize)
    {
        FOR(x, 0, mapSize)
        {

            m_tilesGrid[x].push_back(make_unique<Tile > (Tile()));
            m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR] = make_unique<TileFloor>(TileFloor(x, y));

        }
    }

    m_imgFullMapRender = SDL_CreateRGBSurface(0, Global::pxFullMapRenderSize, Global::pxFullMapRenderSize, 32,
                                                             0xff000000,
                                                             0x00ff0000,
                                                             0x0000ff00,
                                                             0x000000ff);

    MapGeneration::GenerateMap(*this);

}

bool Map::TileIsMinedAtElev(int elev, int mapx, int mapy)
{

    if (m_tilesGrid[mapx][mapy]->m_checkMinedTiles.size() == 0)
        return false;

    if (std::find(m_tilesGrid[mapx][mapy]->m_checkMinedTiles.begin(), m_tilesGrid[mapx][mapy]->m_checkMinedTiles.end(), elev) != m_tilesGrid[mapx][mapy]->m_checkMinedTiles.end())
        return true;

    false;

}

bool Map::TileHoldsObjectOfType(int _objectType, int mapx, int mapy, int floor)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor] != NULL)
        FOR(jj, 0, TileFloor::MAX_OBJECTS_ON_FLOOR)
            if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] != NULL)
                    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj]->m_idxObjectType == _objectType)
                        return true;

    return false;

}

bool Map::TileHoldsObjectOfTypeAndQuantity(int _objectType, int quantity, int mapx, int mapy, int floor)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor] != NULL)
        FOR(jj, 0, TileFloor::MAX_OBJECTS_ON_FLOOR)
            if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] != NULL)
                if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj]->m_idxObjectType == _objectType)
                    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj]->m_propCurrentQuantity == quantity)
                        return true;

    return false;

}

bool Map::TileIsAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val1
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val2
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val3)
        return true;

    return false;

}

bool Map::TileIsNotAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val1
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val2
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == 3)
        return false;

    return true;

}

unique_ptr<Object> Map::GetTopObject(int mapx, int mapy)
{

    int seenFloorIndex = m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return nullptr;

    for (int i = TileFloor::MAX_OBJECTS_ON_FLOOR - 1; i >= 0; i--)
        if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[i] != NULL)
            return move(m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[i]);

    return nullptr;

}

int Map::GetTopObjectType(int mapx, int mapy)
{
        int seenFloorIndex = m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();
    
        if (seenFloorIndex == -1)
            return INVALID_INDEX;
    
        for (int i = TileFloor::MAX_OBJECTS_ON_FLOOR - 1; i >= 0; i--)
            if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[i] != NULL)
                return m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[i]->m_idxObjectType;
    
        return INVALID_INDEX;
}


void Map::AddObject(int objectType, int mapx, int mapy, int floor)
{

    FOR(jj, 0, TileFloor::MAX_OBJECTS_ON_FLOOR)
    {
        if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] == nullptr)
        {
            m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] = make_unique<Object>(Object(objectType, { mapx, mapy }));
            break;
        }
    }

}

void Map::AddObject(unique_ptr<Object> _object, Point p, int floor)
{
    FOR(jj, 0, TileFloor::MAX_OBJECTS_ON_FLOOR)
    {
        if (m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[floor]->m_containedObjects[jj] == nullptr)
        {
            m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[floor]->m_containedObjects[jj] = move(_object);
            break;
        }
    }
}

void Map::AddChangingObject(int _objectType, Point p, int floor)
{
    auto o = make_unique<Object>(Object(_objectType, p));
    m_objectsWithUpdateNeed.push_back(*o);
    AddObject(move(o), p, SURFACE_FLOOR);
}

void Map::AddObjectIfDoesntAlreadyExist(int objectType, int mapx, int mapy, int floor)
{

    if (!TileHoldsObjectOfType(objectType, mapx, mapy, floor))
        AddObject(objectType, mapx, mapy, floor);

}

