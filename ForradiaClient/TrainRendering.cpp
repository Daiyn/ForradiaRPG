#include "TrainRendering.h"
#include "ImageLoading.h"
#include "CTrain.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include <SDL2/SDL_timer.h>
#include "Global_Train.h"
#include "CNPC.h"



void TrainRendering::RenderTrainLocomotive(int x, int y, CPoint pTile)
{

    if (pTile.m_x == Global::defaultTrain->m_coordPosition.x && pTile.m_y == Global::defaultTrain->m_coordPosition.y)
    {

        int imgWidth = Global::GetTileSize() * 4;
        int imgHeight = Global::GetTileSize() * 4;

        SDL_Rect rTileMod = { x * Global::GetTileSize() - Global::GetTileSize() * 3,
                                y * Global::GetTileSize() - Global::GetTileSize() * 2,
                                imgWidth,
                                imgHeight };

        int animIndex = (SDL_GetTicks() % 900) / 300;

        switch (animIndex)
        {

        case 0:
            SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDTrainLocomotive0], NULL, &rTileMod);
            break;
        case 1:
            SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDTrainLocomotive1], NULL, &rTileMod);
            break;
        case 2:
            SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDTrainLocomotive2], NULL, &rTileMod);
            break;

        }

        for (int i = 0; i < Global::defaultTrain->m_containedNPCsOnTrain.size(); i++)
        {

            int imgWidth = Global::GetTileSize() * 1.5;
            int imgHeight = Global::GetTileSize() * 1.5;

            SDL_Rect rTileMod = { x * Global::GetTileSize() - Global::GetTileSize() * 4.5 - i * Global::GetTileSize() * 2,
                                    y * Global::GetTileSize() - Global::GetTileSize() * 1.5,
                                    imgWidth,
                                    imgHeight };

            SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDNPCSprite], NULL, &rTileMod);

        }
    }
}


void TrainRendering::RenderTrainCarriages(int x, int y, CPoint pTile)
{

    for (auto it = Global::defaultTrain->m_coordsCarriagePositions.begin();
         it != Global::defaultTrain->m_coordsCarriagePositions.end(); it++)
    {

        if (pTile.m_x == (*it).x && pTile.m_y == (*it).y)
        {

            int imgWidth = Global::GetTileSize() * 4;
            int imgHeight = Global::GetTileSize() * 4;

            SDL_Rect rTileMod = { x * Global::GetTileSize() - Global::GetTileSize() * 3,
                    y * Global::GetTileSize() - Global::GetTileSize() * 2,
                    imgWidth,
                    imgHeight };

            SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDTrainCarriage], NULL, &rTileMod);

        }
    }
}