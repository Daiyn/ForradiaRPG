#include "CTileFloor.h"
#include <memory>

using std::unique_ptr;
using std::move;
using std::make_unique;

CTileFloor::CTileFloor(int _mapx, int _mapy)
{

    m_mapx = _mapx;
    m_mapy = _mapy;

    for (int i = 0; i < MAX_OBJECTS_ON_FLOOR; i++)
    {
        m_floorObjectsArr[i] = NULL;
    }

    m_groundType = -1;

}

CTileFloor::CTileFloor(int _mapx, int _mapy, int _groundType)
{

    m_mapx = _mapx;
    m_mapy = _mapy;
    m_groundType = _groundType;

    for (int i = 0; i < MAX_FOES_ON_FLOOR; i++)
    {
        m_floorFoesArr[i] = NULL;
    }

    for (int i = 0; i < MAX_OBJECTS_ON_FLOOR; i++)
    {
        m_floorObjectsArr[i] = NULL;
    }

}

void CTileFloor::ReplaceObject(int objectTypeToReplace, int objectToReplaceQuantity, int objectTypeToReplaceWith, int objectToReplaceWithQuantity)
{
    for (int i = 0; i < CTileFloor::MAX_OBJECTS_ON_FLOOR; i++)
    {
        if (m_floorObjectsArr[i] != NULL)
        {
            if (m_floorObjectsArr[i]->m_idxObjectType == objectTypeToReplace)
            {

                if (m_floorObjectsArr[i]->m_qtyCurrent == objectToReplaceQuantity)
                {
                    int mapx = m_floorObjectsArr[i]->m_2DMapX;
                    int mapy = m_floorObjectsArr[i]->m_2DMapY;
                    m_floorObjectsArr[i].reset();
                    m_floorObjectsArr[i] = make_unique<CObject>(CObject(objectTypeToReplaceWith, { mapx, mapy }, objectToReplaceWithQuantity));
                    break;
                }
            }
        }
    }
}

bool CTileFloor::HoldsObjectOfType(int _objectType)
{

    for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_floorObjectsArr[jj] != NULL)
        {
            if (m_floorObjectsArr[jj]->m_idxObjectType == _objectType)
                return true;
        }
    }

    return false;

}

bool CTileFloor::HoldsObjectOfTypeAndQuantity(int _objectType, int _quantity)
{

    for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_floorObjectsArr[jj] != NULL)
        {
            if (m_floorObjectsArr[jj]->m_idxObjectType == _objectType)
            {
                if (m_floorObjectsArr[jj]->m_qtyCurrent == _quantity)
                    return true;
            }
        }
    }

    return false;

}

int CTileFloor::GetObjectIndexForObjectType(int _objectType)
{
    for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        if (m_floorObjectsArr[jj] != NULL)
            if (m_floorObjectsArr[jj]->m_idxObjectType == _objectType)
                return jj;

    return INVALID_INDEX;
}

bool CTileFloor::HoldsObjects()
{
    for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        if (m_floorObjectsArr[jj] != NULL)
            return true;

    return false;
}

int CTileFloor::GetFreeObjectIndex()
{
    for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        if (m_floorObjectsArr[jj] == NULL)
            return jj;

    return INVALID_INDEX;
}

void CTileFloor::DeleteObjectAtIndex(int i)
{
    if (m_floorObjectsArr[i] != nullptr)
        m_floorObjectsArr[i].reset();
}

void CTileFloor::AddObject(int _objectType)
{
    for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_floorObjectsArr[jj] == NULL)
        {
            m_floorObjectsArr[jj] = make_unique<CObject>(CObject(_objectType, { m_mapx, m_mapy }));
            break;
        }
    }
}

void CTileFloor::ClearObjects()
{
    for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
    {
        if (m_floorObjectsArr[jjj] != NULL)
        {
            m_floorObjectsArr[jjj].reset();
        }
    }
}

bool CTileFloor::HasNpcs()
{
    return m_npcs.size() > 0;
}

void CTileFloor::DeleteObjectWithId(int id)
{

    for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
    {

        unique_ptr<CObject>& jt = m_floorObjectsArr[jjj];
        if (jt == nullptr)
            continue;

        if ((*jt).m_uniqueID == id)
        {

            m_floorObjectsArr[jjj].reset();

            break;
        }
    }

}

bool CTileFloor::RemoveIfHoldsObjectOfTypeAndQuantity(int _objectType, int _quantity)
{
    for (int jj = 0; jj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_floorObjectsArr[jj] != NULL)
        {
            if (m_floorObjectsArr[jj]->m_idxObjectType == _objectType)
            {
                if (m_floorObjectsArr[jj]->m_qtyCurrent == _quantity)
                {
                    m_floorObjectsArr[jj].reset();

                    return true;
                }
            }
        }
    }

    return false;
}

int CTileFloor::GetObjectIndexWithId(int id)
{

    for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
    {

        unique_ptr<CObject>& jt = m_floorObjectsArr[jjj];
        if (jt == nullptr)
            continue;

        if (jt->m_uniqueID == id)
            return jjj;

    }

    return -1;

}