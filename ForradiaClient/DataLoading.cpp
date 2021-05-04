#include "DataLoading.h"
#include <string>

using std::string;
using std::make_unique;
using std::move;


void DataLoading::LoadDescriptions()
{

    int descriptionIndex = 0;

//==========================
//      TILES
//==========================


    auto descTileGrass = make_unique<CDataDescription>(CDataDescription());
    descTileGrass->m_propAttributes.insert(std::pair<string, string>("Name", "TileGrass"));
    descriptions[ID_TILE_GRASS] = move(descTileGrass);


    auto descTileWater = make_unique<CDataDescription>(CDataDescription());
    descTileWater->m_propAttributes.insert(std::pair<string, string>("Name", "TileWater"));
    descTileWater->m_propAttributes.insert(std::pair<string, string>("IsAnimated", "True"));
    descTileWater->m_propAttributes.insert(std::pair<string, string>("NumFrames", "3"));
    descTileWater->m_propAttributes.insert(std::pair<string, string>("AnimSpeed", "500"));
    descTileWater->m_propAttributes.insert(std::pair<string, string>("WaterDepthImage", "waterDeep"));
    descriptions[ID_TILE_WATER] = move(descTileWater);


    auto descTileRock = make_unique<CDataDescription>(CDataDescription());
    descTileRock->m_propAttributes.insert(std::pair<string, string>("Name", "TileRock"));
    descriptions[ID_TILE_ROCK] = move(descTileRock);


    auto descTileWoodFloor = make_unique<CDataDescription>(CDataDescription());
    descTileWoodFloor->m_propAttributes.insert(std::pair<string, string>("Name", "TileWoodFloor"));
    descriptions[ID_TILE_WOODFLOOR] = move(descTileWoodFloor);

    auto descTileStoneSlab = make_unique<CDataDescription>(CDataDescription());
    descTileStoneSlab->m_propAttributes.insert(std::pair<string, string>("Name", "TileStoneSlab"));
    descriptions[ID_TILE_STONESLAB] = move(descTileStoneSlab);

    auto descTileCaveFloor = make_unique<CDataDescription>(CDataDescription());
    descTileCaveFloor->m_propAttributes.insert(std::pair<string, string>("Name", "TileCaveFloor"));
    descriptions[ID_TILE_CAVEFLOOR] = move(descTileCaveFloor);

    auto descTileSand = make_unique<CDataDescription>(CDataDescription());
    descTileSand->m_propAttributes.insert(std::pair<string, string>("Name", "TileSand"));
    descriptions[ID_TILE_SAND] = move(descTileSand);

    auto descTileClay = make_unique<CDataDescription>(CDataDescription());
    descTileClay->m_propAttributes.insert(std::pair<string, string>("Name", "TileClay"));
    descriptions[ID_TILE_CLAY] = move(descTileClay);



//==========================
//      OBJECTS
//==========================


    auto descObjectTree1 = make_unique<CDataDescription>(CDataDescription());
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectTree1"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "8"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "8"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("ImageFocusedObjectAnimation", "tree1Falling"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Tree"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("RandomScaling", "True"));
    descObjectTree1->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descriptions[ID_OBJECT_TREE1] = move(descObjectTree1);


    auto descObjectTree2 = make_unique<CDataDescription>(CDataDescription());
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectTree2"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "8"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "8"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("ImageFocusedObjectAnimation", "tree2Falling"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Tree"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("RandomScaling", "True"));
    descObjectTree2->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descriptions[ID_OBJECT_TREE2] = move(descObjectTree2);


    auto descObjectFoeDead = make_unique<CDataDescription>(CDataDescription());
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectFoeDead"));
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "2"));
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Dead Foe"));
    descObjectFoeDead->m_propAttributes.insert(std::pair<string, string>("TicksToVanish", "5000"));
    descriptions[descriptionIndex++] = move(descObjectFoeDead);



    auto descObjectFoeDeadDuplicate = make_unique<CDataDescription>(CDataDescription());
    descObjectFoeDeadDuplicate->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectFoeDeadDuplicate"));
    descObjectFoeDeadDuplicate->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "2"));
    descObjectFoeDeadDuplicate->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectFoeDeadDuplicate->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectFoeDeadDuplicate->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descObjectFoeDeadDuplicate->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectFoeDeadDuplicate->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Foe Dead"));
    descriptions[descriptionIndex++] = move(descObjectFoeDeadDuplicate);



    auto descObjectBoulder = make_unique<CDataDescription>(CDataDescription());
    descObjectBoulder->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectBoulder"));
    descObjectBoulder->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "3"));
    descObjectBoulder->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "3"));
    descObjectBoulder->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectBoulder->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descObjectBoulder->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectBoulder->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Boulder"));
    descriptions[ID_OBJECT_BOULDER] = move(descObjectBoulder);



    auto descObjectWoodWallEW = make_unique<CDataDescription>(CDataDescription());
    descObjectWoodWallEW->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectWoodWallEW"));
    descObjectWoodWallEW->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectWoodWallEW->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "3"));
    descObjectWoodWallEW->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectWoodWallEW->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectWoodWallEW->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Wood Wall"));
    descriptions[descriptionIndex++] = move(descObjectWoodWallEW);



    auto descObjectWoodWallNS = make_unique<CDataDescription>(CDataDescription());
    descObjectWoodWallNS->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectWoodWallNS"));
    descObjectWoodWallNS->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectWoodWallNS->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "3"));
    descObjectWoodWallNS->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectWoodWallNS->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectWoodWallNS->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Wood Wall"));
    descriptions[descriptionIndex++] = move(descObjectWoodWallNS);



    auto descObjectWoodWallCorner = make_unique<CDataDescription>(CDataDescription());
    descObjectWoodWallCorner->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectWoodWallCorner"));
    descObjectWoodWallCorner->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectWoodWallCorner->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "3"));
    descObjectWoodWallCorner->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectWoodWallCorner->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectWoodWallCorner->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Wood Wall"));
    descriptions[descriptionIndex++] = move(descObjectWoodWallCorner);


    auto descObjectWoodWallStairsUp = make_unique<CDataDescription>(CDataDescription());
    descObjectWoodWallStairsUp->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectStairsUp"));
    descObjectWoodWallStairsUp->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectWoodWallStairsUp->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectWoodWallStairsUp->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectWoodWallStairsUp->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectWoodWallStairsUp->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Wooden Stairs"));
    descriptions[descriptionIndex++] = move(descObjectWoodWallStairsUp);



    auto descObjectWoodWallStairsDown = make_unique<CDataDescription>(CDataDescription());
    descObjectWoodWallStairsDown->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectStairsDown"));
    descObjectWoodWallStairsDown->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectWoodWallStairsDown->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectWoodWallStairsDown->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectWoodWallStairsDown->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectWoodWallStairsDown->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Wooden Stairs"));
    descriptions[descriptionIndex++] = move(descObjectWoodWallStairsDown);



    auto descObjectBush = make_unique<CDataDescription>(CDataDescription());
    descObjectBush->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectBush"));
    descObjectBush->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectBush->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectBush->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectBush->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectBush->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Bush"));
    descObjectBush->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descriptions[ID_OBJECT_BUSH] = move(descObjectBush);




    auto descObjectBushTall = make_unique<CDataDescription>(CDataDescription());
    descObjectBushTall->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectBushTall"));
    descObjectBushTall->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectBushTall->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectBushTall->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectBushTall->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectBushTall->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Tall Bush"));
    descObjectBushTall->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descriptions[ID_OBJECT_BUSHTALL] = move(descObjectBushTall);




    auto descObjectTreasureChest_NOT_USED = make_unique<CDataDescription>(CDataDescription());
    descObjectTreasureChest_NOT_USED->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectNOT_USED"));
    descObjectTreasureChest_NOT_USED->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "0"));
    descObjectTreasureChest_NOT_USED->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "0"));
    descObjectTreasureChest_NOT_USED->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectTreasureChest_NOT_USED->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectTreasureChest_NOT_USED->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Treasure Chest NOT USED"));
    descriptions[descriptionIndex++] = move(descObjectTreasureChest_NOT_USED);




    auto descObjectTrainRailEW = make_unique<CDataDescription>(CDataDescription());
    descObjectTrainRailEW->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectTrainRailEW"));
    descObjectTrainRailEW->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectTrainRailEW->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectTrainRailEW->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectTrainRailEW->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectTrainRailEW->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Train Rail"));
    descriptions[descriptionIndex++] = move(descObjectTrainRailEW);




    auto descObjectTrainRailEWStationS = make_unique<CDataDescription>(CDataDescription());
    descObjectTrainRailEWStationS->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectTrainRailEWStationS"));
    descObjectTrainRailEWStationS->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectTrainRailEWStationS->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "3"));
    descObjectTrainRailEWStationS->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectTrainRailEWStationS->m_propAttributes.insert(std::pair<string, string>("YOffsetFactor", "1"));
    descObjectTrainRailEWStationS->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectTrainRailEWStationS->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Train Station"));
    descriptions[descriptionIndex++] = move(descObjectTrainRailEWStationS);



    auto descObjectFountain = make_unique<CDataDescription>(CDataDescription());
    descObjectFountain->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectFountain"));
    descObjectFountain->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectFountain->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectFountain->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectFountain->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectFountain->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Fountain"));
    descriptions[descriptionIndex++] = move(descObjectFountain);





    auto descObjectSignConstructionPlace = make_unique<CDataDescription>(CDataDescription());
    descObjectSignConstructionPlace->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectSignConstructionPlace"));
    descObjectSignConstructionPlace->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectSignConstructionPlace->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectSignConstructionPlace->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectSignConstructionPlace->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectSignConstructionPlace->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Construction Place Sign"));
    descriptions[descriptionIndex++] = move(descObjectSignConstructionPlace);





    auto descObjectWoodLog = make_unique<CDataDescription>(CDataDescription());
    descObjectWoodLog->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectWoodLog"));
    descObjectWoodLog->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectWoodLog->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectWoodLog->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectWoodLog->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectWoodLog->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Wood Log"));
    descriptions[descriptionIndex++] = move(descObjectWoodLog);





    auto descObjectFelledTree = make_unique<CDataDescription>(CDataDescription());
    descObjectFelledTree->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectFelledTree"));
    descObjectFelledTree->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "3"));
    descObjectFelledTree->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "3"));
    descObjectFelledTree->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectFelledTree->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectFelledTree->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Felled Tree"));
    descObjectFelledTree->m_propAttributes.insert(std::pair<string, string>("HasAmount", "True"));
    descriptions[descriptionIndex++] = move(descObjectFelledTree);




    auto descObjectPoolOfBlood = make_unique<CDataDescription>(CDataDescription());
    descObjectPoolOfBlood->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectPoolOfBlood"));
    descObjectPoolOfBlood->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectPoolOfBlood->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectPoolOfBlood->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectPoolOfBlood->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descObjectPoolOfBlood->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectPoolOfBlood->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Pool Of Blood"));
    descriptions[descriptionIndex++] = move(descObjectPoolOfBlood);




    auto descObjectStone = make_unique<CDataDescription>(CDataDescription());
    descObjectStone->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectStone"));
    descObjectStone->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectStone->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectStone->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectStone->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectStone->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Stone"));
    descriptions[descriptionIndex++] = move(descObjectStone);


    auto descObjectIronOre = make_unique<CDataDescription>(CDataDescription());
    descObjectIronOre->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectIronOre"));
    descObjectIronOre->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectIronOre->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectIronOre->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectIronOre->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectIronOre->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Iron Ore"));
    descriptions[descriptionIndex++] = move(descObjectIronOre);


    auto descObjectApple = make_unique<CDataDescription>(CDataDescription());
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectApple"));
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Apple"));
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("FoodAmount", "10"));
    descObjectApple->m_propAttributes.insert(std::pair<string, string>("FoodSpeed", "1"));
    descriptions[descriptionIndex++] = move(descObjectApple);


    auto descObjectWoodPlank = make_unique<CDataDescription>(CDataDescription());
    descObjectWoodPlank->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectWoodPlank"));
    descObjectWoodPlank->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectWoodPlank->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectWoodPlank->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectWoodPlank->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectWoodPlank->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Wood Plank"));
    descriptions[descriptionIndex++] = move(descObjectWoodPlank);



    auto descObjectUnloadedCampfire = make_unique<CDataDescription>(CDataDescription());
    descObjectUnloadedCampfire->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectUnloadedCampfire"));
    descObjectUnloadedCampfire->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "2"));
    descObjectUnloadedCampfire->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectUnloadedCampfire->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectUnloadedCampfire->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectUnloadedCampfire->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Unloaded Campfire"));
    descriptions[descriptionIndex++] = move(descObjectUnloadedCampfire);



    auto descObjectLoadedCampfire = make_unique<CDataDescription>(CDataDescription());
    descObjectLoadedCampfire->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectLoadedCampfire"));
    descObjectLoadedCampfire->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "2"));
    descObjectLoadedCampfire->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectLoadedCampfire->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectLoadedCampfire->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectLoadedCampfire->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Loaded Campfire"));
    descriptions[descriptionIndex++] = move(descObjectLoadedCampfire);



    auto descObjectBurningCampfire = make_unique<CDataDescription>(CDataDescription());
    descObjectBurningCampfire->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectBurningCampfire"));
    descObjectBurningCampfire->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "2"));
    descObjectBurningCampfire->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectBurningCampfire->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectBurningCampfire->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectBurningCampfire->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Burning Campfire"));
    descriptions[descriptionIndex++] = move(descObjectBurningCampfire);



    auto descObjectReed = make_unique<CDataDescription>(CDataDescription());
    descObjectReed->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectReed"));
    descObjectReed->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectReed->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "2"));
    descObjectReed->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectReed->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectReed->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Reed"));
    descObjectReed->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", "True"));
    descriptions[descriptionIndex++] = move(descObjectReed);


    auto descObjectShovel = make_unique<CDataDescription>(CDataDescription());
    descObjectShovel->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectShovel"));
    descObjectShovel->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectShovel->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectShovel->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectShovel->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectShovel->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Shovel"));
    descriptions[descriptionIndex++] = move(descObjectShovel);


    auto descObjectMatches = make_unique<CDataDescription>(CDataDescription());
    descObjectMatches->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectMatches"));
    descObjectMatches->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectMatches->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectMatches->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectMatches->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectMatches->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Matches"));
    descriptions[descriptionIndex++] = move(descObjectMatches);


    auto descObjectClayLump = make_unique<CDataDescription>(CDataDescription());
    descObjectClayLump->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectClayLump"));
    descObjectClayLump->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectClayLump->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectClayLump->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectClayLump->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectClayLump->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Clay Lump"));
    descriptions[descriptionIndex++] = move(descObjectClayLump);


    auto descObjectBrick = make_unique<CDataDescription>(CDataDescription());
    descObjectBrick->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectBrick"));
    descObjectBrick->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1"));
    descObjectBrick->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "1"));
    descObjectBrick->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "False"));
    descObjectBrick->m_propAttributes.insert(std::pair<string, string>("Movable", "True"));
    descObjectBrick->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Brick"));
    descriptions[descriptionIndex++] = move(descObjectBrick);


    auto descObjectUnloadedMeltingFurnace = make_unique<CDataDescription>(CDataDescription());
    descObjectUnloadedMeltingFurnace->m_propAttributes.insert(std::pair<string, string>("Name", "ObjectUnloadedMeltingFurnace"));
    descObjectUnloadedMeltingFurnace->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", "1.5"));
    descObjectUnloadedMeltingFurnace->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", "3"));
    descObjectUnloadedMeltingFurnace->m_propAttributes.insert(std::pair<string, string>("IsObstacle", "True"));
    descObjectUnloadedMeltingFurnace->m_propAttributes.insert(std::pair<string, string>("Movable", "False"));
    descObjectUnloadedMeltingFurnace->m_propAttributes.insert(std::pair<string, string>("ReadableName", "Unloaded Melting Furnace"));
    descriptions[descriptionIndex++] = move(descObjectUnloadedMeltingFurnace);




//==========================
//      CRAFTING ECIPES
//==========================


    auto descRecipeWoodPlank = make_unique<CDataDescription>(CDataDescription());
    descRecipeWoodPlank->m_propAttributes.insert(std::pair<string, string>("Name", "RecipeWoodPlankRecipe"));
    descRecipeWoodPlank->m_propAttributes.insert(std::pair<string, string>("FocusObject", "WoodLog"));
    descRecipeWoodPlank->m_propAttributes.insert(std::pair<string, string>("ResultObject", "WoodPlank"));
    descriptions[descriptionIndex++] = move(descRecipeWoodPlank);
    




//==========================
//      ADDITIONAL
//==========================


    auto descCursor = make_unique<CDataDescription>(CDataDescription());
    descCursor->m_propAttributes.insert(std::pair<string, string>("Name", "Cursor"));
    descriptions[ID_CURSOR] = move(descCursor);

    auto descCursorHovering = make_unique<CDataDescription>(CDataDescription());
    descCursorHovering->m_propAttributes.insert(std::pair<string, string>("Name", "CursorHovering"));
    descriptions[ID_CURSOR_HOVERING] = move(descCursorHovering);

    auto descIconsBackground = make_unique<CDataDescription>(CDataDescription());
    descIconsBackground->m_propAttributes.insert(std::pair<string, string>("Name", "IconsBackground"));
    descriptions[ID_ICONS_BACKGROUND] = move(descIconsBackground);

    auto descIcosSystem = make_unique<CDataDescription>(CDataDescription());
    descIcosSystem->m_propAttributes.insert(std::pair<string, string>("Name", "IconSystem"));
    descriptions[ID_ICON_SYSTEM] = move(descIcosSystem);

    auto descIconCrafting = make_unique<CDataDescription>(CDataDescription());
    descIconCrafting->m_propAttributes.insert(std::pair<string, string>("Name", "IconCrafting"));
    descriptions[ID_ICON_CRAFTING] = move(descIconCrafting);

    auto descIconInventory = make_unique<CDataDescription>(CDataDescription());
    descIconInventory->m_propAttributes.insert(std::pair<string, string>("Name", "IconInventory"));
    descriptions[ID_ICON_INVENTORY] = move(descIconInventory);

    auto descMapPreviewBack = make_unique<CDataDescription>(CDataDescription());
    descMapPreviewBack->m_propAttributes.insert(std::pair<string, string>("Name", "MapPreviewBack"));
    descriptions[ID_MAP_PREVIEW_BACK] = move(descMapPreviewBack);

    auto descTerminalBack = make_unique<CDataDescription>(CDataDescription());
    descTerminalBack->m_propAttributes.insert(std::pair<string, string>("Name", "TerminalBack"));
    descriptions[ID_TERMINAL_BACK] = move(descTerminalBack);

    auto descTileTargetEffect = make_unique<CDataDescription>(CDataDescription());
    descTileTargetEffect->m_propAttributes.insert(std::pair<string, string>("Name", "TileTargetEffect"));
    descriptions[ID_TILE_TARGET_EFFECT] = move(descTileTargetEffect);

    auto descShadow = make_unique<CDataDescription>(CDataDescription());
    descShadow->m_propAttributes.insert(std::pair<string, string>("Name", "Shadow"));
    descriptions[ID_SHADOW] = move(descShadow);

    auto descFoe = make_unique<CDataDescription>(CDataDescription());
    descFoe->m_propAttributes.insert(std::pair<string, string>("Name", "Foe"));
    descriptions[ID_FOE] = move(descFoe);

    auto descButterfly = make_unique<CDataDescription>(CDataDescription());
    descButterfly->m_propAttributes.insert(std::pair<string, string>("Name", "Butterfly"));
    descriptions[ID_BUTTERFLY] = move(descButterfly);

    auto descPinkSlime = make_unique<CDataDescription>(CDataDescription());
    descPinkSlime->m_propAttributes.insert(std::pair<string, string>("Name", "PinkSlime"));
    descriptions[ID_PINKSLIME] = move(descPinkSlime);

    auto descHitEffect = make_unique<CDataDescription>(CDataDescription());
    descHitEffect->m_propAttributes.insert(std::pair<string, string>("Name", "HitEffect"));
    descriptions[ID_HIT_EFFECT] = move(descHitEffect);

    auto descSpawnEffect0 = make_unique<CDataDescription>(CDataDescription());
    descSpawnEffect0->m_propAttributes.insert(std::pair<string, string>("Name", "SpawnEffect0"));
    descriptions[ID_SPAWN_EFFECT_0] = move(descSpawnEffect0);

    auto descSpawnEffect1 = make_unique<CDataDescription>(CDataDescription());
    descSpawnEffect1->m_propAttributes.insert(std::pair<string, string>("Name", "SpawnEffect1"));
    descriptions[ID_SPAWN_EFFECT_1] = move(descSpawnEffect1);

    auto descSpawnEffect2 = make_unique<CDataDescription>(CDataDescription());
    descSpawnEffect2->m_propAttributes.insert(std::pair<string, string>("Name", "SpawnEffect2"));
    descriptions[ID_SPAWN_EFFECT_2] = move(descSpawnEffect2);

    auto descNPC = make_unique<CDataDescription>(CDataDescription());
    descNPC->m_propAttributes.insert(std::pair<string, string>("Name", "NPC"));
    descriptions[ID_NPC] = move(descNPC);

    auto descChatBubble = make_unique<CDataDescription>(CDataDescription());
    descChatBubble->m_propAttributes.insert(std::pair<string, string>("Name", "ChatBubble"));
    descriptions[ID_CHAT_BUBBLE] = move(descChatBubble);

    auto descTree1Falling0 = make_unique<CDataDescription>(CDataDescription());
    descTree1Falling0->m_propAttributes.insert(std::pair<string, string>("Name", "Tree1Falling0"));
    descriptions[ID_TREE1_FALLING_0] = move(descTree1Falling0);

    auto descTree1Falling1 = make_unique<CDataDescription>(CDataDescription());
    descTree1Falling1->m_propAttributes.insert(std::pair<string, string>("Name", "Tree1Falling1"));
    descriptions[ID_TREE1_FALLING_1] = move(descTree1Falling1);

    auto descTree1Falling2 = make_unique<CDataDescription>(CDataDescription());
    descTree1Falling2->m_propAttributes.insert(std::pair<string, string>("Name", "Tree1Falling2"));
    descriptions[ID_TREE1_FALLING_2] = move(descTree1Falling2);

    auto descTree2Falling0 = make_unique<CDataDescription>(CDataDescription());
    descTree2Falling0->m_propAttributes.insert(std::pair<string, string>("Name", "Tree2Falling0"));
    descriptions[ID_TREE2_FALLING_0] = move(descTree2Falling0);

    auto descTree2Falling1 = make_unique<CDataDescription>(CDataDescription());
    descTree2Falling1->m_propAttributes.insert(std::pair<string, string>("Name", "Tree2Falling1"));
    descriptions[ID_TREE2_FALLING_1] = move(descTree2Falling1);

    auto descTree2Falling2 = make_unique<CDataDescription>(CDataDescription());
    descTree2Falling2->m_propAttributes.insert(std::pair<string, string>("Name", "Tree2Falling2"));
    descriptions[ID_TREE2_FALLING_2] = move(descTree2Falling2);

    auto descPlayer = make_unique<CDataDescription>(CDataDescription());
    descPlayer->m_propAttributes.insert(std::pair<string, string>("Name", "Player"));
    descriptions[ID_PLAYER] = move(descPlayer);

    auto descForradiaStartText0 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText0->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText0"));
    descriptions[ID_FORRADIA_START_TEXT_0] = move(descForradiaStartText0);

    auto descForradiaStartText1 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText1->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText1"));
    descriptions[ID_FORRADIA_START_TEXT_1] = move(descForradiaStartText1);

    auto descForradiaStartText2 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText2->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText2"));
    descriptions[ID_FORRADIA_START_TEXT_2] = move(descForradiaStartText2);

    auto descForradiaStartText3 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText3->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText3"));
    descriptions[ID_FORRADIA_START_TEXT_3] = move(descForradiaStartText3);

    auto descForradiaStartText4 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText4->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText4"));
    descriptions[ID_FORRADIA_START_TEXT_4] = move(descForradiaStartText4);

    auto descForradiaStartText5 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText5->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText5"));
    descriptions[ID_FORRADIA_START_TEXT_5] = move(descForradiaStartText5);

    auto descForradiaStartText6 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText6->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText6"));
    descriptions[ID_FORRADIA_START_TEXT_6] = move(descForradiaStartText6);

    auto descForradiaStartText7 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText7->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText7"));
    descriptions[ID_FORRADIA_START_TEXT_7] = move(descForradiaStartText7);

    auto descForradiaStartText8 = make_unique<CDataDescription>(CDataDescription());
    descForradiaStartText8->m_propAttributes.insert(std::pair<string, string>("Name", "ForradiaStartText8"));
    descriptions[ID_FORRADIA_START_TEXT_8] = move(descForradiaStartText8);

    auto descMenuButtonBack = make_unique<CDataDescription>(CDataDescription());
    descMenuButtonBack->m_propAttributes.insert(std::pair<string, string>("Name", "MenuButtonBack"));
    descriptions[ID_MENU_BUTTON_BACK] = move(descMenuButtonBack);

    auto descMenuButtonBackHovered = make_unique<CDataDescription>(CDataDescription());
    descMenuButtonBackHovered->m_propAttributes.insert(std::pair<string, string>("Name", "MenuButtonBackHovered"));
    descriptions[ID_MENU_BUTTON_BACK_HOVERED] = move(descMenuButtonBackHovered);

    auto descTitleStartNewGame = make_unique<CDataDescription>(CDataDescription());
    descTitleStartNewGame->m_propAttributes.insert(std::pair<string, string>("Name", "TitleStartNewGame"));
    descriptions[ID_TITLE_START_NEW_GAME] = move(descTitleStartNewGame);





    auto descSkillEffect0 = make_unique<CDataDescription>(CDataDescription());
    descSkillEffect0->m_propAttributes.insert(std::pair<string, string>("Name", "SkillEffect0"));
    descriptions[ID_SKILL_EFFECT_0] = move(descSkillEffect0);

    auto descSkillEffect1 = make_unique<CDataDescription>(CDataDescription());
    descSkillEffect1->m_propAttributes.insert(std::pair<string, string>("Name", "SkillEffect1"));
    descriptions[ID_SKILL_EFFECT_1] = move(descSkillEffect1);

    auto descSkillEffect1_0 = make_unique<CDataDescription>(CDataDescription());
    descSkillEffect1_0->m_propAttributes.insert(std::pair<string, string>("Name", "SkillEffect1_0"));
    descriptions[ID_SKILL_EFFECT_1_0] = move(descSkillEffect1_0);

    auto descSkillEffect1_1 = make_unique<CDataDescription>(CDataDescription());
    descSkillEffect1_1->m_propAttributes.insert(std::pair<string, string>("Name", "SkillEffect1_1"));
    descriptions[ID_SKILL_EFFECT_1_1] = move(descSkillEffect1_1);

    auto descSkillEffect1_2 = make_unique<CDataDescription>(CDataDescription());
    descSkillEffect1_2->m_propAttributes.insert(std::pair<string, string>("Name", "SkillEffect1_2"));
    descriptions[ID_SKILL_EFFECT_1_2] = move(descSkillEffect1_2);

    auto descUnseenTile = make_unique<CDataDescription>(CDataDescription());
    descUnseenTile->m_propAttributes.insert(std::pair<string, string>("Name", "UnseenTile"));
    descriptions[ID_UNSEEN_TILE] = move(descUnseenTile);

    auto descWaterDepth0 = make_unique<CDataDescription>(CDataDescription());
    descWaterDepth0->m_propAttributes.insert(std::pair<string, string>("Name", "WaterDepth0"));
    descriptions[ID_WATER_DEPTH_0] = move(descWaterDepth0);

    auto descWaterDepth1 = make_unique<CDataDescription>(CDataDescription());
    descWaterDepth1->m_propAttributes.insert(std::pair<string, string>("Name", "WaterDepth1"));
    descriptions[ID_WATER_DEPTH_1] = move(descWaterDepth1);

    auto descWaterDepth2 = make_unique<CDataDescription>(CDataDescription());
    descWaterDepth2->m_propAttributes.insert(std::pair<string, string>("Name", "WaterDepth2"));
    descriptions[ID_WATER_DEPTH_2] = move(descWaterDepth2);


    auto descEdgeRight = make_unique<CDataDescription>(CDataDescription());
    descEdgeRight->m_propAttributes.insert(std::pair<string, string>("Name", "EdgeRight"));
    descriptions[ID_EDGE_RIGHT] = move(descEdgeRight);


    auto descEdgeTop = make_unique<CDataDescription>(CDataDescription());
    descEdgeTop->m_propAttributes.insert(std::pair<string, string>("Name", "EdgeTop"));
    descriptions[ID_EDGE_TOP] = move(descEdgeTop);


    auto descElevLeft= make_unique<CDataDescription>(CDataDescription());
    descElevLeft->m_propAttributes.insert(std::pair<string, string>("Name", "ElevLeft"));
    descriptions[ID_ELEV_LEFT] = move(descElevLeft);


    auto descElevBottom = make_unique<CDataDescription>(CDataDescription());
    descElevBottom->m_propAttributes.insert(std::pair<string, string>("Name", "ElevBottom"));
    descriptions[ID_ELEV_BOTTOM] = move(descElevBottom);


    auto descElevLeftDark = make_unique<CDataDescription>(CDataDescription());
    descElevLeftDark->m_propAttributes.insert(std::pair<string, string>("Name", "ElevLeftDark"));
    descriptions[ID_ELEV_LEFT_DARK] = move(descElevLeftDark);


    auto descElevBottomDark = make_unique<CDataDescription>(CDataDescription());
    descElevBottomDark->m_propAttributes.insert(std::pair<string, string>("Name", "ElevBottomDark"));
    descriptions[ID_ELEV_BOTTOM_DARK] = move(descElevBottomDark);


    auto descElevLeftRock = make_unique<CDataDescription>(CDataDescription());
    descElevLeftRock->m_propAttributes.insert(std::pair<string, string>("Name", "ElevLeftRock"));
    descriptions[ID_ELEV_LEFT_ROCK] = move(descElevLeftRock);


    auto descElevBottomRock = make_unique<CDataDescription>(CDataDescription());
    descElevBottomRock->m_propAttributes.insert(std::pair<string, string>("Name", "ElevBottomRock"));
    descriptions[ID_ELEV_BOTTOM_ROCK] = move(descElevBottomRock);


    auto descElevLeftDarkRock = make_unique<CDataDescription>(CDataDescription());
    descElevLeftDarkRock->m_propAttributes.insert(std::pair<string, string>("Name", "ElevLeftDarkRock"));
    descriptions[ID_ELEV_LEFT_DARK_ROCK] = move(descElevLeftDarkRock);


    auto descElevBottomDarkRock = make_unique<CDataDescription>(CDataDescription());
    descElevBottomDarkRock->m_propAttributes.insert(std::pair<string, string>("Name", "ElevBottomDarkRock"));
    descriptions[ID_ELEV_BOTTOM_DARK_ROCK] = move(descElevBottomDarkRock);


    auto descEdgeRightRock = make_unique<CDataDescription>(CDataDescription());
    descEdgeRightRock->m_propAttributes.insert(std::pair<string, string>("Name", "EdgeRightRock"));
    descriptions[ID_EDGE_RIGHT_ROCK] = move(descEdgeRightRock);


    auto descEdgeTopRock = make_unique<CDataDescription>(CDataDescription());
    descEdgeTopRock->m_propAttributes.insert(std::pair<string, string>("Name", "EdgeTopRock"));
    descriptions[ID_EDGE_TOP_ROCK] = move(descEdgeTopRock);


    auto descElevCorner = make_unique<CDataDescription>(CDataDescription());
    descElevCorner->m_propAttributes.insert(std::pair<string, string>("Name", "ElevCorner"));
    descriptions[ID_ELEV_CORNER] = move(descElevCorner);


    auto descGrassStraws = make_unique<CDataDescription>(CDataDescription());
    descGrassStraws->m_propAttributes.insert(std::pair<string, string>("Name", "GrassStraws"));
    descriptions[ID_GRASS_STRAWS] = move(descGrassStraws);


    auto descCaveEntranceNorth = make_unique<CDataDescription>(CDataDescription());
    descCaveEntranceNorth->m_propAttributes.insert(std::pair<string, string>("Name", "CaveEntranceNorth"));
    descriptions[ID_CAVE_ENTRANCE_NORTH] = move(descCaveEntranceNorth);


    auto descCaveEntranceEast = make_unique<CDataDescription>(CDataDescription());
    descCaveEntranceEast->m_propAttributes.insert(std::pair<string, string>("Name", "CaveEntranceEast"));
    descriptions[ID_CAVE_ENTRANCE_EAST] = move(descCaveEntranceEast);


    auto descCaveEntranceSouth = make_unique<CDataDescription>(CDataDescription());
    descCaveEntranceSouth->m_propAttributes.insert(std::pair<string, string>("Name", "CaveEntranceSouth"));
    descriptions[ID_CAVE_ENTRANCE_SOUTH] = move(descCaveEntranceSouth);


    auto descCaveEntranceWest = make_unique<CDataDescription>(CDataDescription());
    descCaveEntranceWest->m_propAttributes.insert(std::pair<string, string>("Name", "CaveEntranceWest"));
    descriptions[ID_CAVE_ENTRANCE_WEST] = move(descCaveEntranceWest);


    auto descTileHoverEffect = make_unique<CDataDescription>(CDataDescription());
    descTileHoverEffect->m_propAttributes.insert(std::pair<string, string>("Name", "TileHoverEffect"));
    descriptions[ID_TILE_HOVER_EFFECT] = move(descTileHoverEffect);


    auto descTrainLocomotive_0 = make_unique<CDataDescription>(CDataDescription());
    descTrainLocomotive_0->m_propAttributes.insert(std::pair<string, string>("Name", "TrainLocomotive0"));
    descriptions[ID_TRAIN_LOCOMOTIVE_0] = move(descTrainLocomotive_0);


    auto descTrainLocomotive_1 = make_unique<CDataDescription>(CDataDescription());
    descTrainLocomotive_1->m_propAttributes.insert(std::pair<string, string>("Name", "TrainLocomotive1"));
    descriptions[ID_TRAIN_LOCOMOTIVE_1] = move(descTrainLocomotive_1);


    auto descTrainLocomotive_2 = make_unique<CDataDescription>(CDataDescription());
    descTrainLocomotive_2->m_propAttributes.insert(std::pair<string, string>("Name", "TrainLocomotive2"));
    descriptions[ID_TRAIN_LOCOMOTIVE_2] = move(descTrainLocomotive_2);


    auto descTrainCarriage = make_unique<CDataDescription>(CDataDescription());
    descTrainCarriage->m_propAttributes.insert(std::pair<string, string>("Name", "TrainCarriage"));
    descriptions[ID_TRAIN_CARRIAGE] = move(descTrainCarriage);


    auto descIconCloseWindow = make_unique<CDataDescription>(CDataDescription());
    descIconCloseWindow->m_propAttributes.insert(std::pair<string, string>("Name", "IconCloseWindow"));
    descriptions[ID_ICON_CLOSE_WINDOW] = move(descIconCloseWindow);


    auto descOptionIconUnselected = make_unique<CDataDescription>(CDataDescription());
    descOptionIconUnselected->m_propAttributes.insert(std::pair<string, string>("Name", "OptionIconUnselected"));
    descriptions[ID_OPTION_ICON_UNSELECTED] = move(descOptionIconUnselected);


    auto descOptionIconSelected = make_unique<CDataDescription>(CDataDescription());
    descOptionIconSelected->m_propAttributes.insert(std::pair<string, string>("Name", "OptionIconSelected"));
    descriptions[ID_OPTION_ICON_SELECTED] = move(descOptionIconSelected);


    auto descEffectVanish0 = make_unique<CDataDescription>(CDataDescription());
    descEffectVanish0->m_propAttributes.insert(std::pair<string, string>("Name", "EffectVanish0"));
    descriptions[ID_EFFECT_VANISH_0] = move(descEffectVanish0);

    auto descEffectVanish1 = make_unique<CDataDescription>(CDataDescription());
    descEffectVanish1->m_propAttributes.insert(std::pair<string, string>("Name", "EffectVanish1"));
    descriptions[ID_EFFECT_VANISH_1] = move(descEffectVanish1);

    auto descEffectVanish2 = make_unique<CDataDescription>(CDataDescription());
    descEffectVanish2->m_propAttributes.insert(std::pair<string, string>("Name", "EffectVanish2"));
    descriptions[ID_EFFECT_VANISH_2] = move(descEffectVanish2);

    auto descEffectVanish3 = make_unique<CDataDescription>(CDataDescription());
    descEffectVanish3->m_propAttributes.insert(std::pair<string, string>("Name", "EffectVanish3"));
    descriptions[ID_EFFECT_VANISH_3] = move(descEffectVanish3);

    auto descEffectVanish4 = make_unique<CDataDescription>(CDataDescription());
    descEffectVanish4->m_propAttributes.insert(std::pair<string, string>("Name", "EffectVanish4"));
    descriptions[ID_EFFECT_VANISH_4] = move(descEffectVanish4);

    auto descEffectVanish5 = make_unique<CDataDescription>(CDataDescription());
    descEffectVanish5->m_propAttributes.insert(std::pair<string, string>("Name", "EffectVanish5"));
    descriptions[ID_EFFECT_VANISH_5] = move(descEffectVanish5);

    auto descWindowBack = make_unique<CDataDescription>(CDataDescription());
    descWindowBack->m_propAttributes.insert(std::pair<string, string>("Name", "WindowBack"));
    descriptions[ID_WINDOW_BACK] = move(descWindowBack);

    auto descInventorySlotBack = make_unique<CDataDescription>(CDataDescription());
    descInventorySlotBack->m_propAttributes.insert(std::pair<string, string>("Name", "InventorySlotBack"));
    descriptions[ID_INVENTORY_SLOT_BACK] = move(descInventorySlotBack);

    auto descIconActiveFoodItemFrame = make_unique<CDataDescription>(CDataDescription());
    descIconActiveFoodItemFrame->m_propAttributes.insert(std::pair<string, string>("Name", "IconActiveFoodItemFrame"));
    descriptions[ID_ICON_ACTIVE_FOOD_ITEM_FRAME] = move(descIconActiveFoodItemFrame);

}


int DataLoading::GetDescriptionIndexByName(string name) {

    for (int i = 0; i < CONTENT_DB_SIZE; i++)
    {

        if (descriptions[i] == NULL)
            continue;

        if (descriptions[i]->m_propAttributes["Name"] == name)
            return i;
    }
    
    return -1;

}

