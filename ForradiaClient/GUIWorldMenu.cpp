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
#include "Cursor.h"
#include "Crafting.h"
#include "CMap.h"
#include "CPlayer.h"
#include "FoodEating.h"

bool GUIWorldMenu::HandleLeftMouseClickInWorld() {

    if (!isShown)
        return false;

    isShown = false;

    CPoint pMouse = Global::GetMousePoint();

    for (int i = 0; i < shownMenuOptions.size(); i++)
    {

        int xRow = menuX + margin;
        int yRow = menuY + margin + i * rowHeight;

        CRectangle rect = { xRow, yRow, menuW, menuH };

        if (rect.ContainsPoint(pMouse))
        {

            if (shownMenuOptions[i] == MENU_ID_CHOP_DOWN_TREE)
                Crafting::ChopDownTree(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_CREATE_UNLOADED_CAMPFIRE)
                Crafting::CreateUnloadedCampfire(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_LOAD_CAMPFIRE)
                Crafting::LoadCampfire(clickedTile);


            if (shownMenuOptions[i] == MENU_ID_CHOP_UP_WOOD_LOG)
                Crafting::ChopUpWoodLog(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_MINE_CAVE)
                Mining::MineTile(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_LIGHT_CAMPFIRE)
                Crafting::LightCampfire(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_DIG_CLAY)
                Crafting::DigClay(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_CREATE_BRICK)
                Crafting::CreateBrick(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_CREATE_MELTING_FURNACE)
                Crafting::CreateMeltingFurnace(clickedTile);

            if (shownMenuOptions[i] == MENU_ID_EAT_APPLE)
                FoodEating::EatAppleFromGround(clickedTile);

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

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    menuX = mx + Global::GetTileSize();
    menuY = my - Global::GetTileSize()/2;

    shownMenuOptions.clear();

    clickedTile = { PlayerActions::hoveredTile.m_x , PlayerActions::hoveredTile.m_y};

    if (Global::currentMap->TileHoldsObjectOfType(objectTree1, clickedTile.m_x, clickedTile.m_y, SURFACE_FLOOR)
        || Global::currentMap->TileHoldsObjectOfType(objectTree2, clickedTile.m_x, clickedTile.m_y, SURFACE_FLOOR))
        shownMenuOptions.push_back(MENU_ID_CHOP_DOWN_TREE);

    if (Global::currentMap->TileHoldsObjectOfType(objectFelledTree, clickedTile.m_x, clickedTile.m_y, SURFACE_FLOOR))
        shownMenuOptions.push_back(MENU_ID_CHOP_UP_WOOD_LOG);

    if (Global::currentMap->TileHoldsObjectOfTypeAndQuantity(objectStone, 5, clickedTile.m_x, clickedTile.m_y, SURFACE_FLOOR))
        shownMenuOptions.push_back(MENU_ID_CREATE_UNLOADED_CAMPFIRE);


    if (Global::currentMap->TileHoldsObjectOfType(objectUnloadedCampfire, clickedTile.m_x, clickedTile.m_y, SURFACE_FLOOR)
        && Global::player->m_inventory.HasItemInInventory(objectWoodLog))
        shownMenuOptions.push_back(MENU_ID_LOAD_CAMPFIRE);


    if (Global::currentMap->TileHoldsObjectOfType(objectLoadedCampfire, clickedTile.m_x, clickedTile.m_y, SURFACE_FLOOR)
        && Global::player->m_inventory.HasItemInInventory(objectMatches))
        shownMenuOptions.push_back(MENU_ID_LIGHT_CAMPFIRE);


    if (Global::currentMap->m_2DTiles[clickedTile.m_x][clickedTile.m_y]->m_floorsArray[SURFACE_FLOOR]->m_groundType == groundTypeClay
        && Global::player->m_inventory.HasItemInInventory(objectShovel))
        shownMenuOptions.push_back(MENU_ID_DIG_CLAY);


    if (Global::currentMap->TileHoldsObjectOfType(objectBurningCampfire, clickedTile.m_x, clickedTile.m_y, SURFACE_FLOOR)
        && Global::player->m_inventory.HasItemInInventory(objectClayLump))
        shownMenuOptions.push_back(MENU_ID_CREATE_BRICK);

    int seenFloorIndex = Global::currentMap->m_2DTiles[clickedTile.m_x][clickedTile.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex != -1)
    {

        CTileFloor& floor = *Global::currentMap->m_2DTiles[clickedTile.m_x][clickedTile.m_y]->m_floorsArray[seenFloorIndex];

        if (floor.HoldsObjectOfTypeAndQuantity(objectBrick, Crafting::MELTING_FURNACE_NUM_REQ_BRICKS))
            shownMenuOptions.push_back(MENU_ID_CREATE_MELTING_FURNACE);

        if (floor.HoldsObjectOfTypeAndQuantity(objectApple, 1))
            shownMenuOptions.push_back(MENU_ID_EAT_APPLE);

    }

    int dist = std::max(abs(clickedTile.m_x - Global::player->m_posCurrent.m_x), abs(clickedTile.m_y - Global::player->m_posCurrent.m_y));

    bool slopeUpEast = Global::currentMap->m_2DElevation[clickedTile.m_x + 1][clickedTile.m_y] > Global::currentMap->m_2DElevation[clickedTile.m_x][clickedTile.m_y];
    bool slopeUpNorth = Global::currentMap->m_2DElevation[clickedTile.m_x][clickedTile.m_y - 1] > Global::currentMap->m_2DElevation[clickedTile.m_x][clickedTile.m_y];
    bool slopeUpWest = Global::currentMap->m_2DElevation[clickedTile.m_x][clickedTile.m_y] > Global::currentMap->m_2DElevation[clickedTile.m_x + 1][clickedTile.m_y];
    bool slopeUpSouth = Global::currentMap->m_2DElevation[clickedTile.m_x][clickedTile.m_y] > Global::currentMap->m_2DElevation[clickedTile.m_x][clickedTile.m_y - 1];

    bool cliffWallClicked = slopeUpEast || slopeUpNorth || slopeUpWest || slopeUpSouth;
    bool clickedRock = Global::currentMap->m_2DTiles[clickedTile.m_x][clickedTile.m_y]->m_floorsArray[SURFACE_FLOOR]->m_groundType == groundTypeRock;
    bool oneTileDistanceFrom = dist <= 1;
    bool playerIsUnderground = Global::player->m_elevCurrent != SURFACE_FLOOR;
    bool clickedTileElevationAbovePlayer = Global::currentMap->m_2DElevation[clickedTile.m_x][clickedTile.m_y] > Global::player->m_elevCurrent;
    bool isNotAlreadyMined = !Global::currentMap->TileIsMinedAtElev(Global::player->m_elevCurrent, clickedTile.m_x, clickedTile.m_y);

    if (clickedRock && oneTileDistanceFrom)
        if (cliffWallClicked || (playerIsUnderground && clickedTileElevationAbovePlayer && isNotAlreadyMined))
            shownMenuOptions.push_back(MENU_ID_MINE_CAVE);

    if (shownMenuOptions.size() == 0)
        shownMenuOptions.push_back(MENU_ID_NONE);

    isShown = true;
}

void GUIWorldMenu::Update()
{
    CPoint pMouse = Global::GetMousePoint();

    for (int i = 0; i < shownMenuOptions.size(); i++)
    {

        int xRow = menuX + margin;
        int yRow = menuY + margin + i * rowHeight;

        CRectangle rect = { menuX, yRow, menuW, rowHeight };

        if (rect.ContainsPoint(pMouse))
            Cursor::isHoveringButton = true;

    }
}

void GUIWorldMenu::Render()
{

    if (!isShown)
        return;

    CPoint pMouse = Global::GetMousePoint();

    for (int i = 0; i < shownMenuOptions.size(); i++)
    {

        int xRow = menuX + margin;
        int yRow = menuY + margin + i * rowHeight;

        CRectangle rect = { menuX, yRow, menuW, rowHeight };

        if (rect.ContainsPoint(pMouse))
            Drawing::FilledRect(WORLDMENU_HOVERED, rect);
        else
            Drawing::FilledRect(WORLDMENU_BACKGROUND, rect);

        TextRendering::DrawString(allMenuOptions.at(shownMenuOptions[i]), {0, 0, 0, 255}, xRow, yRow);

    }

}

