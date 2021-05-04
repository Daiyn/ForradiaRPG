#include "FPSCounter.h"
#include "TextRendering.h"
#include "Global_Canvas.h"
#include "Colors.h"
#include "Utilities.h"

using std::to_string;

void FPSCounter::Update() {

    frames++;

    if (Utilities::DoTickCheck(tickSinceLastSecond, 1000))
    {

        fps = frames;
        frames = 0;

    }

}

void FPSCounter::Render() {

    string strFPS = "FPS: " + to_string(fps);
    TextRendering::DrawString(strFPS, WHITE, BOTTOM_CENTER);

}
