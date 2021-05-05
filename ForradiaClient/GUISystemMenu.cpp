#include "GUISystemMenu.h"
#include "CSceneMainMenu.h"
#include "TextRendering.h"
#include "ImageLoading.h"
#include "Global_Canvas.h"
#include "Global_GUIProperties.h"
#include "Global_CurrentScene.h"
#include "Global_SDL.h"
#include "Cursor.h"
#include "Global_Mouse.h"
#include "Drawing.h"
#include <memory>

using std::make_unique;


void GUISystemMenu::Show()
{
    isShown = true;
}

void GUISystemMenu::HandleMouseClickInSystemMenu(bool leftMouseButtonDown)
{

    CPoint pMouse = Global::GetMousePoint();

    int i = 0;

    for (auto option : menuOptions) {

        CRectangle rect = {
                Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                Global::GetCanvasHeight() / 4 + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin),
                Global::attrMenuButtonWidth,
                Global::attrMenuButtonHeight};

        if (rect.ContainsPoint(pMouse)) {
            switch (i) {
                case 0:
                    Global::ChangeScene(make_unique<CSceneMainMenu>(CSceneMainMenu()));
                    isShown = false;
                    break;

                case 1:
                    isShown = false;
                    break;
            }
        }

        i++;
    }

}

void GUISystemMenu::Update()
{

    if (!isShown)
        return;

    CPoint pMouse = Global::GetMousePoint();

    Cursor::isHoveringButton = false;

    int i = 0;

    for (auto option : menuOptions)
    {

        CRectangle rect = {
                Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                Global::GetCanvasHeight() / 4 + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin),
                Global::attrMenuButtonWidth,
                Global::attrMenuButtonHeight };

        if (rect.ContainsPoint(pMouse))
            Cursor::isHoveringButton = true;

        i++;
    }


}

void GUISystemMenu::RenderIfShown() {

    if (!isShown)
        return;

    CPoint pMouse = Global::GetMousePoint();


    int i = 0;

    for (auto option : menuOptions) {

        CRectangle rect = {
                Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                Global::GetCanvasHeight() / 4 + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin),
                Global::attrMenuButtonWidth,
                Global::attrMenuButtonHeight};


        int imgIndex = 0;

        if (rect.ContainsPoint(pMouse))
            imgIndex = ID_MENU_BUTTON_BACK_HOVERED;
        else
            imgIndex = ID_MENU_BUTTON_BACK;


        Drawing::Image(imgIndex, rect);

        int xmid = rect.x + rect.w / 2;
        int xtestpos = xmid - TextRendering::GetTextWidth(option) / 2;

        int ymid = rect.y + rect.h / 2;
        int ytestpos = ymid - TextRendering::GetTextHeight() / 2;

        TextRendering::DrawString(option.c_str(), {0, 0, 0}, xtestpos, ytestpos);

        i++;

    }

}