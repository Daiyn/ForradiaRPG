#include "Utilities.h"
#include "Global_Player.h"
#include "Global_Canvas.h"
#include "Global_GameSettings.h"
#include "CPoint.h"
#include "ItemMoving.h"
#include "Global_CurrentMap.h"
#include "CoreGameRendering.h"
#include "Drawing.h"
#include "PlayerActions.h"
#include "TileRendering.h"
#include "ObjectsRendering.h"
#include "PlayerRendering.h"
#include "GUIMinimap.h"
#include "GUI.h"
#include "GUIWorldMenu.h"
#include "GUIStatusPanel.h"
#include "GUISystemMenu.h"
#include "FoodEating.h"

#define FOR(x,y,z) for (int x = y; x < z; x++)

#define LOOP_OVER_SCREEN(xyz) \
            FOR(y, -3, Global::tilesNumberOfRows + 3) \
            { \
                FOR(x, 0, Global::GetNumberOfColumns() + 3) \
                { \
                    if (Utilities::InMapExcludingEdges(pTile.m_x, pTile.m_y) \
                        ) \
                    { \
                        xyz \
                    } \
                    pTile.JumpRight(); \
                } \
                pTile.JumpToNextRowStart(); \
            }


void CoreGameRendering::Render()
{

    Drawing::BlankScreen();
    RenderGroundWithObjects();
    RenderPlayerActions();
    RenderGUI();
    RenderItemMoving();

}

void CoreGameRendering::RenderGroundWithObjects()
{

    CPoint pTile;

    FOR(i, 0, 2)
    {
        pTile.JumpToScreenStart();

        LOOP_OVER_SCREEN
        (

            if (i == 0)
            {
                TileRendering::RenderTileGround(Global::GetTileSize(), x, y, pTile);
                TileRendering::RenderTileHoveringEffect(x, y, pTile);
            }
            else if (i == 1)
            {

                ObjectsRendering::RenderTileObjects(Global::GetTileSize(), x, y, pTile);
                PlayerRendering::RenderPlayer(x, y, pTile);

               if ((Global::settingGameMode == 1 && TileRendering::CheckUnseenTiles(x, y, pTile)))
                    TileRendering::CoverUnseenTiles(x, y, pTile);

            }
        )
    }
}



void CoreGameRendering::RenderGUI()
{

    FoodEating::Render();
    GUIMinimap::Render();
    GUI::Render();
    GUIWorldMenu::Render();
    GUIStatusPanel::Render();
    GUISystemMenu::RenderIfShown();

}