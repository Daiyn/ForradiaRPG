#include "CInventory.h"
#include "Global_Player.h"
#include "DataLoading.h"
#include "CPlayer.h"

using std::pair;
using std::make_unique;

bool CInventory::UseItemInInventory(int objectType, int _quantity)
{

    int index = INVALID_INDEX;

    for (auto it = m_belongingCollection.begin(); it != m_belongingCollection.end(); it++)
    {
        if (it->second->m_idxObjectType == objectType)
        {
            index = it->first;
            break;
        }
    }

    if (index != INVALID_INDEX)
    {
        if (m_belongingCollection[index]->m_qtyCurrent > _quantity)
        {
            m_belongingCollection[index]->m_qtyCurrent -= _quantity;
            return true;
        }
        else if (m_belongingCollection[index]->m_qtyCurrent == _quantity)
        {
            m_belongingCollection.erase(index);
            return true;
        }
    }

    return false;

}

bool CInventory::HasItemInInventory(int objectType)
{

    for (auto it = m_belongingCollection.begin(); it != m_belongingCollection.end(); it++)
        if (it->second->m_idxObjectType == objectType)
            return true;

    return false;

}

bool CInventory::SlotIsOccupied(int index)
{
    return m_belongingCollection.count(index) > 0;
}

void CInventory::AddItemToInventory(int objectType)
{


    for (int i = 0; i < m_belongingCollection.size() + 1; i++)
    {
        if (m_belongingCollection.count(i) == 0)
        {
            m_belongingCollection.insert(pair<int, unique_ptr<CObject>>(i, make_unique<CObject>(CObject(objectType, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
            break;
        }

    }

}