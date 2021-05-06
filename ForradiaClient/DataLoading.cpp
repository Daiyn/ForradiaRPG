#include "DataLoading.h"
#include <string>

using std::string;
using std::make_unique;
using std::move;
using std::pair;
using std::to_string;

void DataLoading::LoadDescriptions()
{

    int descriptionIndex = 0;

//==========================
//      TILES
//==========================

    AddDescription(kIDTileGrass, "TileGrass");
    AddDescription(kIDTileWater, "TileWater");
    AddDescription(descriptionIndex++, "TileWater0");
    AddDescription(descriptionIndex++, "TileWater1");
    AddDescription(descriptionIndex++, "TileWater2");
    AddDescription(kIDTileRock, "TileRock");
    AddDescription(kIDTileWoodfloor, "TileWoodfloor");
    AddDescription(kIDTileStoneslab, "TileStoneSlab");
    AddDescription(kIDTileCavefloor, "TileCaveFloor");
    AddDescription(kIDTileSand, "TileSand");
    AddDescription(kIDTileClay, "TileClay");



//==========================
//      OBJECTS
//==========================

    AddDescriptionEx(kIDObjectTree1, "ObjectTree1", 8, 8, "tree1Falling", true, false, "Tree", true, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(kIDObjectTree2, "ObjectTree2", 8, 8, "tree2Falling", true, false, "Tree", true, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectFoeDead", 2, 2, "", false, true, "Dead Foe", false, true, 5000, 0, 0, false, 0, 0);
    AddDescriptionEx(kIDObjectBoulder, "ObjectBoulder", 3, 3, "", true, false, "Boulder", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallEW", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallNS", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallCorner", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStairsUp", 1, 1, "", false, false, "Wooden Stairs Up", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStairsDown", 1, 1, "", false, false, "Wooden Stairs Down", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(kIDObjectBush, "ObjectBush", 1, 1, "", true, false, "Bush", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(kIDObjectBushtall, "ObjectBushTall", 1, 2, "", true, false, "Tall Bush", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectTrainRailEW", 1, 2, "", false, false, "Train Rail", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectTrainRailEWStationS", 1, 3, "", false, false, "Train Station", false, true, -1, 0, 1, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectFountain", 1, 2, "", true, false, "Fountain", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectSignConstructionPlace", 1, 1, "", true, false, "Construction Place Sign", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodLog", 1, 1, "", false, true, "Woodlog", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectFelledTree", 3, 3, "", true, true, "Felled Tree", false, false, -1, 0, 0, true, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectPoolOfBlood", 1, 1, "", false, false, "Pool of Blood", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStone", 1, 1, "", false, true, "Stone", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectIronOre", 1, 1, "", false, true, "Iron Ore", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectCoal", 1, 1, "", false, true, "Coal", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectApple", 1, 1, "", false, true, "Apple", false, false, -1, 0, 0, false, 10, 1);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodPlank", 1, 1, "", false, true, "Woodplank", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectUnloadedCampfire", 2, 2, "", false, false, "Unloaded Campfire", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectLoadedCampfire", 2, 2, "", false, false, "Loaded Campfire", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectBurningCampfire", 2, 2, "", false, false, "Burning Campfire", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectReed", 1, 2, "", true, false, "Reed", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectShovel", 1, 1, "", false, true, "Shovel", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectSaw", 1, 1, "", false, true, "Saw", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectMatches", 1, 1, "", false, true, "Matches", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectClayLump", 1, 1, "", false, true, "Clay Lump", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectBrick", 1, 1, "", false, true, "Brick", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectUnloadedMeltingFurnace", 1.5, 3, "", true, false, "Unloaded Melting Furnace", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectLoadedMeltingFurnace", 1.5, 3, "", true, false, "Loaded Melting Furnace", false, false, -1, 0, 0, true, 0, 0);
    AddDescription(descriptionIndex++, "ObjectBurningCampfire0");
    AddDescription(descriptionIndex++, "ObjectBurningCampfire1");
    AddDescription(descriptionIndex++, "ObjectBurningCampfire2");
    AddDescriptionEx(descriptionIndex++, "ObjectSmallAnvil", 1, 1, "", false, true, "Small Anvil", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectHotMeltingFurnace", 1.5, 3, "", true, false, "Hot Melting Furnace", false, false, -1, 0, 0, true, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectHotIronLump", 1, 1, "", false, true, "Hot Iron Lump", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectIronNail", 1, 1, "", false, true, "Iron Nail", false, false, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStoneHammer", 1, 1, "", false, true, "Stone Hammer", false, false, -1, 0, 0, false, 0, 0);

//==========================
//      ADDITIONAL
//==========================


    AddDescription(kIDCursor, "Cursor");
    AddDescription(kIDCursorHovering, "CursorHovering");
    AddDescription(kIDIconsBackground, "IconsBackground");
    AddDescription(kIDIconSystem, "IconSystem");
    AddDescription(kIDIconCrafting, "IconCrafting");
    AddDescription(kIDIconInventory, "IconInventory");
    AddDescription(kIDFullMapFrameBackground, "MapPreviewBack");
    AddDescription(kIDTerminalBackground, "TerminalBack");
    AddDescription(kIDTileTargetEffect, "TileTargetEffect");
    AddDescription(kIDShadow, "Shadow");
    AddDescription(kIDFoe, "Foe");
    AddDescription(kIDButterfly, "Butterfly");
    AddDescription(kIDPinkSlime, "PinkSlime");
    AddDescription(kIDHitEffect, "HitEffect");
    AddDescription(kIDSpawnEffect0, "SpawnEffect0");
    AddDescription(kIDSpawnEffect1, "SpawnEffect1");
    AddDescription(kIDSpawnEffect2, "SpawnEffect2");
    AddDescription(kIDNPCSprite, "NPC");
    AddDescription(kIDChatBubble, "ChatBubble");
    AddDescription(kIDTree1Falling0, "Tree1Falling0");
    AddDescription(kIDTree1Falling1, "Tree1Falling1");
    AddDescription(kIDTree1Falling2, "Tree1Falling2");
    AddDescription(kIDTree2Falling0, "Tree2Falling0");
    AddDescription(kIDTree2Falling1, "Tree2Falling1");
    AddDescription(kIDTree2Falling2, "Tree2Falling2");
    AddDescription(kIDPlayerSprite, "Player");
    AddDescription(kIDForradiaStartText0, "ForradiaStartText0");
    AddDescription(kIDForradiaStartText1, "ForradiaStartText1");
    AddDescription(kIDForradiaStartText2, "ForradiaStartText2");
    AddDescription(kIDForradiaStartText3, "ForradiaStartText3");
    AddDescription(kIDForradiaStartText4, "ForradiaStartText4");
    AddDescription(kIDForradiaStartText5, "ForradiaStartText5");
    AddDescription(kIDForradiaStartText6, "ForradiaStartText6");
    AddDescription(kIDForradiaStartText7, "ForradiaStartText7");
    AddDescription(kIDForradiaStartText8, "ForradiaStartText8");
    AddDescription(kIDMenuButtonBackground, "MenuButtonBack");
    AddDescription(kIDMenuButtonBackHovered, "MenuButtonBackHovered");
    AddDescription(kIDTitleStartNewGame, "TitleStartNewGame");
    AddDescription(kIDSkillEffectA, "SkillEffect0");
    AddDescription(kIDSkillEffectB, "SkillEffect1");
    AddDescription(kIDSkillEffectB0, "SkillEffect1_0");
    AddDescription(kIDSkillEffectB1, "SkillEffect1_1");
    AddDescription(kIDSkillEffectB2, "SkillEffect1_2");
    AddDescription(kIDUnseenTile, "UnseenTile");
    AddDescription(kIDWaterDepth0, "WaterDepth0");
    AddDescription(kIDWaterDepth1, "WaterDepth1");
    AddDescription(kIDWaterDepth2, "WaterDepth2");
    AddDescription(kIDEdgeRight, "EdgeRight");
    AddDescription(kIDEdgeTop, "EdgeTop");
    AddDescription(kIDElevLeft, "ElevLeft");
    AddDescription(kIDElevBottom, "ElevBottom");
    AddDescription(kIDElevLeftDark, "ElevLeftDark");
    AddDescription(kIDElevBottomDark, "ElevBottomDark");
    AddDescription(kIDElevLeftRock, "ElevLeftRock");
    AddDescription(kIDElevBottomRock, "ElevBottomRock");
    AddDescription(kIDElevLeftDarkRock, "ElevLeftDarkRock");
    AddDescription(kIDElevBottomDarkRock, "ElevBottomDarkRock");
    AddDescription(kIDEdgeRightRock, "EdgeRightRock");
    AddDescription(kIDEdgeTopRock, "EdgeTopRock");
    AddDescription(kIDElevCorner, "ElevCorner");
    AddDescription(kIDGrassStraws, "GrassStraws");
    AddDescription(kIDCaveEntranceNorth, "CaveEntranceNorth");
    AddDescription(kIDCaveEntranceEast, "CaveEntranceEast");
    AddDescription(kIDCaveEntranceSouth, "CaveEntranceSouth");
    AddDescription(kIDCaveEntranceWest, "CaveEntranceWest");
    AddDescription(kIDTileHoverEffect, "TileHoverEffect");
    AddDescription(kIDTrainLocomotive0, "TrainLocomotive0");
    AddDescription(kIDTrainLocomotive1, "TrainLocomotive1");
    AddDescription(kIDTrainLocomotive2, "TrainLocomotive2");
    AddDescription(kIDTrainCarriage, "TrainCarriage");
    AddDescription(kIDIconCloseWindow, "IconCloseWindow");
    AddDescription(kIDOptionIconUnselected, "OptionIconUnselected");
    AddDescription(kIDOptionIconSelected, "OptionIconSelected");
    AddDescription(kIDEffectVanish0, "EffectVanish0");
    AddDescription(kIDEffectVanish1, "EffectVanish1");
    AddDescription(kIDEffectVanish2, "EffectVanish2");
    AddDescription(kIDEffectVanish3, "EffectVanish3");
    AddDescription(kIDEffectVanish4, "EffectVanish4");
    AddDescription(kIDEffectVanish5, "EffectVanish5");
    AddDescription(kIDWindowBackground, "WindowBack");
    AddDescription(kIDInventorySlotBackground, "InventorySlotBack");
    AddDescription(kIDIconActiveFoodItemFrame, "IconActiveFoodItemFrame");

}


int DataLoading::GetDescriptionIndexByName(string name)
{

    if (contentIndicesByName->count(name) > 0)
        return contentIndicesByName->at(name);
    
    return -1;

}

void DataLoading::AddDescription(int id, string name)
{
    auto desc = make_unique<CDataDescription>(CDataDescription());
    desc->m_propAttributes.insert(std::pair<string, string>("Name", name));
    contentIndicesByName->insert(pair<string, int>(name, id));
    libDescriptions[id] = move(desc);
}

void DataLoading::AddDescriptionEx(int id,
                                    string name,
                                    double imgWidthMulti,
                                    double imgHeightMulti,
                                    string imgFocusedObjAnim,
                                    bool isObstacle,
                                    bool movable,
                                    string readableName,
                                    bool randomScaling,
                                    bool ignoreShadow,
                                    int ticksToVanish,
                                    int XOffsetFactor,
                                    int YOffsetFactor,
                                    bool hasAmount,
                                    double foodAmount,
                                    double foodSpeed)
{

    auto desc = make_unique<CDataDescription>(CDataDescription());
    desc->m_propAttributes.insert(std::pair<string, string>("Name", name));
    desc->m_propAttributes.insert(std::pair<string, string>("ImageWidthMultiplier", to_string(imgWidthMulti)));
    desc->m_propAttributes.insert(std::pair<string, string>("ImageHeightMultiplier", to_string(imgHeightMulti)));
    desc->m_propAttributes.insert(std::pair<string, string>("ImageFocusedObjectAnimation", imgFocusedObjAnim));
    desc->m_propAttributes.insert(std::pair<string, string>("IsObstacle", isObstacle ? "true" : "false"));
    desc->m_propAttributes.insert(std::pair<string, string>("Movable", movable ? "true" : "false"));
    desc->m_propAttributes.insert(std::pair<string, string>("ReadableName", readableName));
    desc->m_propAttributes.insert(std::pair<string, string>("RandomScaling", randomScaling ? "true" : "false"));
    desc->m_propAttributes.insert(std::pair<string, string>("IgnoreShadow", ignoreShadow ? "true" : "false"));
    desc->m_propAttributes.insert(std::pair<string, string>("TicksToVanish", to_string(ticksToVanish)));
    desc->m_propAttributes.insert(std::pair<string, string>("XOffsetFactor", to_string(XOffsetFactor)));
    desc->m_propAttributes.insert(std::pair<string, string>("YOffsetFactor", to_string(YOffsetFactor)));
    desc->m_propAttributes.insert(std::pair<string, string>("HasAmount", hasAmount ? "true" : "false"));
    desc->m_propAttributes.insert(std::pair<string, string>("FoodAmount", to_string(foodAmount)));
    desc->m_propAttributes.insert(std::pair<string, string>("FoodSpeed", to_string(foodSpeed)));
    contentIndicesByName->insert(pair<string, int>(name, id));
    libDescriptions[id] = move(desc);

}