#include "GUI.h"
#include "CWindowInventory.h"
#include "ImageLoading.h"
#include "GUISystemMenu.h"
#include "Global_Canvas.h"
#include "Global_Mouse.h"
#include "Global_SDL.h"
#include "Drawing.h"
#include "Cursor.h"
#include "CGUIButton.h"

bool GUI::CheckMouseClickInGUI()
{

    CPoint pMouse = Global::GetMousePoint();

    CGUIButton buttons[NUMBER_OF_BUTTONS];

    int w = (wOrig / 1600.0 * Global::GetCanvasWidth() + wOrig / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        buttons[i] = { { x,y,w,w }, buttonImages[i] };
        x += w;
    }

    for (CGUIButton button : buttons)
        if (button.m_bounds.ContainsPoint(pMouse))
            return true;

    for (int i = 0; i < windows.size(); i++)
    {
        if (windows[i]->CheckMouseClickInWindow())
            return true;
    }

    return false;

}

bool GUI::HandleMouseClickInGUI()
{

    CPoint pMouse = Global::GetMousePoint();

    CGUIButton buttons[NUMBER_OF_BUTTONS];

    int w = (wOrig / 1600.0 * Global::GetCanvasWidth() + wOrig / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        buttons[i] = { { x,y,w,w }, buttonImages[i] };
        x += w;
    }

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {

        if (buttons[i].m_bounds.ContainsPoint(pMouse))
        {

            switch (i)
            {
            case 0:
                windows.push_back(std::make_unique<CWindowInventory>(CWindowInventory()));
                break;
            case 2: 
                GUISystemMenu::Show();
                break;
            }
        
            return true;
        }

    }

    for (int i = 0; i < windows.size(); i++)
    {
        if (windows[i]->HandleMouseClickInWindow())
            return true;
    }

    return false;

}

bool GUI::HandleMouseReleaseInGUI()
{

    for (int i = 0; i < windows.size(); i++)
    {
        if (windows[i]->HandleMouseReleaseInWindow())
            return true;
    }

    return false;

}

void GUI::Update()
{


    CPoint pMouse = Global::GetMousePoint();

    CGUIButton buttons[NUMBER_OF_BUTTONS];

    int w = (wOrig / 1600.0 * Global::GetCanvasWidth() + wOrig / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        buttons[i] = { { x,y,w,w }, buttonImages[i] };
        x += w;
    }

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {

        if (buttons[i].m_bounds.ContainsPoint(pMouse))
        {
            Cursor::isHoveringButton = true;
            break;

        }

    }

    for (auto it = windows.begin(); it != windows.end(); it++)
    {

        (*it)->Update();

        if ((*it)->m_activateWindowDestruction)
        {
            windows.erase(it);
            Update();
            return;
        }

    }

}

void GUI::Render()
{

    for (int i = 0; i < windows.size(); i++)
    {
        windows[i]->Render();
    }

    CGUIButton buttons[NUMBER_OF_BUTTONS];

    int w = (wOrig / 1600.0 * Global::GetCanvasWidth() + wOrig / 900.0 * Global::GetCanvasHeight()) / 2;

    int x = Global::GetCanvasWidth() - 3 * w;
    int y = Global::GetCanvasHeight() - w;

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        buttons[i] = { { x,y,w,w }, buttonImages[i] };
        x += w;
    }

    int wBackground = 360 * Global::GetScalingHorizontal();
    int hBackground = 120 * Global::GetScalingVertical();

    int xBackground = Global::GetCanvasWidth() - wBackground;
    int yBackground = Global::GetCanvasHeight() - hBackground;

    Drawing::Image(ID_ICONS_BACKGROUND, xBackground, yBackground, wBackground, hBackground);

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
        Drawing::Image(buttons[i].m_idxImage, buttons[i].m_bounds.x, buttons[i].m_bounds.y, buttons[i].m_bounds.w, buttons[i].m_bounds.h);

}
