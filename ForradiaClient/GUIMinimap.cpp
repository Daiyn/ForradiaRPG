#include "GUIMinimap.h"
#include "ImageLoading.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Global_Player.h"
#include "Global_CurrentMap.h"
#include "Global_MapSize.h"
#include "Drawing.h"
#include "Colors.h"
#include "CMap.h"
#include "CPlayer.h"
#include "TextRendering.h"

void GUIMinimap::Render()
{

    int miniMapSize = GetScaledMiniMapSize();

    if (Global::contentCurrentMap->m_texFullMapRender == NULL)
        Global::contentCurrentMap->m_texFullMapRender = Global::ConvertSurfaceToTexture(Global::contentCurrentMap->m_imgFullMapRender);

    CRectangle rectMapOverview = { Global::GetCanvasWidth() - miniMapSize - pxBorderWidth, pxBorderWidth, miniMapSize, miniMapSize};

    CRectangle rectFrame = rectMapOverview;
    rectFrame.Translate(-pxBorderWidth, -pxBorderWidth);
    rectFrame.IncreaseSize(2*pxBorderWidth, 2*pxBorderWidth);

    CRectangle rectPlayerPos(Global::statePlayer->m_coordPosition);
    rectPlayerPos.Scale((double)miniMapSize / Global::tilesMapSize);
    rectPlayerPos.Translate(Global::GetCanvasWidth() - miniMapSize - pxBorderWidth - 2, pxBorderWidth - 2);
    rectPlayerPos.SetSize(pxPlayerSymbolSize, pxPlayerSymbolSize);

    Drawing::Image(ImagesIDs::FullMapFrameBackground, rectFrame);
    Drawing::Image(Global::contentCurrentMap->m_texFullMapRender, rectMapOverview);

    Drawing::FilledRect(WHITE, rectPlayerPos);


    // Draw coords

    int y = GetBottomY();
    int w = 100;
    int x = Global::GetCanvasWidth() - w;
    int h = 25;
    int margin = 3;

    Drawing::FilledRect(MEDIUM_BLUE_TRANSPARENT, x, y, w, h);

    string strCoord = "(" + std::to_string(Global::statePlayer->m_coordPosition.m_x) + ", " + std::to_string(Global::statePlayer->m_coordPosition.m_y) + ")";

    TextRendering::DrawString(strCoord, BLACK, x + margin, y + margin);

}

int GUIMinimap::GetScaledMiniMapSize()
{
    return pxSizeOriginal * Global::GetScalingAverage();
}

int GUIMinimap::GetBottomY()
{
    return GetScaledMiniMapSize() + 2 * pxBorderWidth;
}