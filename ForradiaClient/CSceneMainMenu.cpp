#include "CSceneMainMenu.h"
#include "CSceneStartNewGame.h"
#include "Utilities.h"
#include "Drawing.h"
#include "TextRendering.h"
#include "Global_Gameloop.h"
#include "Global_Canvas.h"
#include "Global_Mouse.h"
#include "Global_GUIProperties.h"
#include "Global_CurrentScene.h"
#include "Global_SDL.h"
#include "Cursor.h"
#include "Constants.h"
#include <memory>

using std::make_unique;

void CSceneMainMenu::DoMouseDown(Uint8 button)
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
                    Global::ChangeScene(make_unique<CSceneStartNewGame>(CSceneStartNewGame()));
                    break;
                case 1:
                    Global::eventQuit = true;
                    break;
            }
        }

        i++;

    }

}

void CSceneMainMenu::Update()
{

    Cursor::isHoveringButton = false;

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


        if (mx >= xMenuButton && my >= yMenuButton && mx < xMenuButton + wMenuButton && my < yMenuButton + hMenuButton)
            Cursor::isHoveringButton = true;

        i++;

    }

}


void CSceneMainMenu::Render()
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
        Drawing::Image(kIDForradiaStartText0, titleX, titleY, titleW, titleH);
        break;
    case 1:
        Drawing::Image(kIDForradiaStartText1, titleX, titleY, titleW, titleH);
        break;
    case 2:
        Drawing::Image(kIDForradiaStartText2, titleX, titleY, titleW, titleH);
        break;
    case 3:
        Drawing::Image(kIDForradiaStartText3, titleX, titleY, titleW, titleH);
        break;
    case 4:
        Drawing::Image(kIDForradiaStartText4, titleX, titleY, titleW, titleH);
        break;
    case 5:
        Drawing::Image(kIDForradiaStartText5, titleX, titleY, titleW, titleH);
        break;
    case 6:
        Drawing::Image(kIDForradiaStartText6, titleX, titleY, titleW, titleH);
        break;
    case 7:
        Drawing::Image(kIDForradiaStartText7, titleX, titleY, titleW, titleH);
        break;
    case 8:
        Drawing::Image(kIDForradiaStartText8, titleX, titleY, titleW, titleH);
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
            imgIndex = kIDMenuButtonBackHovered;
        else
            imgIndex = kIDMenuButtonBackground;

        Drawing::Image(imgIndex, xMenuButton, yMenuButton, wMenuButton, hMenuButton);

        int xmid = xMenuButton + wMenuButton / 2;
        int xtestpos = xmid - TextRendering::GetTextWidth(menuButton) / 2;

        int ymid = yMenuButton + hMenuButton / 2;
        int ytestpos = ymid - TextRendering::GetTextHeight() / 2;

        TextRendering::DrawString(menuButton.c_str(), {0, 0, 0}, xtestpos, ytestpos);

        i++;
    }



}


