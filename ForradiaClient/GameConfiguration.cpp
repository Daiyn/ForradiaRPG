#include "GameConfiguration.h"
#include "DataLoading.h"
#include "Global_Player.h"
#include <memory>
#include "Object.h"

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
    int indexPlough = DataLoading::GetDescriptionIndexByName("ObjectPlough");

    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(0, make_unique<Object>(Object(indexApple, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(2, make_unique<Object>(Object(indexApple, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(5, make_unique<Object>(Object(indexStone, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }, 5))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(15, make_unique<Object>(Object(indexWoodLog, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(17, make_unique<Object>(Object(indexShovel, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(18, make_unique<Object>(Object(indexMatches, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(19, make_unique<Object>(Object(indexSaw, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(20, make_unique<Object>(Object(indexSmallAnvil, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(21, make_unique<Object>(Object(indexBrick, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(22, make_unique<Object>(Object(indexBrick, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(23, make_unique<Object>(Object(indexBrick, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(24, make_unique<Object>(Object(indexCoal, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(25, make_unique<Object>(Object(indexIronOre, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(26, make_unique<Object>(Object(indexIronNail, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }, 25))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(27, make_unique<Object>(Object(indexStoneHammer, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));
    Global::statePlayer->m_inventory.m_containedItems.insert(pair<int, unique_ptr<Object>>(28, make_unique<Object>(Object(indexPlough, { OBJECT_IN_AIR_OR_INVENTORY, OBJECT_IN_AIR_OR_INVENTORY }))));

}
