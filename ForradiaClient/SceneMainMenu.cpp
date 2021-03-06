#include "SceneMainMenu.h"
#include "SceneStartNewGame.h"
#include "Utilities.h"
#include "Drawing.h"
#include "TextRendering.h"
#include "Global_Gameloop.h"
#include "Global_Canvas.h"
#include "Global_Mouse.h"
#include "Global_GUIProperties.h"
#include "Global_CurrentScene.h"
#include "Global_SDL.h"
#include "Constants.h"
#include <memory>

using std::make_unique;

void SceneMainMenu::DoMouseDown(Uint8 button)
{

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    int titleW = 766 / 3 / 1600.0 * Global::GetCanvasWidth();
    int titleH = 342 / 3 / 900.0 * Global::GetCanvasHeight();
    int titleX = Global::GetCanvasWidth() / 2 - titleW / 2;
    int titleY = 0;

    int i = 0;

    for (auto menuButton : m_labelsMenuButtons)
    {

        SDL_Rect rect = {Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                         titleH * 2 + Global::attrMenuButtonMargin + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin),
                         Global::attrMenuButtonWidth,
                         Global::attrMenuButtonHeight};

        if (mx >= rect.x && my >= rect.y && mx < rect.x + rect.w && my < rect.y + rect.h) {
            switch (i) {
                case 0:
                    Global::ChangeScene(make_unique<SceneStartNewGame>(SceneStartNewGame()));
                    break;
                case 1:
                    Global::eventQuit = true;
                    break;
            }
        }

        i++;

    }

}

void SceneMainMenu::Update()
{

 

    int mx;
    int my;

    SDL_GetMouseState(&mx, &my);

    int titleH = 342 / 3 / 900.0 * Global::GetCanvasHeight();

    int i = 0;

    for (auto menuButton : m_labelsMenuButtons)
    {

        int xMenuButton = Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2;
        int yMenuButton = titleH * 2 + Global::attrMenuButtonMargin + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin);
        int wMenuButton = Global::attrMenuButtonWidth;
        int hMenuButton = Global::attrMenuButtonHeight;



        i++;

    }

}


void SceneMainMenu::Render()
{

    int animIndex_text = Utilities::GenerateAnimationFrameIndex(19, 90);

    if (animIndex_text > 8)
        animIndex_text = 0;

    Drawing::FilledRect(Global::attrBackColorR, Global::attrBackColorG, Global::attrBackColorB, 0, 0, Global::GetCanvasWidth(), Global::GetCanvasHeight());

    int titleW = 766 / 3 / 1600.0*Global::GetCanvasWidth();
    int titleH = 342 / 3 / 900.0 * Global::GetCanvasHeight();
    int titleX = Global::GetCanvasWidth() / 2 - titleW / 2;
    int titleY = titleH/2;

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

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
        Drawing::Image(ImagesIDs::ForradiaStartText0, titleX, titleY, titleW, titleH);
        break;

    }
    
    int i = 0;

    for (auto menuButton : m_labelsMenuButtons)
    {

        int xMenuButton = Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2;
        int yMenuButton = titleH*2 + Global::attrMenuButtonMargin + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin);
        int wMenuButton = Global::attrMenuButtonWidth;
        int hMenuButton = Global::attrMenuButtonHeight;

        int imgIndex = 0;

        if (mx >= xMenuButton && my >= yMenuButton && mx < xMenuButton + wMenuButton && my < yMenuButton + hMenuButton)
            imgIndex = ImagesIDs::MenuButtonBackHovered;
        else
            imgIndex = ImagesIDs::MenuButtonBackground;

        Drawing::Image(imgIndex, xMenuButton, yMenuButton, wMenuButton, hMenuButton);

        int xmid = xMenuButton + wMenuButton / 2;
        int xtestpos = xmid - TextRendering::GetTextWidth(menuButton) / 2;

        int ymid = yMenuButton + hMenuButton / 2;
        int ytestpos = ymid - TextRendering::GetTextHeight() / 2;

        TextRendering::DrawString(menuButton.c_str(), {0, 0, 0}, xtestpos, ytestpos);

        i++;
    }



}


