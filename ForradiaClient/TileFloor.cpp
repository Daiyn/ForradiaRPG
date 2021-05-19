#include "TileFloor.h"
#include <memory>
#include "Point.h"

using std::unique_ptr;
using std::move;
using std::make_unique;

TileFloor::TileFloor(int _mapx, int _mapy)
{

    m_coordMapX = _mapx;
    m_coordMapY = _mapy;

    for (int i = 0; i < MAX_OBJECTS_ON_FLOOR; i++)
    {
        m_containedObjects[i] = NULL;
    }

    m_idxGroundType = -1;

}

TileFloor::TileFloor(int _mapx, int _mapy, int _groundType)
{

    m_coordMapX = _mapx;
    m_coordMapY = _mapy;
    m_idxGroundType = _groundType;

    for (int i = 0; i < MAX_OBJECTS_ON_FLOOR; i++)
    {
        m_containedObjects[i] = NULL;
    }

}

void TileFloor::ReplaceObject(int objectTypeToReplace, int objectToReplaceQuantity, int objectTypeToReplaceWith, int objectToReplaceWithQuantity)
{
    for (int i = 0; i < TileFloor::MAX_OBJECTS_ON_FLOOR; i++)
    {
        if (m_containedObjects[i] != NULL)
        {
            if (m_containedObjects[i]->m_idxObjectType == objectTypeToReplace)
            {

                if (m_containedObjects[i]->m_propCurrentQuantity == objectToReplaceQuantity)
                {
                    int mapx = m_containedObjects[i]->m_coordMapX;
                    int mapy = m_containedObjects[i]->m_coordMapY;
                    m_containedObjects[i].reset();
                    m_containedObjects[i] = make_unique<Object>(Object(objectTypeToReplaceWith, { mapx, mapy }, objectToReplaceWithQuantity));
                    break;
                }
            }
        }
    }
}

bool TileFloor::HoldsObjectOfType(int _objectType)
{

    for (int jj = 0; jj < TileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_containedObjects[jj] != NULL)
        {
            if (m_containedObjects[jj]->m_idxObjectType == _objectType)
                return true;
        }
    }

    return false;

}

bool TileFloor::HoldsObjectOfTypeAndQuantity(int _objectType, int _quantity)
{

    for (int jj = 0; jj < TileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_containedObjects[jj] != NULL)
        {
            if (m_containedObjects[jj]->m_idxObjectType == _objectType)
            {
                if (m_containedObjects[jj]->m_propCurrentQuantity == _quantity)
                    return true;
            }
        }
    }

    return false;

}

int TileFloor::GetObjectIndexForObjectType(int _objectType)
{
    for (int jj = 0; jj < TileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        if (m_containedObjects[jj] != NULL)
            if (m_containedObjects[jj]->m_idxObjectType == _objectType)
                return jj;

    return INVALID_INDEX;
}

bool TileFloor::HoldsObjects()
{
    for (int jj = 0; jj < TileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        if (m_containedObjects[jj] != NULL)
            return true;

    return false;
}

int TileFloor::GetFreeObjectIndex()
{
    for (int jj = 0; jj < TileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
        if (m_containedObjects[jj] == NULL)
            return jj;

    return INVALID_INDEX;
}

void TileFloor::DeleteObjectAtIndex(int i)
{
    if (m_containedObjects[i] != nullptr)
        m_containedObjects[i].reset();
}

void TileFloor::AddObject(int _objectType)
{
    for (int jj = 0; jj < TileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_containedObjects[jj] == NULL)
        {
            m_containedObjects[jj] = make_unique<Object>(Object(_objectType, { m_coordMapX, m_coordMapY }));
            break;
        }
    }
}

void TileFloor::ClearObjects()
{
    for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
    {
        if (m_containedObjects[jjj] != NULL)
        {
            m_containedObjects[jjj].reset();
        }
    }
}

void TileFloor::DeleteObjectWithId(int id)
{

    for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
    {

        unique_ptr<Object>& jt = m_containedObjects[jjj];
        if (jt == nullptr)
            continue;

        if ((*jt).m_uniqueID == id)
        {

            m_containedObjects[jjj].reset();

            break;
        }
    }

}

bool TileFloor::RemoveIfHoldsObjectOfTypeAndQuantity(int _objectType, int _quantity)
{
    for (int jj = 0; jj < TileFloor::MAX_OBJECTS_ON_FLOOR; jj++)
    {
        if (m_containedObjects[jj] != NULL)
        {
            if (m_containedObjects[jj]->m_idxObjectType == _objectType)
            {
                if (m_containedObjects[jj]->m_propCurrentQuantity == _quantity)
                {
                    m_containedObjects[jj].reset();

                    return true;
                }
            }
        }
    }

    return false;
}

int TileFloor::GetObjectIndexWithId(int id)
{

    for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
    {

        unique_ptr<Object>& jt = m_containedObjects[jjj];
        if (jt == nullptr)
            continue;

        if (jt->m_uniqueID == id)
            return jjj;

    }

    return -1;

}