#include "GUISystemMenu.h"
#include "SceneMainMenu.h"
#include "TextRendering.h"
#include "ImageLoading.h"
#include "Global_Canvas.h"
#include "Global_GUIProperties.h"
#include "Global_CurrentScene.h"
#include "Global_SDL.h"
#include "Global_Mouse.h"
#include "Drawing.h"
#include <memory>

using std::make_unique;


void GUISystemMenu::Show()
{
    stateIsShown = true;
}

void GUISystemMenu::HandleMouseClickInSystemMenu(bool leftMouseButtonDown)
{

    Point pMouse = Global::GetMousePoint();

    int i = 0;

    for (auto option : labelsMenuOptions) {

        Rectangle rect = {
                Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                Global::GetCanvasHeight() / 4 + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin),
                Global::attrMenuButtonWidth,
                Global::attrMenuButtonHeight};

        if (rect.ContainsPoint(pMouse)) {
            switch (i) {
                case 0:
                    Global::ChangeScene(make_unique<SceneMainMenu>(SceneMainMenu()));
                    stateIsShown = false;
                    break;

                case 1:
                    stateIsShown = false;
                    break;
            }
        }

        i++;
    }

}

void GUISystemMenu::Update()
{

    if (!stateIsShown)
        return;

    Point pMouse = Global::GetMousePoint();


    int i = 0;

    for (auto option : labelsMenuOptions)
    {

        Rectangle rect = {
                Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                Global::GetCanvasHeight() / 4 + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin),
                Global::attrMenuButtonWidth,
                Global::attrMenuButtonHeight };


        i++;
    }


}

void GUISystemMenu::RenderIfShown() {

    if (!stateIsShown)
        return;

    Point pMouse = Global::GetMousePoint();


    int i = 0;

    for (auto option : labelsMenuOptions) {

        Rectangle rect = {
                Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                Global::GetCanvasHeight() / 4 + i * (Global::attrMenuButtonHeight + Global::attrMenuButtonMargin),
                Global::attrMenuButtonWidth,
                Global::attrMenuButtonHeight};


        int imgIndex = 0;

        if (rect.ContainsPoint(pMouse))
            imgIndex = ImagesIDs::MenuButtonBackHovered;
        else
            imgIndex = ImagesIDs::MenuButtonBackground;


        Drawing::Image(imgIndex, rect);

        int xmid = rect.x + rect.w / 2;
        int xtestpos = xmid - TextRendering::GetTextWidth(option) / 2;

        int ymid = rect.y + rect.h / 2;
        int ytestpos = ymid - TextRendering::GetTextHeight() / 2;

        TextRendering::DrawString(option.c_str(), {0, 0, 0}, xtestpos, ytestpos);

        i++;

    }

}