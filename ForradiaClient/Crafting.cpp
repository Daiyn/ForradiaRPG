#include "Crafting.h"
#include "PlayerActions.h"
#include "DataLoading.h"
#include "Global_CurrentMap.h"
#include "Map.h"
#include "Global_Player.h"
#include "Player.h"
#include <memory>

using std::make_unique;

void Crafting::ChopDownTree(Point p)
{
	PlayerActions::FocusOnObject(p);
}

void Crafting::CreateWoodplank(Point p)
{

    int objectWoodLog = DataLoading::GetDescriptionIndexByName("ObjectWoodLog");
    int objectWoodPlank = DataLoading::GetDescriptionIndexByName("ObjectWoodPlank");
    int objectSaw = DataLoading::GetDescriptionIndexByName("ObjectSaw");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    if (Global::statePlayer->m_inventory.HasItemInInventory(objectSaw))
        Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex]->ReplaceObject(objectWoodLog, 1, objectWoodPlank, 1);

}

void Crafting::CreateWoodfloor(Point p)
{

    int objectWoodplank = DataLoading::GetDescriptionIndexByName("ObjectWoodPlank");
    int tileWoodfloor = DataLoading::GetDescriptionIndexByName("TileWoodfloor");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (Global::statePlayer->m_inventory.HasItemInInventory(objectWoodplank)
        && floor.m_idxGroundType != ImagesIDs::TileWater)
    {
        if (Global::statePlayer->m_inventory.UseItemInInventory(objectWoodplank, 1))
        {
            floor.m_idxGroundType = tileWoodfloor;
        }
    }

}

void Crafting::CreateUnloadedCampfire(Point p)
{

	int objectStone = DataLoading::GetDescriptionIndexByName("ObjectStone");
	int objectUnloadedCampfire = DataLoading::GetDescriptionIndexByName("ObjectUnloadedCampfire");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    if (Global::statePlayer->ConsumeNRGY(5))
	    Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex]->ReplaceObject(objectStone, 5, objectUnloadedCampfire, 1);

}

void Crafting::LoadCampfire(Point p)
{
    int objectWoodLog = DataLoading::GetDescriptionIndexByName("ObjectWoodLog");
    int objectUnloadedCampfire = DataLoading::GetDescriptionIndexByName("ObjectUnloadedCampfire");
    int objectLoadedCampfire = DataLoading::GetDescriptionIndexByName("ObjectLoadedCampfire");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectUnloadedCampfire))
        if (Global::statePlayer->m_inventory.UseItemInInventory(objectWoodLog, 1))
            if (Global::statePlayer->ConsumeNRGY(6))
                floor.ReplaceObject(objectUnloadedCampfire, 1, objectLoadedCampfire, 1);

}

void Crafting::LightCampfire(Point p)
{
    int objectMatches = DataLoading::GetDescriptionIndexByName("ObjectMatches");
    int objectLoadedCampfire = DataLoading::GetDescriptionIndexByName("ObjectLoadedCampfire");
    int objectBurningCampfire = DataLoading::GetDescriptionIndexByName("ObjectBurningCampfire");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectLoadedCampfire))
        if (Global::statePlayer->m_inventory.HasItemInInventory(objectMatches))
            if (Global::statePlayer->ConsumeNRGY(5))
                floor.ReplaceObject(objectLoadedCampfire, 1, objectBurningCampfire, 1);

}

void Crafting::ChopUpWoodLog(Point p)
{

    int objectWoodLog = DataLoading::GetDescriptionIndexByName("ObjectWoodLog");
    int objectFelledTree = DataLoading::GetDescriptionIndexByName("ObjectFelledTree");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    bool breakLoop = false;

    for (int y = p.m_y - 1; y <= p.m_y + 1 && !breakLoop; y++)
    {
        for (int x = p.m_x - 1; x <= p.m_x + 1 && !breakLoop; x++)
        {

            int seenFloorIndexFreeSpace = Global::contentCurrentMap->m_tilesGrid[x][y]->GetIndexForSeenFloor();

            if (seenFloorIndexFreeSpace == -1)
                continue;

            TileFloor& floorFreeSpace = *Global::contentCurrentMap->m_tilesGrid[x][y]->m_floorsArray[seenFloorIndexFreeSpace];

            if (floorFreeSpace.HoldsObjects())
                continue;

            int freeObjectSpaceIndex = floorFreeSpace.GetFreeObjectIndex();

            if (Global::statePlayer->ConsumeNRGY(5))
            {
                floorFreeSpace.m_containedObjects[freeObjectSpaceIndex] = make_unique<Object>(Object(objectWoodLog, { x, y }));

                int index = floor.GetObjectIndexForObjectType(objectFelledTree);

                if (index != INVALID_INDEX)
                {
                    floor.m_containedObjects[index]->m_propCurrentAmount -= 20;

                    if (floor.m_containedObjects[index]->m_propCurrentAmount <= 0)
                        floor.DeleteObjectAtIndex(index);

                    breakLoop = true;
                    break;
                }
            }
        }
    }

}

void Crafting::DigClay(Point p)
{
    int tileClay = DataLoading::GetDescriptionIndexByName("TileClay");
    int objectShovel = DataLoading::GetDescriptionIndexByName("ObjectShovel");
    int objectClayLump = DataLoading::GetDescriptionIndexByName("ObjectClayLump");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.m_idxGroundType == tileClay)
        if (Global::statePlayer->m_inventory.HasItemInInventory(objectShovel))
            if (Global::statePlayer->ConsumeNRGY(5))
                floor.AddObject(objectClayLump);

}

void Crafting::CreateBrick(Point p)
{
    int objectClayLump = DataLoading::GetDescriptionIndexByName("ObjectClayLump");
    int objectBrick = DataLoading::GetDescriptionIndexByName("ObjectBrick");
    int objectBurningCampfire = DataLoading::GetDescriptionIndexByName("ObjectBurningCampfire");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectBurningCampfire))
        if (Global::statePlayer->ConsumeNRGY(5))
            if (Global::statePlayer->m_inventory.UseItemInInventory(objectClayLump, 1))
                    Global::statePlayer->m_inventory.AddItemToInventory(objectBrick);
}

void Crafting::CreateMeltingFurnace(Point p)
{
    int objectBrick = DataLoading::GetDescriptionIndexByName("ObjectBrick");
    int objectUnloadedMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectUnloadedMeltingFurnace");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfTypeAndQuantity(objectBrick, MELTING_FURNACE_NUM_REQ_BRICKS))
        if (Global::statePlayer->ConsumeNRGY(5))
            floor.ReplaceObject(objectBrick, MELTING_FURNACE_NUM_REQ_BRICKS, objectUnloadedMeltingFurnace, 1);
}

void Crafting::LoadMeltingFurnace(Point p)
{
    int objectCoal = DataLoading::GetDescriptionIndexByName("ObjectCoal");
    int objectUnloadedMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectUnloadedMeltingFurnace");
    int objectLoadedMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectLoadedMeltingFurnace");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectUnloadedMeltingFurnace))
        if (Global::statePlayer->m_inventory.UseItemInInventory(objectCoal, 1))
            floor.ReplaceObject(objectUnloadedMeltingFurnace, 1, objectLoadedMeltingFurnace, 1);

}


void Crafting::LightMeltingFurnace(Point p)
{
    int objectMatches = DataLoading::GetDescriptionIndexByName("ObjectMatches");
    int objectLoadedMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectLoadedMeltingFurnace");
    int objectHotMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectHotMeltingFurnace");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectLoadedMeltingFurnace))
        if (Global::statePlayer->m_inventory.HasItemInInventory(objectMatches))
            if (Global::statePlayer->ConsumeNRGY(5))
                floor.ReplaceObject(objectLoadedMeltingFurnace, 1, objectHotMeltingFurnace, 1);

}

void Crafting::HeatIron(Point p)
{
    int objectIronOre = DataLoading::GetDescriptionIndexByName("ObjectIronOre");
    int objectHotIronLump = DataLoading::GetDescriptionIndexByName("ObjectHotIronLump");
    int objectHotMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectHotMeltingFurnace");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectHotMeltingFurnace))
        if (Global::statePlayer->ConsumeNRGY(5))
            if (Global::statePlayer->m_inventory.UseItemInInventory(objectIronOre, 1))
                Global::statePlayer->m_inventory.AddItemToInventory(objectHotIronLump);
}

void Crafting::CreateIronNail(Point p)
{

    int objectHotIronLump = DataLoading::GetDescriptionIndexByName("ObjectHotIronLump");
    int objectSmallAnvil = DataLoading::GetDescriptionIndexByName("ObjectSmallAnvil");
    int objectIronNail = DataLoading::GetDescriptionIndexByName("ObjectIronNail");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectSmallAnvil))
        if (Global::statePlayer->ConsumeNRGY(5))
            if (Global::statePlayer->m_inventory.UseItemInInventory(objectHotIronLump, 1))
                Global::statePlayer->m_inventory.AddItemToInventory(objectIronNail);

}


void Crafting::DigGround(Point p)
{
    Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_elevationHeight--;
}


void Crafting::CreateWoodWallNS(Point p)
{
    int objectWoodplank = DataLoading::GetDescriptionIndexByName("ObjectWoodPlank");
    int objectIronNail = DataLoading::GetDescriptionIndexByName("ObjectIronNail");
    int objectStoneHammer = DataLoading::GetDescriptionIndexByName("ObjectStoneHammer");
    int objectWoodWallNS = DataLoading::GetDescriptionIndexByName("ObjectWoodWallNS");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectWoodplank))
        if (Global::statePlayer->ConsumeNRGY(5))
            if (Global::statePlayer->m_inventory.HasItemInInventory(objectStoneHammer))
                if (Global::statePlayer->m_inventory.UseItemInInventory(objectIronNail, 1))
                    Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex]->ReplaceObject(objectWoodplank, 1, objectWoodWallNS, 1);
}

void Crafting::CreateWoodWallEW(Point p)
{
    int objectWoodplank = DataLoading::GetDescriptionIndexByName("ObjectWoodPlank");
    int objectIronNail = DataLoading::GetDescriptionIndexByName("ObjectIronNail");
    int objectStoneHammer = DataLoading::GetDescriptionIndexByName("ObjectStoneHammer");
    int objectWoodWallEW = DataLoading::GetDescriptionIndexByName("ObjectWoodWallEW");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectWoodplank))
        if (Global::statePlayer->ConsumeNRGY(5))
            if (Global::statePlayer->m_inventory.HasItemInInventory(objectStoneHammer))
                if (Global::statePlayer->m_inventory.UseItemInInventory(objectIronNail, 1))
                    Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex]->ReplaceObject(objectWoodplank, 1, objectWoodWallEW, 1);
}

void Crafting::CreateWoodWallCorner(Point p)
{
    int objectWoodplank = DataLoading::GetDescriptionIndexByName("ObjectWoodPlank");
    int objectIronNail = DataLoading::GetDescriptionIndexByName("ObjectIronNail");
    int objectStoneHammer = DataLoading::GetDescriptionIndexByName("ObjectStoneHammer");
    int objectWoodWallCorner = DataLoading::GetDescriptionIndexByName("ObjectWoodWallCorner");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectWoodplank))
        if (Global::statePlayer->ConsumeNRGY(5))
            if (Global::statePlayer->m_inventory.HasItemInInventory(objectStoneHammer))
                if (Global::statePlayer->m_inventory.UseItemInInventory(objectIronNail, 1))
                    Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex]->ReplaceObject(objectWoodplank, 1, objectWoodWallCorner, 1);
}


void Crafting::HarvestStrawberry(Point p)
{
    int objectRipeStrawberryPlant = DataLoading::GetDescriptionIndexByName("ObjectRipeStrawberryPlant");
    int objectHarvestedStrawberryPlant = DataLoading::GetDescriptionIndexByName("ObjectHarvestedStrawberryPlant");
    int objectStrawberry = DataLoading::GetDescriptionIndexByName("ObjectStrawberry");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    TileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.HoldsObjectOfType(objectRipeStrawberryPlant))
        if (Global::statePlayer->ConsumeNRGY(1))
        {
            Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex]->ReplaceObject(objectRipeStrawberryPlant, 1, objectHarvestedStrawberryPlant, 1);
            Global::statePlayer->m_inventory.AddItemToInventory(objectStrawberry);
        }
}