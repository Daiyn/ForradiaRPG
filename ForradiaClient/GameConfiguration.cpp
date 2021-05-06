#include "GameConfiguration.h"
#include "DataLoading.h"
#include "Global_Player.h"
#include <memory>
#include "CObject.h"

using std::make_unique;
using std::unique_ptr;
using std::pair;

void GameConfiguration::AddPlayerStartingItems()
{

    int indexApple = DataLoading::GetDescriptionIndexByName("ObjectApple");
    int indexStone = DataLoading::GetDescriptionIndexByName("ObjectStone");
    int indexWoodLog = DataLoading::GetDescriptionIndexByName("ObjectWoodLog");
    int indexShovel = DataLoading::GetDescriptionIndexByName("ObjectShovel");
    int indexMatches = DataLoading::GetDescriptionIndexByName("ObjectMatches");
    int indexSaw = DataLoading::GetDescriptionIndexByName("ObjectSaw");
    int indexSmallAnvil = DataLoading::GetDescriptionIndexByName("ObjectSmallAnvil");
    int indexBrick = DataLoading::GetDescriptionIndexByName("ObjectBrick");
    int indexCoal = DataLoading::GetDescriptionIndexByName("ObjectCoal");
    int indexIronOre = DataLoading::GetDescriptionIndexByName("ObjectIronOre");
    int indexIronNail = DataLoading::GetDescriptionIndexByName("ObjectIronNail");
    int indexStoneHammer = DataLoading::GetDescriptionIndexByName("ObjectStoneHammer");

    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(0, make_unique<CObject>(CObject(indexApple, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(2, make_unique<CObject>(CObject(indexApple, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(5, make_unique<CObject>(CObject(indexStone, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }, 5))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(15, make_unique<CObject>(CObject(indexWoodLog, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(17, make_unique<CObject>(CObject(indexShovel, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(18, make_unique<CObject>(CObject(indexMatches, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(19, make_unique<CObject>(CObject(indexSaw, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(20, make_unique<CObject>(CObject(indexSmallAnvil, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(21, make_unique<CObject>(CObject(indexBrick, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(22, make_unique<CObject>(CObject(indexBrick, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(23, make_unique<CObject>(CObject(indexBrick, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(24, make_unique<CObject>(CObject(indexCoal, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(25, make_unique<CObject>(CObject(indexIronOre, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(26, make_unique<CObject>(CObject(indexIronNail, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }, 25))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<CObject>>(27, make_unique<CObject>(CObject(indexStoneHammer, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));

}
