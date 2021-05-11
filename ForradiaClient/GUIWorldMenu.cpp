#include "GUIWorldMenu.h"
#include "PlayerActions.h"
#include "TextRendering.h"
#include "DataLoading.h"
#include <SDL2/SDL_timer.h>
#include "Global_CurrentMap.h"
#include "Global_Player.h"
#include "Global_SDL.h"
#include "Global_Canvas.h"
#include "Global_Mouse.h"
#include "Drawing.h"
#include "Colors.h"
#include "Mining.h"
#include "Crafting.h"
#include "CMap.h"
#include "CPlayer.h"
#include "FoodEating.h"

bool GUIWorldMenu::HandleLeftMouseClickInWorld() {

    if (!stateIsShown)
        return false;

    stateIsShown = false;

    CPoint pMouse = Global::GetMousePoint();

    for (int i = 0; i < stateShownMenuOptions.size(); i++)
    {

        int xRow = pxMenuX + pxMargin;
        int yRow = pxMenuY + pxMargin + i * pxRowHeight;

        CRectangle rect = { xRow, yRow, pxMenuWidth, pxRowHeight };

        if (rect.ContainsPoint(pMouse))
        {

            if (stateShownMenuOptions[i] == MENU_ID_CHOP_DOWN_TREE)
                Crafting::ChopDownTree(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_UNLOADED_CAMPFIRE)
                Crafting::CreateUnloadedCampfire(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_LOAD_CAMPFIRE)
                Crafting::LoadCampfire(coordClickedTile);


            if (stateShownMenuOptions[i] == MENU_ID_CHOP_UP_WOOD_LOG)
                Crafting::ChopUpWoodLog(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_MINE_CAVE)
                Mining::MineTile(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_LIGHT_CAMPFIRE)
                Crafting::LightCampfire(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_DIG_CLAY)
                Crafting::DigClay(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_BRICK)
                Crafting::CreateBrick(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_MELTING_FURNACE)
                Crafting::CreateMeltingFurnace(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_EAT_APPLE)
                FoodEating::EatAppleFromGround(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_WOODPLANK)
                Crafting::CreateWoodplank(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_WOODFLOOR)
                Crafting::CreateWoodfloor(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_LOAD_MELTING_FURNACE)
                Crafting::LoadMeltingFurnace(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_LIGHT_MELTING_FURNACE)
                Crafting::LightMeltingFurnace(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_HEAT_IRON)
                Crafting::HeatIron(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_IRON_NAIL)
                Crafting::CreateIronNail(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_DIG_GROUND)
                Crafting::DigGround(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_WOODWALL_NS)
                Crafting::CreateWoodWallNS(coordClickedTile);

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_WOODWALL_EW)
            {
                Crafting::CreateWoodWallEW(coordClickedTile);
                break;
            }

            if (stateShownMenuOptions[i] == MENU_ID_CREATE_WOODWALL_CORNER)
                Crafting::CreateWoodWallCorner(coordClickedTile);

        }
    }

    return true;
}

void GUIWorldMenu::HandleRightMouseClickInWorld() {

    int groundTypeRock = DataLoading::GetDescriptionIndexByName("TileRock");
    int groundTypeClay = DataLoading::GetDescriptionIndexByName("TileClay");
    int objectTree1 = DataLoading::GetDescriptionIndexByName("ObjectTree1");
    int objectTree2 = DataLoading::GetDescriptionIndexByName("ObjectTree2");
    int objectUnloadedCampfire = DataLoading::GetDescriptionIndexByName("ObjectUnloadedCampfire");
    int objectStone = DataLoading::GetDescriptionIndexByName("ObjectStone");
    int objectFelledTree = DataLoading::GetDescriptionIndexByName("ObjectFelledTree");
    int objectWoodLog = DataLoading::GetDescriptionIndexByName("ObjectWoodLog");
    int objectMatches = DataLoading::GetDescriptionIndexByName("ObjectMatches");
    int objectLoadedCampfire = DataLoading::GetDescriptionIndexByName("ObjectLoadedCampfire");
    int objectShovel = DataLoading::GetDescriptionIndexByName("ObjectShovel");
    int objectClayLump = DataLoading::GetDescriptionIndexByName("ObjectClayLump");
    int objectBurningCampfire = DataLoading::GetDescriptionIndexByName("ObjectBurningCampfire");
    int objectBrick = DataLoading::GetDescriptionIndexByName("ObjectBrick");
    int objectApple = DataLoading::GetDescriptionIndexByName("ObjectApple");
    int objectSaw = DataLoading::GetDescriptionIndexByName("ObjectSaw");
    int objectWoodplank = DataLoading::GetDescriptionIndexByName("ObjectWoodPlank");
    int objectUnloadedMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectUnloadedMeltingFurnace");
    int objectLoadedMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectLoadedMeltingFurnace");
    int objectHotMeltingFurnace = DataLoading::GetDescriptionIndexByName("ObjectHotMeltingFurnace");
    int objectCoal = DataLoading::GetDescriptionIndexByName("ObjectCoal");
    int objectIronOre = DataLoading::GetDescriptionIndexByName("ObjectIronOre");
    int objectSmallAnvil = DataLoading::GetDescriptionIndexByName("ObjectSmallAnvil");
    int objectHotIronLump = DataLoading::GetDescriptionIndexByName("ObjectHotIronLump");
    int objectStoneHammer = DataLoading::GetDescriptionIndexByName("ObjectStoneHammer");
    int objectIronNail = DataLoading::GetDescriptionIndexByName("ObjectIronNail");

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    pxMenuX = mx + Global::GetTileSize();
    pxMenuY = my - Global::GetTileSize()/2;

    stateShownMenuOptions.clear();

    coordClickedTile = { PlayerActions::coordHoveredTile.m_x , PlayerActions::coordHoveredTile.m_y};

    if (Global::contentCurrentMap->TileHoldsObjectOfType(objectTree1, coordClickedTile.m_x, coordClickedTile.m_y, SURFACE_FLOOR)
        || Global::contentCurrentMap->TileHoldsObjectOfType(objectTree2, coordClickedTile.m_x, coordClickedTile.m_y, SURFACE_FLOOR))
        stateShownMenuOptions.push_back(MENU_ID_CHOP_DOWN_TREE);

    if (Global::contentCurrentMap->TileHoldsObjectOfType(objectFelledTree, coordClickedTile.m_x, coordClickedTile.m_y, SURFACE_FLOOR))
        stateShownMenuOptions.push_back(MENU_ID_CHOP_UP_WOOD_LOG);

    if (Global::contentCurrentMap->TileHoldsObjectOfTypeAndQuantity(objectStone, 5, coordClickedTile.m_x, coordClickedTile.m_y, SURFACE_FLOOR))
        stateShownMenuOptions.push_back(MENU_ID_CREATE_UNLOADED_CAMPFIRE);


    if (Global::contentCurrentMap->TileHoldsObjectOfType(objectUnloadedCampfire, coordClickedTile.m_x, coordClickedTile.m_y, SURFACE_FLOOR)
        && Global::statePlayer->m_inventory.HasItemInInventory(objectWoodLog))
        stateShownMenuOptions.push_back(MENU_ID_LOAD_CAMPFIRE);


    if (Global::contentCurrentMap->TileHoldsObjectOfType(objectLoadedCampfire, coordClickedTile.m_x, coordClickedTile.m_y, SURFACE_FLOOR)
        && Global::statePlayer->m_inventory.HasItemInInventory(objectMatches))
        stateShownMenuOptions.push_back(MENU_ID_LIGHT_CAMPFIRE);


    if (Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == groundTypeClay
        && Global::statePlayer->m_inventory.HasItemInInventory(objectShovel))
        stateShownMenuOptions.push_back(MENU_ID_DIG_CLAY);


    if (Global::contentCurrentMap->TileHoldsObjectOfType(objectBurningCampfire, coordClickedTile.m_x, coordClickedTile.m_y, SURFACE_FLOOR)
        && Global::statePlayer->m_inventory.HasItemInInventory(objectClayLump))
        stateShownMenuOptions.push_back(MENU_ID_CREATE_BRICK);

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex != -1)
    {

        CTileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_floorsArray[seenFloorIndex];

        if (floor.HoldsObjectOfTypeAndQuantity(objectBrick, Crafting::MELTING_FURNACE_NUM_REQ_BRICKS))
            stateShownMenuOptions.push_back(MENU_ID_CREATE_MELTING_FURNACE);

        if (floor.HoldsObjectOfTypeAndQuantity(objectApple, 1))
            stateShownMenuOptions.push_back(MENU_ID_EAT_APPLE);

        if (floor.HoldsObjectOfTypeAndQuantity(objectWoodLog, 1)
            && Global::statePlayer->m_inventory.HasItemInInventory(objectSaw))
            stateShownMenuOptions.push_back(MENU_ID_CREATE_WOODPLANK);

        if (floor.m_idxGroundType != ImagesIDs::TileWater
            && Global::statePlayer->m_inventory.HasItemInInventory(objectWoodplank))
            stateShownMenuOptions.push_back(MENU_ID_CREATE_WOODFLOOR);

        if (floor.HoldsObjectOfType(objectUnloadedMeltingFurnace)
            && Global::statePlayer->m_inventory.HasItemInInventory(objectCoal))
            stateShownMenuOptions.push_back(MENU_ID_LOAD_MELTING_FURNACE);

        if (floor.HoldsObjectOfType(objectLoadedMeltingFurnace)
            && Global::statePlayer->m_inventory.HasItemInInventory(objectMatches))
            stateShownMenuOptions.push_back(MENU_ID_LIGHT_MELTING_FURNACE);

        if (floor.HoldsObjectOfType(objectHotMeltingFurnace)
            && Global::statePlayer->m_inventory.HasItemInInventory(objectIronOre))
            stateShownMenuOptions.push_back(MENU_ID_HEAT_IRON);

        if (floor.HoldsObjectOfType(objectSmallAnvil)
            && Global::statePlayer->m_inventory.HasItemInInventory(objectHotIronLump))
            stateShownMenuOptions.push_back(MENU_ID_CREATE_IRON_NAIL);

        if (!floor.HoldsObjects()
            && Global::statePlayer->m_inventory.HasItemInInventory(objectShovel))
            stateShownMenuOptions.push_back(MENU_ID_DIG_GROUND);

        if (floor.HoldsObjectOfType(objectWoodplank))
            if (Global::statePlayer->m_inventory.HasItemInInventory(objectStoneHammer))
                if (Global::statePlayer->m_inventory.HasItemInInventory(objectIronNail))
                {
                    stateShownMenuOptions.push_back(MENU_ID_CREATE_WOODWALL_NS);
                    stateShownMenuOptions.push_back(MENU_ID_CREATE_WOODWALL_EW);
                    stateShownMenuOptions.push_back(MENU_ID_CREATE_WOODWALL_CORNER);
                }


    }

    int dist = std::max(abs(coordClickedTile.m_x - Global::statePlayer->m_coordPosition.m_x), abs(coordClickedTile.m_y - Global::statePlayer->m_coordPosition.m_y));

    bool slopeUpEast = Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x + 1][coordClickedTile.m_y]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_elevationHeight;
    bool slopeUpNorth = Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y - 1]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_elevationHeight;
    bool slopeUpWest = Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x + 1][coordClickedTile.m_y]->m_elevationHeight;
    bool slopeUpSouth = Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_elevationHeight > Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y - 1]->m_elevationHeight;

    bool cliffWallClicked = slopeUpEast || slopeUpNorth || slopeUpWest || slopeUpSouth;
    bool clickedRock = Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == groundTypeRock;
    bool oneTileDistanceFrom = dist <= 1;
    bool playerIsUnderground = Global::statePlayer->m_locCurrentElevation != SURFACE_FLOOR;
    bool clickedTileElevationAbovePlayer = Global::contentCurrentMap->m_tilesGrid[coordClickedTile.m_x][coordClickedTile.m_y]->m_elevationHeight > Global::statePlayer->m_locCurrentElevation;
    bool isNotAlreadyMined = !Global::contentCurrentMap->TileIsMinedAtElev(Global::statePlayer->m_locCurrentElevation, coordClickedTile.m_x, coordClickedTile.m_y);

    if (clickedRock && oneTileDistanceFrom)
        if (cliffWallClicked || (playerIsUnderground && clickedTileElevationAbovePlayer && isNotAlreadyMined))
            stateShownMenuOptions.push_back(MENU_ID_MINE_CAVE);

    if (stateShownMenuOptions.size() == 0)
        stateShownMenuOptions.push_back(MENU_ID_NONE);

    stateIsShown = true;
}

void GUIWorldMenu::Update()
{
    CPoint pMouse = Global::GetMousePoint();

    for (int i = 0; i < stateShownMenuOptions.size(); i++)
    {

        int xRow = pxMenuX + pxMargin;
        int yRow = pxMenuY + pxMargin + i * pxRowHeight;

        CRectangle rect = { pxMenuX, yRow, pxMenuWidth, pxRowHeight };


    }
}

void GUIWorldMenu::Render()
{

    if (!stateIsShown)
        return;

    CPoint pMouse = Global::GetMousePoint();

    for (int i = 0; i < stateShownMenuOptions.size(); i++)
    {

        int xRow = pxMenuX + pxMargin;
        int yRow = pxMenuY + pxMargin + i * pxRowHeight;

        CRectangle rect = { pxMenuX, yRow, pxMenuWidth, pxRowHeight };

        if (rect.ContainsPoint(pMouse))
            Drawing::FilledRect(WORLDMENU_HOVERED, rect);
        else
            Drawing::FilledRect(WORLDMENU_BACKGROUND, rect);

        TextRendering::DrawString(contentAvailableMenuOptions.at(stateShownMenuOptions[i]), {0, 0, 0, 255}, xRow, yRow);

    }

}

