#include "CSceneStartScreen.h"
#include "CSceneMainMenu.h"
#include "Utilities.h"
#include "Drawing.h"
#include "Global_CurrentScene.h"
#include "Global_Canvas.h"
#include "Global_GUIProperties.h"
#include "Constants.h"

#include <memory>

using std::make_unique;


void CSceneStartScreen::DoMouseDown(Uint8 button)
{

    Global::ChangeScene(make_unique<CSceneMainMenu>(CSceneMainMenu()));

}

void CSceneStartScreen::Render()
{

    int animIndex = Utilities::GenerateAnimationFrameIndex(4, 300);
    int animIndex_cloudsBack = Utilities::GenerateAnimationFrameIndex(4, 900);
    int animIndex_bgWater = Utilities::GenerateAnimationFrameIndex(5, 300);
    int animIndex_cloudsFront = Utilities::GenerateAnimationFrameIndex(4, 900);
    int animIndex_text = Utilities::GenerateAnimationFrameIndex(19, 90);

    if (animIndex_text > 8)
        animIndex_text = 0;

    Drawing::FilledRect(Global::attrBackColorR, Global::attrBackColorG, Global::attrBackColorB, 0, 0, Global::GetCanvasWidth(), Global::GetCanvasHeight());

    int w = 500;
    int h = 223;

    switch (animIndex_text)
    {

    case 0:
        Drawing::Image( ID_FORRADIA_START_TEXT_0, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 1:
        Drawing::Image(ID_FORRADIA_START_TEXT_1, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 2:
        Drawing::Image(ID_FORRADIA_START_TEXT_2, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 3:
        Drawing::Image(ID_FORRADIA_START_TEXT_3, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 4:
        Drawing::Image(ID_FORRADIA_START_TEXT_4, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 5:
        Drawing::Image(ID_FORRADIA_START_TEXT_5, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 6:
        Drawing::Image(ID_FORRADIA_START_TEXT_6, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 7:
        Drawing::Image(ID_FORRADIA_START_TEXT_7, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    case 8:
        Drawing::Image(ID_FORRADIA_START_TEXT_8, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;
    }

 }
