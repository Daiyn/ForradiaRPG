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
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        Drawing::Image(kIDForradiaStartText0, Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() / 2 - h / 2, w, h);
        break;

    }

 }
