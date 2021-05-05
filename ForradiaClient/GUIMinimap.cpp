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

void GUIMinimap::Render()
{

    int miniMapSize = GetScaledMiniMapSize();

    if (Global::texFullMapOverview == NULL)
        Global::texFullMapOverview = Global::ConvertSurfaceToTexture(Global::contentCurrentMap->m_imgFullMapRender);

    CRectangle rectMapOverview = { Global::GetCanvasWidth() - miniMapSize - borderWidth, borderWidth, miniMapSize, miniMapSize};

    CRectangle rectFrame = rectMapOverview;
    rectFrame.Translate(-borderWidth, -borderWidth);
    rectFrame.IncreaseSize(2*borderWidth, 2*borderWidth);

    CRectangle rectPlayerPos(Global::player->m_coordPosition);
    rectPlayerPos.Scale((double)miniMapSize / Global::mapSize);
    rectPlayerPos.Translate(Global::GetCanvasWidth() - miniMapSize - borderWidth - 2, borderWidth - 2);
    rectPlayerPos.SetSize(playerPointSize, playerPointSize);

    Drawing::Image(ID_MAP_PREVIEW_BACK, rectFrame);
    Drawing::Image(Global::texFullMapOverview, rectMapOverview);

    Drawing::FilledRect(WHITE, rectPlayerPos);

}

int GUIMinimap::GetScaledMiniMapSize()
{
    return miniMapSizeOrig * Global::GetScalingAverage();
}

int GUIMinimap::GetBottomY()
{
    return GetScaledMiniMapSize() + 2 * borderWidth;
}