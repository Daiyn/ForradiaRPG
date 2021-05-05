#include "GUIStatusPanel.h"
#include "TextRendering.h"
#include "ImageLoading.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Global_Player.h"
#include "Drawing.h"
#include "Colors.h"
#include "CPlayer.h"
#include <iomanip>

using std::stringstream;
using std::setprecision;

void GUIStatusPanel::Render()
{

    int w = wOrig * Global::GetScalingHorizontal();
    int h = hOrig * Global::GetScalingVertical();


    CRectangle rect = {0, 0, w, h};

    auto tex = ImageLoading::texturesArray[ID_MAP_PREVIEW_BACK];
    Drawing::Image(ID_MAP_PREVIEW_BACK, rect);

    int barLeft = margin;
    int barTop = margin * 3;
    int barWidth = w - 2 * margin;
    int barHeight = 25;

    string strHP = "HP: " + std::to_string(Global::player->m_statCurrentHP) + "/" + std::to_string(Global::player->m_statMaxHP);

    TextRendering::DrawString(strHP, WHITE, margin, margin);

    CRectangle rectHPBar = {barLeft, barTop, barWidth, barHeight};

    Drawing::FilledRect(BLACK, rectHPBar);

    int hpBarFilledWidth = barWidth * (double) Global::player->m_statCurrentHP / Global::player->m_statMaxHP;

    if (hpBarFilledWidth > 0)
    {

        CRectangle rectHPBarFilled = {barLeft, barTop, hpBarFilledWidth, barHeight};

        Drawing::FilledRect(GREEN, rectHPBarFilled);
        Drawing::RectContour(BLACK, rectHPBarFilled);

    }

    barTop += 2 * barHeight;

    stringstream streamNRGYCurrent;
    streamNRGYCurrent << std::fixed << setprecision(0) << Global::player->m_statCurrentNRGY;
    string strNRGYCurrent = streamNRGYCurrent.str();

    stringstream streamNRGYMax;
    streamNRGYMax << std::fixed << setprecision(0) << Global::player->m_statMaxNRGY;
    string strNRGYMax = streamNRGYMax.str();

    string strNRGY = "NRGY: " + strNRGYCurrent + "/" + strNRGYMax;

    TextRendering::DrawString(strNRGY, WHITE, margin, margin + 2*barHeight);

    CRectangle rectNRGYBar = { barLeft, barTop, barWidth, barHeight };

    Drawing::FilledRect(BLACK, rectNRGYBar);

    int nrgyBarFilledWidth = barWidth * (double)Global::player->m_statCurrentNRGY / Global::player->m_statMaxNRGY;

    if (nrgyBarFilledWidth > 0)
    {

        CRectangle rectNRGYBarFilled = { barLeft, barTop, nrgyBarFilledWidth, barHeight };

        Drawing::FilledRect(ORANGE, rectNRGYBarFilled);
        Drawing::RectContour(BLACK, rectNRGYBarFilled);

    }

}