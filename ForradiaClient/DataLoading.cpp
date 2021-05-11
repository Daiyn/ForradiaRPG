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

    AddDescription(ImagesIDs::TileGrass, "TileGrass");
    AddDescription(ImagesIDs::TileWater, "TileWater");
    AddDescription(descriptionIndex++, "TileWater0");
    AddDescription(descriptionIndex++, "TileWater1");
    AddDescription(descriptionIndex++, "TileWater2");
    AddDescription(ImagesIDs::TileRock, "TileRock");
    AddDescription(ImagesIDs::TileWoodfloor, "TileWoodfloor");
    AddDescription(ImagesIDs::TileStoneslab, "TileStoneSlab");
    AddDescription(ImagesIDs::TileCavefloor, "TileCaveFloor");
    AddDescription(ImagesIDs::TileSand, "TileSand");
    AddDescription(ImagesIDs::TileClay, "TileClay");



//==========================
//      OBJECTS
//==========================

    AddDescriptionEx(ImagesIDs::ObjectTree1, "ObjectTree1", 6, 6, "tree1Falling", true, false, "Tree", true, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(ImagesIDs::ObjectTree2, "ObjectTree2", 6, 6, "tree2Falling", true, false, "Tree", true, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectFoeDead", 2, 2, "", false, true, "Dead Foe", false, true, 5000, 0, 0, false, 0, 0);
    AddDescriptionEx(ImagesIDs::ObjectBoulder, "ObjectBoulder", 3, 3, "", true, false, "Boulder", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallEW", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallNS", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallCorner", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStairsUp", 1, 1, "", false, false, "Wooden Stairs Up", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStairsDown", 1, 1, "", false, false, "Wooden Stairs Down", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(ImagesIDs::ObjectBush, "ObjectBush", 1, 1, "", true, false, "Bush", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(ImagesIDs::ObjectBushtall, "ObjectBushTall", 1, 2, "", true, false, "Tall Bush", false, true, -1, 0, 0, false, 0, 0);
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


    AddDescription(ImagesIDs::Cursor, "Cursor");
    AddDescription(ImagesIDs::CursorHovering, "CursorHovering");
    AddDescription(ImagesIDs::IconsBackground, "IconsBackground");
    AddDescription(ImagesIDs::IconSystem, "IconSystem");
    AddDescription(ImagesIDs::IconCrafting, "IconCrafting");
    AddDescription(ImagesIDs::IconInventory, "IconInventory");
    AddDescription(ImagesIDs::FullMapFrameBackground, "MapPreviewBack");
    AddDescription(ImagesIDs::TerminalBackground, "TerminalBack");
    AddDescription(ImagesIDs::TileTargetEffect, "TileTargetEffect");
    AddDescription(ImagesIDs::Shadow, "Shadow");
    AddDescription(ImagesIDs::Foe, "Foe");
    AddDescription(ImagesIDs::Butterfly, "Butterfly");
    AddDescription(ImagesIDs::PinkSlime, "PinkSlime");
    AddDescription(ImagesIDs::HitEffect, "HitEffect");
    AddDescription(ImagesIDs::SpawnEffect0, "SpawnEffect0");
    AddDescription(ImagesIDs::SpawnEffect1, "SpawnEffect1");
    AddDescription(ImagesIDs::SpawnEffect2, "SpawnEffect2");
    AddDescription(ImagesIDs::NPCSprite, "NPC");
    AddDescription(ImagesIDs::ChatBubble, "ChatBubble");
    AddDescription(ImagesIDs::Tree1Falling0, "Tree1Falling0");
    AddDescription(ImagesIDs::Tree1Falling1, "Tree1Falling1");
    AddDescription(ImagesIDs::Tree1Falling2, "Tree1Falling2");
    AddDescription(ImagesIDs::Tree2Falling0, "Tree2Falling0");
    AddDescription(ImagesIDs::Tree2Falling1, "Tree2Falling1");
    AddDescription(ImagesIDs::Tree2Falling2, "Tree2Falling2");
    AddDescription(ImagesIDs::PlayerSprite, "Player");
    AddDescription(ImagesIDs::ForradiaStartText0, "ForradiaStartText0");
    AddDescription(ImagesIDs::ForradiaStartText1, "ForradiaStartText1");
    AddDescription(ImagesIDs::ForradiaStartText2, "ForradiaStartText2");
    AddDescription(ImagesIDs::ForradiaStartText3, "ForradiaStartText3");
    AddDescription(ImagesIDs::ForradiaStartText4, "ForradiaStartText4");
    AddDescription(ImagesIDs::ForradiaStartText5, "ForradiaStartText5");
    AddDescription(ImagesIDs::ForradiaStartText6, "ForradiaStartText6");
    AddDescription(ImagesIDs::ForradiaStartText7, "ForradiaStartText7");
    AddDescription(ImagesIDs::ForradiaStartText8, "ForradiaStartText8");
    AddDescription(ImagesIDs::MenuButtonBackground, "MenuButtonBack");
    AddDescription(ImagesIDs::MenuButtonBackHovered, "MenuButtonBackHovered");
    AddDescription(ImagesIDs::TitleStartNewGame, "TitleStartNewGame");
    AddDescription(ImagesIDs::SkillEffectA, "SkillEffect0");
    AddDescription(ImagesIDs::SkillEffectB, "SkillEffect1");
    AddDescription(ImagesIDs::SkillEffectB0, "SkillEffect1_0");
    AddDescription(ImagesIDs::SkillEffectB1, "SkillEffect1_1");
    AddDescription(ImagesIDs::SkillEffectB2, "SkillEffect1_2");
    AddDescription(ImagesIDs::UnseenTile, "UnseenTile");
    AddDescription(ImagesIDs::WaterDepth0, "WaterDepth0");
    AddDescription(ImagesIDs::WaterDepth1, "WaterDepth1");
    AddDescription(ImagesIDs::WaterDepth2, "WaterDepth2");
    AddDescription(ImagesIDs::EdgeRight, "EdgeRight");
    AddDescription(ImagesIDs::EdgeTop, "EdgeTop");
    AddDescription(ImagesIDs::ElevLeft, "ElevLeft");
    AddDescription(ImagesIDs::ElevBottom, "ElevBottom");
    AddDescription(ImagesIDs::ElevLeftDark, "ElevLeftDark");
    AddDescription(ImagesIDs::ElevBottomDark, "ElevBottomDark");
    AddDescription(ImagesIDs::ElevLeftRock, "ElevLeftRock");
    AddDescription(ImagesIDs::ElevBottomRock, "ElevBottomRock");
    AddDescription(ImagesIDs::ElevLeftDarkRock, "ElevLeftDarkRock");
    AddDescription(ImagesIDs::ElevBottomDarkRock, "ElevBottomDarkRock");
    AddDescription(ImagesIDs::EdgeRightRock, "EdgeRightRock");
    AddDescription(ImagesIDs::EdgeTopRock, "EdgeTopRock");
    AddDescription(ImagesIDs::ElevCorner, "ElevCorner");
    AddDescription(ImagesIDs::GrassStraws, "GrassStraws");
    AddDescription(ImagesIDs::CaveEntranceNorth, "CaveEntranceNorth");
    AddDescription(ImagesIDs::CaveEntranceEast, "CaveEntranceEast");
    AddDescription(ImagesIDs::CaveEntranceSouth, "CaveEntranceSouth");
    AddDescription(ImagesIDs::CaveEntranceWest, "CaveEntranceWest");
    AddDescription(ImagesIDs::TileHoverEffect, "TileHoverEffect");
    AddDescription(ImagesIDs::TrainLocomotive0, "TrainLocomotive0");
    AddDescription(ImagesIDs::TrainLocomotive1, "TrainLocomotive1");
    AddDescription(ImagesIDs::TrainLocomotive2, "TrainLocomotive2");
    AddDescription(ImagesIDs::TrainCarriage, "TrainCarriage");
    AddDescription(ImagesIDs::IconCloseWindow, "IconCloseWindow");
    AddDescription(ImagesIDs::OptionIconUnselected, "OptionIconUnselected");
    AddDescription(ImagesIDs::OptionIconSelected, "OptionIconSelected");
    AddDescription(ImagesIDs::EffectVanish0, "EffectVanish0");
    AddDescription(ImagesIDs::EffectVanish1, "EffectVanish1");
    AddDescription(ImagesIDs::EffectVanish2, "EffectVanish2");
    AddDescription(ImagesIDs::EffectVanish3, "EffectVanish3");
    AddDescription(ImagesIDs::EffectVanish4, "EffectVanish4");
    AddDescription(ImagesIDs::EffectVanish5, "EffectVanish5");
    AddDescription(ImagesIDs::WindowBackground, "WindowBack");
    AddDescription(ImagesIDs::InventorySlotBackground, "InventorySlotBack");
    AddDescription(ImagesIDs::IconActiveFoodItemFrame, "IconActiveFoodItemFrame");

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