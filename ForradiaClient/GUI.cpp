#include "GUI.h"
#include "CWindowInventory.h"
#include "ImageLoading.h"
#include "GUISystemMenu.h"
#include "Global_Canvas.h"
#include "Global_Mouse.h"
#include "Global_SDL.h"
#include "Drawing.h"
#include "CGUIButton.h"

bool GUI::CheckMouseClickInGUI()
{

    CPoint pMouse = Global::GetMousePoint();

    CGUIButton buttons[numberOfGUIButtons];

    int w = (pxWidthOriginal / 1600.0 * Global::GetCanvasWidth() + pxWidthOriginal / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < numberOfGUIButtons; i++)
    {
        buttons[i] = { { x,y,w,w }, idxsButtonImages[i] };
        x += w;
    }

    for (CGUIButton button : buttons)
        if (button.m_bounds.ContainsPoint(pMouse))
            return true;

    for (int i = 0; i < activeWindows.size(); i++)
    {
        if (activeWindows[i]->CheckMouseClickInWindow())
            return true;
    }

    return false;

}

bool GUI::HandleMouseClickInGUI()
{

    CPoint pMouse = Global::GetMousePoint();

    CGUIButton buttons[numberOfGUIButtons];

    int w = (pxWidthOriginal / 1600.0 * Global::GetCanvasWidth() + pxWidthOriginal / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < numberOfGUIButtons; i++)
    {
        buttons[i] = { { x,y,w,w }, idxsButtonImages[i] };
        x += w;
    }

    for (int i = 0; i < numberOfGUIButtons; i++)
    {

        if (buttons[i].m_bounds.ContainsPoint(pMouse))
        {

            switch (i)
            {
            case 0:
                activeWindows.push_back(std::make_unique<CWindowInventory>(CWindowInventory()));
                break;
            case 2: 
                GUISystemMenu::Show();
                break;
            }
        
            return true;
        }

    }

    for (int i = 0; i < activeWindows.size(); i++)
    {
        if (activeWindows[i]->HandleMouseClickInWindow())
            return true;
    }

    return false;

}

bool GUI::HandleMouseReleaseInGUI()
{

    for (int i = 0; i < activeWindows.size(); i++)
    {
        if (activeWindows[i]->HandleMouseReleaseInWindow())
            return true;
    }

    return false;

}

void GUI::Update()
{


    CPoint pMouse = Global::GetMousePoint();

    CGUIButton buttons[numberOfGUIButtons];

    int w = (pxWidthOriginal / 1600.0 * Global::GetCanvasWidth() + pxWidthOriginal / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < numberOfGUIButtons; i++)
    {
        buttons[i] = { { x,y,w,w }, idxsButtonImages[i] };
        x += w;
    }


    for (auto it = activeWindows.begin(); it != activeWindows.end(); it++)
    {

        (*it)->Update();

        if ((*it)->m_activateWindowDestruction)
        {
            activeWindows.erase(it);
            Update();
            return;
        }

    }

}

void GUI::Render()
{

    for (int i = 0; i < activeWindows.size(); i++)
    {
        activeWindows[i]->Render();
    }

    CGUIButton buttons[numberOfGUIButtons];

    int w = (pxWidthOriginal / 1600.0 * Global::GetCanvasWidth() + pxWidthOriginal / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < numberOfGUIButtons; i++)
    {
        buttons[i] = { { x,y,w,w }, idxsButtonImages[i] };
        x += w;
    }

    int wBackground = 360 * Global::GetScalingHorizontal();
    int hBackground = 120 * Global::GetScalingVertical();

    int xBackground = Global::GetCanvasWidth() - wBackground;
    int yBackground = Global::GetCanvasHeight() - hBackground;

    Drawing::Image(kIDIconsBackground, xBackground, yBackground, wBackground, hBackground);

    for (int i = 0; i < numberOfGUIButtons; i++)
        Drawing::Image(buttons[i].m_idxImage, buttons[i].m_bounds.x, buttons[i].m_bounds.y, buttons[i].m_bounds.w, buttons[i].m_bounds.h);

}
