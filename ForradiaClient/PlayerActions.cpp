#include "PlayerActions.h"
#include <SDL2/SDL_mouse.h>
#include "Global_Canvas.h"
#include "Global_Player.h"
#include <SDL2/SDL_timer.h>
#include "Global_SDL.h"
#include <SDL2/SDL_render.h>
#include "Global_CurrentMap.h"
#include "DataLoading.h"
#include "CMap.h"
#include "CPlayer.h"

void RenderPlayerActions()
{
    PlayerActions::Render();
}

void PlayerActions::FocusOnObject(CPoint p)
{

    focusedObjectMapx = p.m_x;
    focusedObjectMapy = p.m_y;
    focusedObjectProgress = 0;

}

void PlayerActions::Update()
{

    UpdateHoveredTile();
    UpdateSkillsPerformed();
    UpdateFocusedObject();

}

void PlayerActions::UpdateHoveredTile()
{
    if (Global::statePlayer != nullptr)
    {
        CPoint p;

        SDL_GetMouseState(&p.m_x, &p.m_y);
        p = { p.m_x / Global::GetTileSize(), p.m_y / Global::GetTileSize() };
        p = { Global::statePlayer->m_coordPosition.m_x - (Global::GetNumberOfColumns() - 1) / 2 + p.m_x, Global::statePlayer->m_coordPosition.m_y - (Global::tilesNumberOfRows - 1) / 2 + p.m_y };
        hoveredTile = p;
    }

}

void PlayerActions::StartPerformSkill()
{

    if (SDL_GetTicks() - Global::statePlayer->m_tickLastSkillCastEnded < Global::statePlayer->m_spdSkillCasting)
        return;

    if (skillInAction)
        return;

    float dx = hoveredTile.m_x - Global::statePlayer->m_coordPosition.m_x;
    float dy = hoveredTile.m_y - Global::statePlayer->m_coordPosition.m_y;

    float dist = sqrt(dx * dx + dy * dy);

    dxStep = dx / dist;
    dyStep = dy / dist;

    xStart = Global::statePlayer->m_coordPosition.m_x;
    yStart = Global::statePlayer->m_coordPosition.m_y;

    tickStartSkillPerform = SDL_GetTicks();

    skillInAction = true;

    skillAffectedTiles.clear();

}

void PlayerActions::Render()
{

    if (!skillInAction)
        return;

    float deltaTime = SDL_GetTicks() - tickStartSkillPerform;
    deltaTime = pow(deltaTime, 1.5f);
    deltaTime /= 120;

    float currentX = xStart + deltaTime * dxStep / 2;
    float currentY = yStart + deltaTime * dyStep / 2;

    float tileX = currentX - (Global::statePlayer->m_coordPosition.m_x - (Global::GetNumberOfColumns() - 1) / 2);
    float tileY = currentY - (Global::statePlayer->m_coordPosition.m_y - (Global::tilesNumberOfRows - 1) / 2);

    skillAffectedTiles.push_back({(int) currentX, (int) currentY});


    int dx = currentX - Global::statePlayer->m_coordPosition.m_x;
    int dy = currentY - Global::statePlayer->m_coordPosition.m_y;

    int dist = sqrt(dx * dx + dy * dy);

    for (int y = currentY - dist; y <= currentY + dist; y++)
    {
        for (int x = currentX - dist; x <= currentX + dist; x++)
        {
            int ddx = x - currentX;
            int ddy = y - currentY;

            if (ddx * ddx + ddy * ddy < dist)
                skillAffectedTiles.push_back({(int) x, (int) y});
        }
    }

    if (dx * dx + dy * dy > 8 * 8)
        return;


    int x1 = (Global::GetNumberOfColumns() - 1) / 2 * Global::GetTileSize() - 0 * Global::GetTileSize();
    int y1 = (Global::tilesNumberOfRows - 1) / 2 * Global::GetTileSize();

    int x2 = (int) (tileX * Global::GetTileSize());
    int y2 = (int) (tileY * Global::GetTileSize());

    x2 = x1 + (x2 - x1) * 1;
    y2 = y1 + (y2 - y1) * 1;

    for (int i = 0; i < 256; i += 5)
    {
        SDL_SetRenderDrawColor(Global::renderer, 255, 255 - i * 3 / 4, 0, i);

        if (i % 15 == 0)
            SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, i);

        SDL_RenderDrawLine(Global::renderer, x1, y1, x2 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1),
                           y2 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1));
        SDL_RenderDrawLine(Global::renderer, x1, y1,
                           x2 + 1 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1),
                           y2 + 1 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1));
    }
}

void PlayerActions::UpdateSkillsPerformed()
{
    if (skillInAction)
    {
        float deltaTime = SDL_GetTicks() - tickStartSkillPerform;
        deltaTime = pow(deltaTime, 1.5f);

        if (deltaTime > 4000)
        {
            skillAffectedTiles.clear();
            skillInAction = false;
            Global::statePlayer->m_tickLastSkillCastEnded = SDL_GetTicks();
        }
    }
}

void PlayerActions::UpdateFocusedObject()
{
    if (focusedObjectMapx != -1 && focusedObjectMapy != -1)
    {
        if (tmrFocusedObjectProgressIncrease.TimeForUpdate())
        {
 
            if (focusedObjectProgress >= 2)
            {

                if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTree1"), focusedObjectMapx, focusedObjectMapy, SURFACE_FLOOR)
                    || Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTree2"), focusedObjectMapx, focusedObjectMapy, SURFACE_FLOOR))
                {

                    Global::contentCurrentMap->m_tilesGrid[focusedObjectMapx][focusedObjectMapy]->m_floorsArray[SURFACE_FLOOR]->ClearObjects();
                    Global::contentCurrentMap->m_tilesGrid[focusedObjectMapx][focusedObjectMapy]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectFelledTree"));

                }

                focusedObjectMapx = -1;
                focusedObjectMapy = -1;

            }

            focusedObjectProgress += 1;

        }
    }
}