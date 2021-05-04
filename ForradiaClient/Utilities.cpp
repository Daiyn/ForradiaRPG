#include "Utilities.h"
#include <stdlib.h>
#include <SDL2/SDL_timer.h>
#include "Global_Mouse.h"
#include "Global_Canvas.h"
#include "Global_Player.h"
#include "Global_MapSize.h"
#include "CPlayer.h"

int Utilities::Normalize(int a, int b)
{

    int d = a - b;
    int absd = abs(d);
    int norm = 0;

    if (d != 0)
        norm = d / absd;

    return norm;

}

int Utilities::GenerateAnimationFrameIndex(int numberOfFrames, int animationSpeed)
{

    return (SDL_GetTicks() % (numberOfFrames * animationSpeed)) / animationSpeed;

}

int Utilities::GenerateTileCorrelatedAnimationFrameIndex(int numberOfFrames, int animationSpeed, int mapx, int mapy)
{

    return ((SDL_GetTicks() + mapx * 100 + mapy * 100) % (numberOfFrames * animationSpeed)) / animationSpeed;

}

int Utilities::GetHoveredScreenMapx()
{

    int mx = Global::GetMouseX();
    int tilex = mx / Global::GetTileSize();

    return tilex;

}

int Utilities::GetHoveredScreenMapy() {

    int my = Global::GetMouseY();
    int tiley = my / Global::GetTileSize();

    return tiley;

}

int Utilities::GetHoveredMapx()
{

    return Global::player->m_posCurrent.m_x - (Global::GetNumberOfColumns() - 1) / 2 + Utilities::GetHoveredScreenMapx();

}

int Utilities::GetHoveredMapy()
{

    return Global::player->m_posCurrent.m_y - (Global::numberOfRows - 1) / 2 + Utilities::GetHoveredScreenMapy();

}

bool Utilities::InMapIncludingEdges(int mapx, int mapy)
{

    if (mapx < 0 || mapx >= Global::mapSize || mapy < 0 || mapy >= Global::mapSize)
        return false;

    return true;

}

bool Utilities::InMapExcludingEdges(int mapx, int mapy)
{

    if (mapx <= 0 || mapx >= Global::mapSize - 1 || mapy <= 0 || mapy >= Global::mapSize - 1)
        return false;

    return true;

}


bool Utilities::DoTickCheck(int& tickVariable, int threshold)
{
    bool result = SDL_GetTicks() - tickVariable > threshold;

    if (result)
        tickVariable = SDL_GetTicks();

    return result;
}