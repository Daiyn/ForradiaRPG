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
        m_2DElevation.push_back(vector<int>());
        m_2DNPCOwnedLand.push_back(vector<bool>());
        m_2DMinedTiles.push_back(vector<vector<int>>());
        m_2DTiles.push_back(vector<unique_ptr<CTile>>());
    }

    FOR(y, 0, mapSize)
    {
        FOR(x, 0, mapSize)
        {

            m_2DTiles[x].push_back(make_unique<CTile > (CTile()));
            m_2DTiles[x][y]->m_floorsArray[SURFACE_FLOOR] = make_unique<CTileFloor>(CTileFloor(x, y));
            m_2DElevation[x].push_back(0);
            m_2DNPCOwnedLand[x].push_back(false);
            m_2DMinedTiles[x].push_back(vector<int>());

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

    if (m_2DMinedTiles[mapx][mapy].size() == 0)
        return false;

    if (std::find(m_2DMinedTiles[mapx][mapy].begin(), m_2DMinedTiles[mapx][mapy].end(), elev) != m_2DMinedTiles[mapx][mapy].end())
        return true;

    false;

}

bool CMap::TileHoldsObjectOfType(int _objectType, int mapx, int mapy, int floor)
{

    if (m_2DTiles[mapx][mapy]->m_floorsArray[floor] != NULL)
        FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
            if (m_2DTiles[mapx][mapy]->m_floorsArray[floor]->m_floorObjectsArr[jj] != NULL)
                    if (m_2DTiles[mapx][mapy]->m_floorsArray[floor]->m_floorObjectsArr[jj]->m_idxObjectType == _objectType)
                        return true;

    return false;

}

bool CMap::TileHoldsObjectOfTypeAndQuantity(int _objectType, int quantity, int mapx, int mapy, int floor)
{

    if (m_2DTiles[mapx][mapy]->m_floorsArray[floor] != NULL)
        FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
            if (m_2DTiles[mapx][mapy]->m_floorsArray[floor]->m_floorObjectsArr[jj] != NULL)
                if (m_2DTiles[mapx][mapy]->m_floorsArray[floor]->m_floorObjectsArr[jj]->m_idxObjectType == _objectType)
                    if (m_2DTiles[mapx][mapy]->m_floorsArray[floor]->m_floorObjectsArr[jj]->m_qtyCurrent == quantity)
                        return true;

    return false;

}

bool CMap::TileIsAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3)
{

    if (m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_groundType == val1
        || m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_groundType == val2
        || m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_groundType == val3)
        return true;

    return false;

}

bool CMap::TileIsNotAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3)
{

    if (m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_groundType == val1
        || m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_groundType == val2
        || m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_groundType == 3)
        return false;

    return true;

}

void CMap::UpdateNPCs()
{

    for (auto it : m_listAllNPCs)
        it.get().Update(this);

}

bool CMap::SeenFloorHasFoes(int mapx, int mapy)
{

    if (!Utilities::InMapIncludingEdges(mapx, mapy))
        return false;

    int seenFlorIndex = m_2DTiles[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFlorIndex == -1)
        return false;

    FOR(i, 0, CTileFloor::MAX_FOES_ON_FLOOR)
        if (m_2DTiles[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_floorFoesArr[i] != nullptr)
            return true;

    return false;

}

bool CMap::SeenFloorHasBlockingFoes(int mapx, int mapy)
{

    if (!Utilities::InMapIncludingEdges(mapx, mapy))
        return false;

    int seenFlorIndex = m_2DTiles[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFlorIndex == -1)
        return false;

    FOR(i, 0, CTileFloor::MAX_FOES_ON_FLOOR)
        if (m_2DTiles[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_floorFoesArr[i] != nullptr)
            if (m_2DTiles[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_floorFoesArr[i]->m_idxFoeType != ID_BUTTERFLY)
                return true;

    return false;

}

int CMap::GetTopFoeInMapAllFoeArrayIndex(int mapx, int mapy)
{

    int seenFlorIndex = m_2DTiles[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFlorIndex == -1)
        return -1;

    for (int i = CTileFloor::MAX_FOES_ON_FLOOR - 1; i >= 0; i--)
        if (m_2DTiles[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_floorFoesArr[i] != nullptr)
        {
            for (int j = 0; j < m_allFoesArray.size(); j++)
            {
                if (m_2DTiles[mapx][mapy]->m_floorsArray[seenFlorIndex]->m_floorFoesArr[i]->m_uniqueId == m_allFoesArray[j].get().m_uniqueId)
                    return j;
            }
        }

    return -1;

}

unique_ptr<CObject> CMap::GetTopObject(int mapx, int mapy)
{

    int seenFloorIndex = m_2DTiles[mapx][mapy]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return nullptr;

    for (int i = CTileFloor::MAX_OBJECTS_ON_FLOOR - 1; i >= 0; i--)
        if (m_2DTiles[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_floorObjectsArr[i] != NULL)
            return move(m_2DTiles[mapx][mapy]->m_floorsArray[seenFloorIndex]->m_floorObjectsArr[i]);

    return nullptr;

}

void CMap::ClearReferencesToFoe(CFoe& foe, int allFoesListIndex, CTileFloor& floor)
{
    
    for (auto it = m_allFoesArray.begin(); it != m_allFoesArray.end(); it++)
    {
        if (it->get().m_uniqueId == foe.m_uniqueId)
        {
            m_allFoesArray.erase(it);
            break;
        }
    }

    FOR(ii, 0, CTileFloor::MAX_FOES_ON_FLOOR)
    {
        if (foe.m_uniqueId == floor.m_floorFoesArr[ii].get()->m_uniqueId)
        {
            floor.m_floorFoesArr[ii].reset();
            break;
        }
    }

}

void CMap::AddObject(int objectType, int mapx, int mapy, int floor)
{

    FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
    {
        if (m_2DTiles[mapx][mapy]->m_floorsArray[floor]->m_floorObjectsArr[jj] == nullptr)
        {
            m_2DTiles[mapx][mapy]->m_floorsArray[floor]->m_floorObjectsArr[jj] = make_unique<CObject>(CObject(objectType, { mapx, mapy }));
            break;
        }
    }

}

void CMap::AddObject(unique_ptr<CObject> _object, CPoint p, int floor)
{
    FOR(jj, 0, CTileFloor::MAX_OBJECTS_ON_FLOOR)
    {
        if (m_2DTiles[p.m_x][p.m_y]->m_floorsArray[floor]->m_floorObjectsArr[jj] == nullptr)
        {
            m_2DTiles[p.m_x][p.m_y]->m_floorsArray[floor]->m_floorObjectsArr[jj] = move(_object);
            break;
        }
    }
}

void CMap::AddChangingObject(int _objectType, CPoint p, int floor)
{
    auto o = make_unique<CObject>(CObject(_objectType, p));
    m_listChangingObject.push_back(*o);
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
        if (m_2DTiles[foe->m_posSpawn.m_x][foe->m_posSpawn.m_y]->m_floorsArray[floor]->m_floorFoesArr[j] == nullptr)
        {

            m_allFoesArray.push_back(*foe);

            m_2DTiles[foe->m_posSpawn.m_x][foe->m_posSpawn.m_y]->m_floorsArray[floor]->m_floorFoesArr[j] = move(foe);
            break;
        }
    }

}

void CMap::TranslateFoe(int uniqueID, CPoint pFrom, CPoint pTo, int floor)
{

    FOR(k, 0, CTileFloor::MAX_FOES_ON_FLOOR)
    {
        if (m_2DTiles[pTo.m_x][pTo.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorFoesArr[k] == nullptr)
        {

            FOR(ii, 0, CTileFloor::MAX_FOES_ON_FLOOR)
            {

                if (m_2DTiles[pFrom.m_x][pFrom.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorFoesArr[ii] == nullptr)
                    continue;

                CFoe& jt = *m_2DTiles[pFrom.m_x][pFrom.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorFoesArr[ii];

                

                if (jt.m_uniqueId == uniqueID)
                {

                    m_2DTiles[pTo.m_x][pTo.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorFoesArr[k] = move(m_2DTiles[pFrom.m_x][pFrom.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorFoesArr[ii]);
                    m_2DTiles[pTo.m_x][pTo.m_y]->m_floorsArray[SURFACE_FLOOR]->m_floorFoesArr[k].get()->m_posCurrent = pTo;

                    return;

                }
            }
        }
    }

}