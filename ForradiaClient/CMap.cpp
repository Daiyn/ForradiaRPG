#include "CMap.h"
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
#include "CTile.h"

#define FOR(x,y,z) for (int x = y; x < z; x++)

using std::move;
using std::make_unique;

CMap::CMap(int mapSize)
{

    FOR(i, 0, mapSize)
    {
        m_tilesGrid.push_back(vector<unique_ptr<CTile>>());
    }

    FOR(y, 0, mapSize)
    {
        FOR(x, 0, mapSize)
        {

            m_tilesGrid[x].push_back(make_unique<CTile > (CTile()));
            m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR] = make_unique<CTileFloor>(CTileFloor(x, y));

        }
    }

    m_imgFullMapRender = SDL_CreateRGBSurface(0, Global::mapPreviewSize, Global::mapPreviewSize, 32,
                                                             0xff000000,
                                                             0x00ff0000,
                                                             0x0000ff00,
                                                             0x000000ff);

    MapGeneration::GenerateMap(*this);

}

void CMap::GenerateMapPreview()
{

}

bool CMap::TileIsMinedAtElev(int elev, int mapx, int mapy)
{

    if (m_tilesGrid[mapx][mapy]->m_checkMinedTiles.size() == 0)
        return false;

    if (std::find(m_tilesGrid[mapx][mapy]->m_checkMinedTiles.begin(), m_tilesGrid[mapx][mapy]->m_checkMinedTiles.end(), elev) != m_tilesGrid[mapx][mapy]->m_checkMinedTiles.end())
        return true;

    false;

}

bool CMap::TileHoldsObjectOfType(int _objectType, int mapx, int mapy, int floor)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor] != NULL)
        FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
            if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] != NULL)
                    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj]->m_idxObjectType == _objectType)
                        return true;

    return false;

}

bool CMap::TileHoldsObjectOfTypeAndQuantity(int _objectType, int quantity, int mapx, int mapy, int floor)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor] != NULL)
        FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
            if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] != NULL)
                if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj]->m_idxObjectType == _objectType)
                    if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj]->m_propCurrentQuantity == quantity)
                        return true;

    return false;

}

bool CMap::TileIsAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val1
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val2
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val3)
        return true;

    return false;

}

bool CMap::TileIsNotAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3)
{

    if (m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val1
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == val2
        || m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == 3)
        return false;

    return true;

}

void CMap::UpdateNPCs()
{

    for (auto it : m_mirrorAllNPCs)
        it.get().Update(this);

}

bool CMap::SeenFloorHasFoes(int mapx, int mapy)
{

    if (!Utilities::InMapIncludingEdges(mapx, mapy))
        return false;

    int seenFlorIndex = m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFlorIndex == -1)
        return false;

    FOR(i, 0, CTileFloor::MAX_FOES_ON_FLOOR)
        if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_containedFoes[i] != nullptr)
            return true;

    return false;

}

bool CMap::SeenFloorHasBlockingFoes(int mapx, int mapy)
{

    if (!Utilities::InMapIncludingEdges(mapx, mapy))
        return false;

    int seenFlorIndex = m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFlorIndex == -1)
        return false;

    FOR(i, 0, CTileFloor::MAX_FOES_ON_FLOOR)
        if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_containedFoes[i] != nullptr)
            if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_containedFoes[i]->m_idxFoeType != ID_BUTTERFLY)
                return true;

    return false;

}

int CMap::GetTopFoeInMapAllFoeArrayIndex(int mapx, int mapy)
{

    int seenFlorIndex = m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFlorIndex == -1)
        return -1;

    for (int i = CTileFloor::MAX_FOES_ON_FLOOR - 1; i >= 0; i--)
        if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_containedFoes[i] != nullptr)
        {
            for (int j = 0; j < m_mirrorAllFoes.size(); j++)
            {
                if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_containedFoes[i]->m_uniqueID == m_mirrorAllFoes[j].get().m_uniqueID)
                    return j;
            }
        }

    return -1;

}

unique_ptr<CObject> CMap::GetTopObject(int mapx, int mapy)
{

    int seenFloorIndex = m_tilesGrid[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return nullptr;

    for (int i = CTileFloor::MAX_OBJECTS_ON_FLOOR - 1; i >= 0; i--)
        if (m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[i] != NULL)
            return move(m_tilesGrid[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_containedObjects[i]);

    return nullptr;

}

void CMap::ClearReferencesToFoe(CFoe& foe, int allFoesListIndex, CTileFloor& floor)
{
    
    for (auto it = m_mirrorAllFoes.begin(); it != m_mirrorAllFoes.end(); it++)
    {
        if (it->get().m_uniqueID == foe.m_uniqueID)
        {
            m_mirrorAllFoes.erase(it);
            break;
        }
    }

    FOR(ii, 0, CTileFloor::MAX_FOES_ON_FLOOR)
    {
        if (foe.m_uniqueID == floor.m_containedFoes[ii].get()->m_uniqueID)
        {
            floor.m_containedFoes[ii].reset();
            break;
        }
    }

}

void CMap::AddObject(int objectType, int mapx, int mapy, int floor)
{

    FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
    {
        if (m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] == nullptr)
        {
            m_tilesGrid[mapx][mapy]->m_floorsArray[floor]->m_containedObjects[jj] = make_unique<CObject>(CObject(objectType, { mapx, mapy }));
            break;
        }
    }

}

void CMap::AddObject(unique_ptr<CObject> _object, CPoint p, int floor)
{
    FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
    {
        if (m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[floor]->m_containedObjects[jj] == nullptr)
        {
            m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[floor]->m_containedObjects[jj] = move(_object);
            break;
        }
    }
}

void CMap::AddChangingObject(int _objectType, CPoint p, int floor)
{
    auto o = make_unique<CObject>(CObject(_objectType, p));
    m_objectsWithUpdateNeed.push_back(*o);
    AddObject(move(o), p, SURFACE_FLOOR);
}

void CMap::AddObjectIfDoesntAlreadyExist(int objectType, int mapx, int mapy, int floor)
{

    if (!TileHoldsObjectOfType(objectType, mapx, mapy, floor))
        AddObject(objectType, mapx, mapy, floor);

}

void CMap::AddFoe(unique_ptr<CFoe> foe, int floor)
{
    
    FOR(j, 0, CTileFloor::MAX_FOES_ON_FLOOR)
    {
        if (m_tilesGrid[foe->m_coordSpawn.m_x][foe->m_coordSpawn.m_y]->m_floorsArray[floor]->m_containedFoes[j] == nullptr)
        {

            m_mirrorAllFoes.push_back(*foe);

            m_tilesGrid[foe->m_coordSpawn.m_x][foe->m_coordSpawn.m_y]->m_floorsArray[floor]->m_containedFoes[j] = move(foe);
            break;
        }
    }

}

void CMap::TranslateFoe(int uniqueID, CPoint pFrom, CPoint pTo, int floor)
{

    FOR(k, 0, CTileFloor::MAX_FOES_ON_FLOOR)
    {
        if (m_tilesGrid[pTo.m_x][pTo.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedFoes[k] == nullptr)
        {

            FOR(ii, 0, CTileFloor::MAX_FOES_ON_FLOOR)
            {

                if (m_tilesGrid[pFrom.m_x][pFrom.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedFoes[ii] == nullptr)
                    continue;

                CFoe& jt = *m_tilesGrid[pFrom.m_x][pFrom.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedFoes[ii];

                

                if (jt.m_uniqueID == uniqueID)
                {

                    m_tilesGrid[pTo.m_x][pTo.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedFoes[k] = move(m_tilesGrid[pFrom.m_x][pFrom.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedFoes[ii]);
                    m_tilesGrid[pTo.m_x][pTo.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedFoes[k].get()->m_coordPosition = pTo;

                    return;

                }
            }
        }
    }
}