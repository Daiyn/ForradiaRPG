#include "FPSCounter.h"
#include "TextRendering.h"
#include "Global_Canvas.h"
#include "Colors.h"
#include "Utilities.h"
#include "Drawing.h"

using std::to_string;

void FPSCounter::Update()
{

    framesCountForOneSec++;

    if (tmrFPSSave.TimeForUpdate())
    {

        resultFPS = framesCountForOneSec;
        framesCountForOneSec = 0;

    }

}

void FPSCounter::Render()
{

    Drawing::FilledRect(WHITE, Global::GetCanvasWidth() / 2 - 50, Global::GetCanvasHeight() - 30, 100, 30);
    string strFPS = "FPS: " + to_string(resultFPS);
    TextRendering::DrawString(strFPS, BLACK, BOTTOM_CENTER);

}
