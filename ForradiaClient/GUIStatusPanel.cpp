#include "GUIStatusPanel.h"
#include "TextRendering.h"
#include "ImageLoading.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Global_Player.h"
#include "Drawing.h"
#include "Colors.h"
#include "Player.h"
#include <iomanip>

using std::stringstream;
using std::setprecision;

void GUIStatusPanel::Render()
{

    int w = pxWidthOriginal * Global::GetScalingHorizontal();
    int h = pxHeightOriginal * Global::GetScalingVertical();


    Rectangle rect = {0, 0, w, h};

    auto tex = ImageLoading::libTextures[ImagesIDs::FullMapFrameBackground];
    Drawing::Image(ImagesIDs::FullMapFrameBackground, rect);

    int barLeft = pxMargin;
    int barTop = pxMargin * 3;
    int barWidth = w - 2 * pxMargin;
    int barHeight = 25;

    stringstream streamNRGYCurrent;
    streamNRGYCurrent << std::fixed << setprecision(0) << Global::statePlayer->m_statCurrentNRGY;
    string strNRGYCurrent = streamNRGYCurrent.str();

    stringstream streamNRGYMax;
    streamNRGYMax << std::fixed << setprecision(0) << Global::statePlayer->m_statMaxNRGY;
    string strNRGYMax = streamNRGYMax.str();

    string strNRGY = "NRGY: " + strNRGYCurrent + "/" + strNRGYMax;

    TextRendering::DrawString(strNRGY, WHITE, pxMargin, pxMargin);

    Rectangle rectNRGYBar = { barLeft, barTop, barWidth, barHeight };

    Drawing::FilledRect(BLACK, rectNRGYBar);

    int nrgyBarFilledWidth = barWidth * (double)Global::statePlayer->m_statCurrentNRGY / Global::statePlayer->m_statMaxNRGY;

    if (nrgyBarFilledWidth > 0)
    {

        Rectangle rectNRGYBarFilled = { barLeft, barTop, nrgyBarFilledWidth, barHeight };

        Drawing::FilledRect(ORANGE, rectNRGYBarFilled);
        Drawing::RectContour(BLACK, rectNRGYBarFilled);

    }

}