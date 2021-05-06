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

    AddDescription(ID_TILE_GRASS, "TileGrass");
    AddDescription(ID_TILE_WATER, "TileWater");
    AddDescription(descriptionIndex++, "TileWater0");
    AddDescription(descriptionIndex++, "TileWater1");
    AddDescription(descriptionIndex++, "TileWater2");
    AddDescription(ID_TILE_ROCK, "TileRock");
    AddDescription(ID_TILE_WOODFLOOR, "TileWoodfloor");
    AddDescription(ID_TILE_STONESLAB, "TileStoneSlab");
    AddDescription(ID_TILE_CAVEFLOOR, "TileCaveFloor");
    AddDescription(ID_TILE_SAND, "TileSand");
    AddDescription(ID_TILE_CLAY, "TileClay");



//==========================
//      OBJECTS
//==========================

    AddDescriptionEx(ID_OBJECT_TREE1, "ObjectTree1", 8, 8, "tree1Falling", true, false, "Tree", true, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(ID_OBJECT_TREE2, "ObjectTree2", 8, 8, "tree2Falling", true, false, "Tree", true, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectFoeDead", 2, 2, "", false, true, "Dead Foe", false, true, 5000, 0, 0, false, 0, 0);
    AddDescriptionEx(ID_OBJECT_BOULDER, "ObjectBoulder", 3, 3, "", true, false, "Boulder", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallEW", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallNS", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectWoodWallCorner", 1, 3, "", true, false, "Wood Wall", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStairsUp", 1, 1, "", false, false, "Wooden Stairs Up", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(descriptionIndex++, "ObjectStairsDown", 1, 1, "", false, false, "Wooden Stairs Down", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(ID_OBJECT_BUSH, "ObjectBush", 1, 1, "", true, false, "Bush", false, true, -1, 0, 0, false, 0, 0);
    AddDescriptionEx(ID_OBJECT_BUSHTALL, "ObjectBushTall", 1, 2, "", true, false, "Tall Bush", false, true, -1, 0, 0, false, 0, 0);
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

//==========================
//      ADDITIONAL
//==========================


    AddDescription(ID_CURSOR, "Cursor");
    AddDescription(ID_CURSOR_HOVERING, "CursorHovering");
    AddDescription(ID_ICONS_BACKGROUND, "IconsBackground");
    AddDescription(ID_ICON_SYSTEM, "IconSystem");
    AddDescription(ID_ICON_CRAFTING, "IconCrafting");
    AddDescription(ID_ICON_INVENTORY, "IconInventory");
    AddDescription(ID_MAP_PREVIEW_BACK, "MapPreviewBack");
    AddDescription(ID_TERMINAL_BACK, "TerminalBack");
    AddDescription(ID_TILE_TARGET_EFFECT, "TileTargetEffect");
    AddDescription(ID_SHADOW, "Shadow");
    AddDescription(ID_FOE, "Foe");
    AddDescription(ID_BUTTERFLY, "Butterfly");
    AddDescription(ID_PINKSLIME, "PinkSlime");
    AddDescription(ID_HIT_EFFECT, "HitEffect");
    AddDescription(ID_SPAWN_EFFECT_0, "SpawnEffect0");
    AddDescription(ID_SPAWN_EFFECT_1, "SpawnEffect1");
    AddDescription(ID_SPAWN_EFFECT_2, "SpawnEffect2");
    AddDescription(ID_NPC, "NPC");
    AddDescription(ID_CHAT_BUBBLE, "ChatBubble");
    AddDescription(ID_TREE1_FALLING_0, "Tree1Falling0");
    AddDescription(ID_TREE1_FALLING_1, "Tree1Falling1");
    AddDescription(ID_TREE1_FALLING_2, "Tree1Falling2");
    AddDescription(ID_TREE2_FALLING_0, "Tree2Falling0");
    AddDescription(ID_TREE2_FALLING_1, "Tree2Falling1");
    AddDescription(ID_TREE2_FALLING_2, "Tree2Falling2");
    AddDescription(ID_PLAYER, "Player");
    AddDescription(ID_FORRADIA_START_TEXT_0, "ForradiaStartText0");
    AddDescription(ID_FORRADIA_START_TEXT_1, "ForradiaStartText1");
    AddDescription(ID_FORRADIA_START_TEXT_2, "ForradiaStartText2");
    AddDescription(ID_FORRADIA_START_TEXT_3, "ForradiaStartText3");
    AddDescription(ID_FORRADIA_START_TEXT_4, "ForradiaStartText4");
    AddDescription(ID_FORRADIA_START_TEXT_5, "ForradiaStartText5");
    AddDescription(ID_FORRADIA_START_TEXT_6, "ForradiaStartText6");
    AddDescription(ID_FORRADIA_START_TEXT_7, "ForradiaStartText7");
    AddDescription(ID_FORRADIA_START_TEXT_8, "ForradiaStartText8");
    AddDescription(ID_MENU_BUTTON_BACK, "MenuButtonBack");
    AddDescription(ID_MENU_BUTTON_BACK_HOVERED, "MenuButtonBackHovered");
    AddDescription(ID_TITLE_START_NEW_GAME, "TitleStartNewGame");
    AddDescription(ID_SKILL_EFFECT_0, "SkillEffect0");
    AddDescription(ID_SKILL_EFFECT_1, "SkillEffect1");
    AddDescription(ID_SKILL_EFFECT_1_0, "SkillEffect1_0");
    AddDescription(ID_SKILL_EFFECT_1_1, "SkillEffect1_1");
    AddDescription(ID_SKILL_EFFECT_1_2, "SkillEffect1_2");
    AddDescription(ID_UNSEEN_TILE, "UnseenTile");
    AddDescription(ID_WATER_DEPTH_0, "WaterDepth0");
    AddDescription(ID_WATER_DEPTH_1, "WaterDepth1");
    AddDescription(ID_WATER_DEPTH_2, "WaterDepth2");
    AddDescription(ID_EDGE_RIGHT, "EdgeRight");
    AddDescription(ID_EDGE_TOP, "EdgeTop");
    AddDescription(ID_ELEV_LEFT, "ElevLeft");
    AddDescription(ID_ELEV_BOTTOM, "ElevBottom");
    AddDescription(ID_ELEV_LEFT_DARK, "ElevLeftDark");
    AddDescription(ID_ELEV_BOTTOM_DARK, "ElevBottomDark");
    AddDescription(ID_ELEV_LEFT_ROCK, "ElevLeftRock");
    AddDescription(ID_ELEV_BOTTOM_ROCK, "ElevBottomRock");
    AddDescription(ID_ELEV_LEFT_DARK_ROCK, "ElevLeftDarkRock");
    AddDescription(ID_ELEV_BOTTOM_DARK_ROCK, "ElevBottomDarkRock");
    AddDescription(ID_EDGE_RIGHT_ROCK, "EdgeRightRock");
    AddDescription(ID_EDGE_TOP_ROCK, "EdgeTopRock");
    AddDescription(ID_ELEV_CORNER, "ElevCorner");
    AddDescription(ID_GRASS_STRAWS, "GrassStraws");
    AddDescription(ID_CAVE_ENTRANCE_NORTH, "CaveEntranceNorth");
    AddDescription(ID_CAVE_ENTRANCE_EAST, "CaveEntranceEast");
    AddDescription(ID_CAVE_ENTRANCE_SOUTH, "CaveEntranceSouth");
    AddDescription(ID_CAVE_ENTRANCE_WEST, "CaveEntranceWest");
    AddDescription(ID_TILE_HOVER_EFFECT, "TileHoverEffect");
    AddDescription(ID_TRAIN_LOCOMOTIVE_0, "TrainLocomotive0");
    AddDescription(ID_TRAIN_LOCOMOTIVE_1, "TrainLocomotive1");
    AddDescription(ID_TRAIN_LOCOMOTIVE_2, "TrainLocomotive2");
    AddDescription(ID_TRAIN_CARRIAGE, "TrainCarriage");
    AddDescription(ID_ICON_CLOSE_WINDOW, "IconCloseWindow");
    AddDescription(ID_OPTION_ICON_UNSELECTED, "OptionIconUnselected");
    AddDescription(ID_OPTION_ICON_SELECTED, "OptionIconSelected");
    AddDescription(ID_EFFECT_VANISH_0, "EffectVanish0");
    AddDescription(ID_EFFECT_VANISH_1, "EffectVanish1");
    AddDescription(ID_EFFECT_VANISH_2, "EffectVanish2");
    AddDescription(ID_EFFECT_VANISH_3, "EffectVanish3");
    AddDescription(ID_EFFECT_VANISH_4, "EffectVanish4");
    AddDescription(ID_EFFECT_VANISH_5, "EffectVanish5");
    AddDescription(ID_WINDOW_BACK, "WindowBack");
    AddDescription(ID_INVENTORY_SLOT_BACK, "InventorySlotBack");
    AddDescription(ID_ICON_ACTIVE_FOOD_ITEM_FRAME, "IconActiveFoodItemFrame");

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