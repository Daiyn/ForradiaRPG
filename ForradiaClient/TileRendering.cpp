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
#include "Player.h"
#include "TextRendering.h"
#include "Animations.h"
#include <math.h>

namespace D = Drawing;

using Global::contentCurrentMap;
using std::max;

bool TileRendering::CheckUnseenTiles(int x, int y, Point pTile)
{

    auto TILESIZE = Global::GetTileSize();
    auto& PLAYER = Global::statePlayer;



    double dx = Global::statePlayer->m_coordPosition.m_x - pTile.m_x;
    double dy = Global::statePlayer->m_coordPosition.m_y - pTile.m_y;

    double dmaxabs = max(abs(dx), abs(dy));

    if (dmaxabs > 0)
    {
        double dxstep = dx / dmaxabs;
        double dystep = dy / dmaxabs;

        for (int i = 1; i < dmaxabs; i++)
        {
            int xx = pTile.m_x + i * dxstep;
            int yy = pTile.m_y + i * dystep;

            int seenFloor = Global::contentCurrentMap->m_tilesGrid[xx][yy]->GetIndexForSeenFloor();

            auto& FLOOR = Global::contentCurrentMap->m_tilesGrid[xx][yy]->m_floorsArray[seenFloor];

            for (auto& it : FLOOR->m_containedObjects)
            {
                if (it != nullptr)
                    if (DataLoading::libDescriptions[it->m_idxObjectType] != nullptr)
                        if (DataLoading::libDescriptions[it->m_idxObjectType]->ContainsPropertyWithValue("IsObstacle", "true"))
                            return true;
            }
        }
    }





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

    //if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[PLAYER->m_coordPosition.m_x][PLAYER->m_coordPosition.m_y]->m_elevationHeight)
    //{


    //    return true;
    //}

    return false;

}

void TileRendering::CoverUnseenTiles(int x, int y, Point pTile)
{

    auto TILESIZE = Global::GetTileSize();
    auto& PLAYER = Global::statePlayer;


    bool sightIsBlockedByObject = false;

    double dx = Global::statePlayer->m_coordPosition.m_x - pTile.m_x;
    double dy = Global::statePlayer->m_coordPosition.m_y - pTile.m_y;

    double dmaxabs = max(abs(dx), abs(dy));

    if (dmaxabs > 0)
    {
        double dxstep = dx / dmaxabs;
        double dystep = dy / dmaxabs;

        for (int i = 1; i < dmaxabs && !sightIsBlockedByObject; i++)
        {
            int xx = pTile.m_x + i * dxstep;
            int yy = pTile.m_y + i * dystep;


            int seenFloor = Global::contentCurrentMap->m_tilesGrid[xx][yy]->GetIndexForSeenFloor();

            auto& FLOOR = Global::contentCurrentMap->m_tilesGrid[xx][yy]->m_floorsArray[seenFloor];

            for (auto& it : FLOOR->m_containedObjects)
            {
                if (it != nullptr)
                {
                    int objIdx = it->m_idxObjectType;
                    auto& desc = DataLoading::libDescriptions[objIdx];
                    if (desc != nullptr)
                    {
                        bool isObs = desc->ContainsPropertyWithValue("IsObstacle", "true");
                        if (isObs)
                        {
                            sightIsBlockedByObject = true;
                            break;
                        }
                    }
                }
            }
            int asd = 3;
        }
    }








    //if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[PLAYER->m_coordPosition.m_x][PLAYER->m_coordPosition.m_y]->m_elevationHeight || sightIsBlockedByObject)
    if (sightIsBlockedByObject)
    {

        int increasedSize = TILESIZE*1.7;

        D::Image(ImagesIDs::UnseenTile,
            x * TILESIZE + TILESIZE / 2 - increasedSize / 2,
            y * TILESIZE + TILESIZE / 2 - increasedSize / 2,
            increasedSize,
            increasedSize);


        return;
    }

}

void TileRendering::RenderTileGround(double tileSize, int x, int y, Point pTile)
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

    DataDescription& desc = *DataLoading::libDescriptions[tfSeenFloor->m_idxGroundType];


    //D::ImageCurrentRect(tfSeenFloor->m_idxGroundType);

    D::ImageCurrentRect(Animations::RunThroughAnimationFilter(tfSeenFloor->m_idxGroundType, pTile.m_x, pTile.m_y));



    bool tileCurrentIsWater = false;
    bool tileEastIsWater = false;
    bool tileNorthIsWater = false;

    bool isDeepWater = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight < 0;

    tileCurrentIsWater = tfSeenFloor->m_idxGroundType == ImagesIDs::TileWater;

    if (contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->GetIndexForSeenFloor() != -1)
        tileEastIsWater = tfSeenFloor->m_idxGroundType == ImagesIDs::TileWater;

    if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->GetIndexForSeenFloor() != -1)
        tileNorthIsWater = tfSeenFloor->m_idxGroundType == ImagesIDs::TileWater;

    if (!tileCurrentIsWater && tileEastIsWater && !isDeepWater)
        D::ImageCurrentRect(ImagesIDs::EdgeRight);

    if (tileCurrentIsWater && !tileEastIsWater && !isDeepWater)
        D::ImageCurrentRect(ImagesIDs::EdgeRight);

    if (!tileCurrentIsWater && tileNorthIsWater && !isDeepWater)
        D::ImageCurrentRect(ImagesIDs::EdgeTop);

    if (tileCurrentIsWater && !tileNorthIsWater && !isDeepWater)
        D::ImageCurrentRect(ImagesIDs::EdgeTop);

    bool doDrawGrassStraws = true;

    bool tileIsRock = tfSeenFloor->m_idxGroundType == ImagesIDs::TileRock;
    bool tileIsStoneSlab = tfSeenFloor->m_idxGroundType == ImagesIDs::TileStoneslab;

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
            D::ImageCurrentRect(ImagesIDs::ElevLeft);

        if ((drawElevFlags & drawElevBottom) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ImagesIDs::ElevBottom);

        if ((drawElevFlags & drawElevLeftDark) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ImagesIDs::ElevLeftDark);

        if ((drawElevFlags & drawElevBottomDark) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ImagesIDs::ElevBottomDark);

        if ((drawElevFlags & drawEdgeRight) != 0 && !isDeepWater)
            D::ImageCurrentRect(ImagesIDs::EdgeRight);

        if ((drawElevFlags & drawEdgeTop) != 0 && !isDeepWater)
            D::ImageCurrentRect(ImagesIDs::EdgeTop);

        }
        else
        {

            if ((drawElevFlags & drawElevLeft) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ImagesIDs::ElevLeftRock);

            if ((drawElevFlags & drawElevBottom) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ImagesIDs::ElevBottomRock);

            if ((drawElevFlags & drawElevLeftDark) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ImagesIDs::ElevLeftDarkRock);

            if ((drawElevFlags & drawElevBottomDark) != 0 && !tileCurrentIsWater)
                D::ImageCurrentRect(ImagesIDs::ElevBottomDarkRock);

            if ((drawElevFlags & drawEdgeRight) != 0)
                D::ImageCurrentRect(ImagesIDs::EdgeRightRock);

            if ((drawElevFlags & drawEdgeTop) != 0)
                D::ImageCurrentRect(ImagesIDs::EdgeTopRock);

        }

        if ((drawElevFlags & drawElevCorner) != 0 && !tileCurrentIsWater)
            D::ImageCurrentRect(ImagesIDs::ElevCorner);

    }


    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight)
    {
        D::ImageCurrentRect(ImagesIDs::CaveEntranceWest);
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight)
    {
        D::ImageCurrentRect(ImagesIDs::CaveEntranceSouth);
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x + 1][pTile.m_y]->m_elevationHeight)
    {
        D::ImageCurrentRect(ImagesIDs::CaveEntranceEast);
    }

    if (contentCurrentMap->TileIsMinedAtElev(contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight, pTile.m_x, pTile.m_y)
        && contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_elevationHeight > contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y - 1]->m_elevationHeight)
    {
        D::ImageCurrentRect(ImagesIDs::CaveEntranceNorth);
    }

    int tileFloorGroundType = tfSeenFloor->m_idxGroundType;

    srand(pTile.m_x * 100 + pTile.m_y * 100);
    float scale = (float)(rand() % 10) / 10.0f + 0.5f;

    int destWScaled = (int)(destW * scale*0.8);
    int destHScaled = (int)(destH * scale * 0.8);
    int destXScaled = destX + TILESIZE / 2 - (int)(destWScaled / 2);
    int destYScaled = destY + TILESIZE - (int)(destHScaled);

    

    if (doDrawGrassStraws && tileFloorGroundType == ImagesIDs::TileGrass)
    {

        int grassStrawsAmount = (pTile.m_x + pTile.m_y + pTile.m_x * pTile.m_y) % 6;

        int xx = pTile.m_x + Global::tilesMapSize / 2;
        int yy = pTile.m_y + Global::tilesMapSize / 2;

        float drynessScale = 2.0;

        float drynessLimit = cos(2 * (1 + (pTile.m_y* drynessScale + yy * yy* drynessScale* drynessScale + pTile.m_y * drynessScale * pTile.m_x * drynessScale + cos(pTile.m_x * drynessScale / 100.0 + xx * xx* drynessScale* drynessScale / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
        float dryness = drynessLimit;

        if (dryness > 0.1)
        {

            D::FilledCurrentRect(200, 80, 30, dryness * 100);

        }
        else
        {

            if (scale > 0.8)
            {

                Drawing::RectPrepare(destXScaled, destYScaled, destWScaled, destHScaled);

                for (int i = 0; i < grassStrawsAmount; i++)
                    D::ImageCurrentRect(ImagesIDs::GrassStraws);

            }

        }

    }

}

void TileRendering::RenderTileHoveringEffect(int x, int y, Point pTile)
{

    SDL_Rect rTile = { x * Global::GetTileSize(), y * Global::GetTileSize(), Global::GetTileSize(), Global::GetTileSize() };

    if (pTile.m_x == PlayerActions::coordHoveredTile.m_x && pTile.m_y == PlayerActions::coordHoveredTile.m_y)
    {

        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ImagesIDs::TileHoverEffect], NULL, &rTile);

    }

}