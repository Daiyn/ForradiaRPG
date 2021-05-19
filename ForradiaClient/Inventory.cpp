#include "Inventory.h"
#include "Global_Player.h"
#include "DataLoading.h"
#include "Player.h"

using std::pair;
using std::make_unique;

bool Inventory::UseItemInInventory(int objectType, int _quantity)
{

    int index = INVALID_INDEX;

    for (auto it = m_containedItems.begin(); it != m_containedItems.end(); it++)
    {
        if (it->second->m_idxObjectType == objectType)
        {
            index = it->first;
            break;
        }
    }

    if (index != INVALID_INDEX)
    {
        if (m_containedItems[index]->m_propCurrentQuantity > _quantity)
        {
            m_containedItems[index]->m_propCurrentQuantity -= _quantity;
            return true;
        }
        else if (m_containedItems[index]->m_propCurrentQuantity == _quantity)
        {
            m_containedItems.erase(index);
            return true;
        }
    }

    return false;

}

bool Inventory::HasItemInInventory(int objectType)
{
    for (auto it = m_containedItems.begin(); it != m_containedItems.end(); it++)
        if (it->second->m_idxObjectType == objectType)
            return true;

    return false;
}

bool Inventory::SlotIsOccupied(int index)
{
    return m_containedItems.count(index) > 0;
}

void Inventory::AddItemToInventory(int objectType)
{
    for (int i = 0; i < m_containedItems.size() + 1; i++)
    {
        if (m_containedItems.count(i) == 0)
        {
            m_containedItems.insert(pair<int, unique_ptr<Object>>(i, make_unique<Object>(Object(objectType, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
            break;
        }
    }
}