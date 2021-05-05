#include "TileRendering.h"
#include "ImageLoading.h"
#include "PlayerActions.h"
#include "Drawing.h"
#include "Utilities.h"
#include "DataLoading.h"
#include "Global_CurrentMap.h"
#include "Global_Player.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Global_MapSize.h"
#include "CPlayer.h"
#include "TextRendering.h"
#include "Animations.h"

namespace D = Drawing;

using Global::contentCurrentMap;

bool TileRendering::CheckUnseenTiles(int x, int y, CPoint pTile)
{

    auto TILESIZE = Global::GetTileSize();
    auto& PLAYER = Global::statePlayer;

    if (contentCurrentMap->TileIsMinedAtElev(PLAYER->m_locCurrentElevation, pTile.m_x, pTile.m_y))
        return false;

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && pTile.m_x < Global::tilesMapSize - 1
        && contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight)
    {
        return false;
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && pTile.m_y > 0
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight)
    {
        return false;
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && pTile.m_x < Global::tilesMapSize - 1
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight)
    {
        return false;
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && pTile.m_y > 0
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight)
    {
        return false;
    }
    
    if (contentCurrentMap->m_tilesGrid[PLAYER->m_coordPosition.m_x][PLAYER->m_coordPosition.m_y]->m_elevationHeight < 0
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight <= 0)
        return false;

    if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[PLAYER->m_coordPosition.m_x][PLAYER->m_coordPosition.m_y]->m_elevationHeight)
    {


        return true;
    }

    return false;

}

void TileRendering::CoverUnseenTiles(int x, int y, CPoint pTile)
{

    auto TILESIZE = Global::GetTileSize();
    auto& PLAYER = Global::statePlayer;

    if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[PLAYER->m_coordPosition.m_x][PLAYER->m_coordPosition.m_y]->m_elevationHeight) {

        int increasedSize = TILESIZE*1.7;

        D::Image(ID_UNSEEN_TILE,
            x * TILESIZE + TILESIZE / 2 - increasedSize / 2,
            y * TILESIZE + TILESIZE / 2 - increasedSize / 2,
            increasedSize,
            increasedSize);


        return;
    }

}

void TileRendering::RenderTileGround(double tileSize, int x, int y, CPoint pTile)
{

    int tileSizeCeil = ceil(tileSize);
    auto TILESIZE = tileSizeCeil;
    auto& PLAYER = Global::statePlayer;

    int floorIndex = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->GetIndexForSeenFloor();

    if (floorIndex == -1)
        return;

    auto& tfSeenFloor = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[floorIndex];



    int destX = x * tileSize;
    int destY = y * tileSize;
    int destW = TILESIZE;
    int destH = TILESIZE;

    Drawing::RectPrepare(destX, destY, destW, destH);

    if (PLAYER != NULL)
    {
        if (PLAYER->m_locCurrentElevation != SURFACE_FLOOR)
        {

            if (!contentCurrentMap->TileIsMinedAtElev(PLAYER->m_locCurrentElevation, pTile.m_x, pTile.m_y))
            {
                return;
            }

        }
    }

    int numFrames;
    int animSpeed;
    int animIndex = 0;
    string imageName;
    string imageNameWaterDepth;

    CDataDescription& desc = *DataLoading::libDescriptions[tfSeenFloor->m_idxGroundType];


    //D::ImageCurrentRect(tfSeenFloor->m_idxGroundType);

    D::ImageCurrentRect(Animations::RunThroughAnimationFilter(tfSeenFloor->m_idxGroundType, pTile.m_x, pTile.m_y));



    bool tileCurrentIsWater = false;
    bool tileEastIsWater = false;
    bool tileNorthIsWater = false;

    bool isDeepWater = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight < 0;

    tileCurrentIsWater = tfSeenFloor->m_idxGroundType == ID_TILE_WATER;

    if (contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->GetIndexForSeenFloor() != -1)
        tileEastIsWater = tfSeenFloor->m_idxGroundType == ID_TILE_WATER;

    if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->GetIndexForSeenFloor() != -1)
        tileNorthIsWater = tfSeenFloor->m_idxGroundType == ID_TILE_WATER;

    if (!tileCurrentIsWater && tileEastIsWater && !isDeepWater)
        D::ImageCurrentRect(ID_EDGE_RIGHT);

    if (tileCurrentIsWater && !tileEastIsWater && !isDeepWater)
        D::ImageCurrentRect(ID_EDGE_RIGHT);

    if (!tileCurrentIsWater && tileNorthIsWater && !isDeepWater)
        D::ImageCurrentRect(ID_EDGE_TOP);

    if (tileCurrentIsWater && !tileNorthIsWater && !isDeepWater)
        D::ImageCurrentRect(ID_EDGE_TOP);

    bool doDrawGrassStraws = true;

    bool tileIsRock = tfSeenFloor->m_idxGroundType == ID_TILE_ROCK;
    bool tileIsStoneSlab = tfSeenFloor->m_idxGroundType == ID_TILE_STONESLAB;

    int elevCurrent = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight;
    int elevNorth = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight;
    int elevNorthEast = contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y - 1]->m_elevationHeight;
    int elevEast = contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight;
    int elevSouth = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y + 1]->m_elevationHeight;
    int elevSouthEast = contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y + 1]->m_elevationHeight;
    int elevWest = contentCurrentMap->m_tilesGrid[pTile.m_x - 1][pTile.m_y]->m_elevationHeight;

    bool slopeUpNorth = elevNorth > elevCurrent;
    bool slopeUpNorthEast = elevNorthEast > elevCurrent;
    bool slopeUpEast = elevEast > elevCurrent;
    bool slopeUpSouth = elevSouth > elevCurrent;
    bool slopeUpSouthEast = elevSouthEast > elevCurrent;

    bool slopeDownNorth = elevNorth < elevCurrent;
    bool slopeDownEast = elevEast < elevCurrent;

    int drawElevLeft = 1 << 0;
    int drawElevBottom = 1 << 1;
    int drawElevLeftDark = 1 << 2;
    int drawElevBottomDark = 1 << 3;
    int drawEdgeRight = 1 << 5;
    int drawEdgeTop = 1 << 6;

    int drawElevCorner = 1 << 7;

    int drawRock = 1 << 8;

    int drawElevFlags = 0;

    if (slopeUpNorthEast)
    {

        if (slopeUpSouth && slopeUpSouthEast)
            drawElevFlags |= drawElevBottomDark | drawEdgeRight;
        else {
            drawElevFlags |= drawElevBottomDark | drawElevLeft;

            if ((elevEast == elevCurrent && elevNorth == elevCurrent)
                || (elevWest == elevCurrent
                    && elevSouth == elevCurrent
                    && slopeUpNorth
                    && slopeUpEast))
                drawElevFlags |= drawElevCorner;
        }

    }

    if (slopeUpNorth)
        drawElevFlags |= drawElevLeftDark;

    if (slopeUpEast)
    {

        if (slopeUpSouth || slopeUpEast)
        {

            if (slopeUpNorthEast)
                drawElevFlags |= drawElevLeft | drawElevBottomDark | drawEdgeRight;
            else
                drawElevFlags |= drawElevBottomDark | drawEdgeRight;
        }
        else
        {

            drawElevFlags |= drawElevLeft;

        }

    }


    if (slopeDownNorth)
        drawElevFlags |= drawEdgeTop;

    if (slopeDownEast)
        drawElevFlags |= drawEdgeRight;

    if (tileIsRock || tileIsStoneSlab)
        drawElevFlags |= drawRock;

    if (drawElevFlags != 0)
        doDrawGrassStraws = false;

    if (drawElevFlags != 0)
    {
    
        if ((drawElevFlags & drawRock) == 0)
        {

        if ((drawElevFlags & drawElevLeft) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ID_ELEV_LEFT);

        if ((drawElevFlags & drawElevBottom) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ID_ELEV_BOTTOM);

        if ((drawElevFlags & drawElevLeftDark) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ID_ELEV_LEFT_DARK);

        if ((drawElevFlags & drawElevBottomDark) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ID_ELEV_BOTTOM_DARK);

        if ((drawElevFlags & drawEdgeRight) != 0 && !isDeepWater)
            D::ImageCurrentRect(ID_EDGE_RIGHT);

        if ((drawElevFlags & drawEdgeTop) != 0 && !isDeepWater)
            D::ImageCurrentRect(ID_EDGE_TOP);

        }
        else
        {

            if ((drawElevFlags & drawElevLeft) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ID_ELEV_LEFT_ROCK);

            if ((drawElevFlags & drawElevBottom) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ID_ELEV_BOTTOM_ROCK);

            if ((drawElevFlags & drawElevLeftDark) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ID_ELEV_LEFT_DARK_ROCK);

            if ((drawElevFlags & drawElevBottomDark) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ID_ELEV_BOTTOM_DARK_ROCK);

            if ((drawElevFlags & drawEdgeRight) != 0)
                D::ImageCurrentRect(ID_EDGE_RIGHT_ROCK);

            if ((drawElevFlags & drawEdgeTop) != 0)
                D::ImageCurrentRect(ID_EDGE_TOP_ROCK);

        }

        if ((drawElevFlags & drawElevCorner) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ID_ELEV_CORNER);

    }


    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight)
    {
        D::ImageCurrentRect(ID_CAVE_ENTRANCE_WEST);
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight)
    {
        D::ImageCurrentRect(ID_CAVE_ENTRANCE_SOUTH);
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight)
    {
        D::ImageCurrentRect(ID_CAVE_ENTRANCE_EAST);
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight)
    {
        D::ImageCurrentRect(ID_CAVE_ENTRANCE_NORTH);
    }

    int tileFloorGroundType = tfSeenFloor->m_idxGroundType;

    srand(pTile.m_x * 100 + pTile.m_y * 100);
    float scale = (float)(rand() % 10) / 10.0f + 0.5f;

    int destWScaled = (int)(destW * scale*0.8);
    int destHScaled = (int)(destH * scale * 0.8);
    int destXScaled = destX + TILESIZE / 2 - (int)(destWScaled / 2);
    int destYScaled = destY + TILESIZE - (int)(destHScaled);

    Drawing::RectPrepare(destXScaled, destYScaled, destWScaled, destHScaled);

    if (doDrawGrassStraws && tileFloorGroundType == ID_TILE_GRASS)
    {

        int grassStrawsAmount = (pTile.m_x + pTile.m_y + pTile.m_x * pTile.m_y) % 6;

        for (int i = 0; i < grassStrawsAmount; i++)
            D::ImageCurrentRect(ID_GRASS_STRAWS);

    }

}

void TileRendering::RenderTileHoveringEffect(int x, int y, CPoint pTile)
{

    SDL_Rect rTile = { x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(), Global::GetTileSize() };

    if (pTile.m_x == PlayerActions::coordHoveredTile.m_x && pTile.m_y == PlayerActions::coordHoveredTile.m_y)
    {

        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_TILE_HOVER_EFFECT], NULL, &rTile);

    }

}