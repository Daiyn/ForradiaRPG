#include "GUICoordPanel.h"
#include "SDL2/SDL_render.h"
#include "TextRendering.h"
#include "GUIMinimap.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Global_Player.h"
#include "Drawing.h"
#include "Colors.h"
#include "CPlayer.h"

void GUICoordPanel::Render()
{

    int y = GUIMinimap::GetBottomY();
    int w = 100;
    int x = Global::GetCanvasWidth() - w;
    int h = 25;
    int margin = 3;

    Drawing::FilledRect(MEDIUM_BLUE_TRANSPARENT, x, y, w, h);

    string strCoord = "(" + std::to_string(Global::player->m_coordPosition.m_x) + ", " + std::to_string(Global::player->m_coordPosition.m_y) + ")";

    TextRendering::DrawString(strCoord, BLACK, x + margin, y + margin);

}