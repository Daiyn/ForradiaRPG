#include "FPSCounter.h"
#include "TextRendering.h"
#include "Global_Canvas.h"
#include "Colors.h"
#include "Utilities.h"

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

    string strFPS = "FPS: " + to_string(resultFPS);
    TextRendering::DrawString(strFPS, WHITE, BOTTOM_CENTER);

}
