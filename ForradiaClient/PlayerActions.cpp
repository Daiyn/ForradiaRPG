#include "PlayerActions.h"
#include <SDL2/SDL_mouse.h>
#include "Global_Canvas.h"
#include "Global_Player.h"
#include <SDL2/SDL_timer.h>
#include "Global_SDL.h"
#include <SDL2/SDL_render.h>
#include "Global_CurrentMap.h"
#include "DataLoading.h"
#include "Map.h"
#include "Player.h"

void RenderPlayerActions()
{
    PlayerActions::Render();
}

void PlayerActions::FocusOnObject(Point p)
{

    coordFocusedObjectMapx = p.m_x;
    coordFocusedObjectMapy = p.m_y;
    stateFocusedObjectProgress = 0;

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
        Point p;

        SDL_GetMouseState(&p.m_x, &p.m_y);
        p = { p.m_x / Global::GetTileSize(), p.m_y / Global::GetTileSize() };
        p = { Global::statePlayer->m_coordPosition.m_x - (Global::GetNumberOfColumns() - 1) / 2 + p.m_x, Global::statePlayer->m_coordPosition.m_y - (Global::tilesNumberOfRows - 1) / 2 + p.m_y };
        coordHoveredTile = p;
    }

}

void PlayerActions::StartPerformSkill()
{

    if (SDL_GetTicks() - Global::statePlayer->m_tickLastSkillCastEnded < Global::statePlayer->m_spdSkillCasting)
        return;

    if (stateSkillInAction)
        return;

    float dx = coordHoveredTile.m_x - Global::statePlayer->m_coordPosition.m_x;
    float dy = coordHoveredTile.m_y - Global::statePlayer->m_coordPosition.m_y;

    float dist = sqrt(dx * dx + dy * dy);

    coordDxStep = dx / dist;
    coordDyStep = dy / dist;

    coordStartX = Global::statePlayer->m_coordPosition.m_x;
    coordStartY = Global::statePlayer->m_coordPosition.m_y;

    tickStartSkillPerform = SDL_GetTicks();

    stateSkillInAction = true;

    coordsSkillAffectedTiles.clear();

}

void PlayerActions::Render()
{

    if (!stateSkillInAction)
        return;

    float deltaTime = SDL_GetTicks() - tickStartSkillPerform;
    deltaTime = pow(deltaTime, 1.5f);
    deltaTime /= 120;

    float currentX = coordStartX + deltaTime * coordDxStep / 2;
    float currentY = coordStartY + deltaTime * coordDyStep / 2;

    float tileX = currentX - (Global::statePlayer->m_coordPosition.m_x - (Global::GetNumberOfColumns() - 1) / 2);
    float tileY = currentY - (Global::statePlayer->m_coordPosition.m_y - (Global::tilesNumberOfRows - 1) / 2);

    coordsSkillAffectedTiles.push_back({(int) currentX, (int) currentY});


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
                coordsSkillAffectedTiles.push_back({(int) x, (int) y});
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
        SDL_SetRenderDrawColor(Global::sdlRendererDefault, 255, 255 - i * 3 / 4, 0, i);

        if (i % 15 == 0)
            SDL_SetRenderDrawColor(Global::sdlRendererDefault, 0, 0, 0, i);

        SDL_RenderDrawLine(Global::sdlRendererDefault, x1, y1, x2 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1),
                           y2 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1));
        SDL_RenderDrawLine(Global::sdlRendererDefault, x1, y1,
                           x2 + 1 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1),
                           y2 + 1 + (rand() % 50) * 200 / (i + 1) - (rand() % 50) * 200 / (i + 1));
    }
}

void PlayerActions::UpdateSkillsPerformed()
{
    if (stateSkillInAction)
    {
        float deltaTime = SDL_GetTicks() - tickStartSkillPerform;
        deltaTime = pow(deltaTime, 1.5f);

        if (deltaTime > 4000)
        {
            coordsSkillAffectedTiles.clear();
            stateSkillInAction = false;
            Global::statePlayer->m_tickLastSkillCastEnded = SDL_GetTicks();
        }
    }
}

void PlayerActions::UpdateFocusedObject()
{
    if (coordFocusedObjectMapx != -1 && coordFocusedObjectMapy != -1)
    {
        if (tmrFocusedObjectProgressIncrease.TimeForUpdate())
        {
 
            if (stateFocusedObjectProgress >= 2)
            {

                if (Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTree1"), coordFocusedObjectMapx, coordFocusedObjectMapy, SURFACE_FLOOR)
                    || Global::contentCurrentMap->TileHoldsObjectOfType(DataLoading::GetDescriptionIndexByName("ObjectTree2"), coordFocusedObjectMapx, coordFocusedObjectMapy, SURFACE_FLOOR))
                {

                    Global::contentCurrentMap->m_tilesGrid[coordFocusedObjectMapx][coordFocusedObjectMapy]->m_floorsArray[SURFACE_FLOOR]->ClearObjects();
                    Global::contentCurrentMap->m_tilesGrid[coordFocusedObjectMapx][coordFocusedObjectMapy]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectFelledTree"));

                }

                coordFocusedObjectMapx = -1;
                coordFocusedObjectMapy = -1;

            }

            stateFocusedObjectProgress += 1;

        }
    }
}