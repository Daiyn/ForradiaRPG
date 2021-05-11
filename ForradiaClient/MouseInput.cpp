#include "MouseInput.h"
#include "CWindow.h"
#include "GUI.h"
#include "GUISystemMenu.h"
#include "GUIWorldMenu.h"
#include "KeyboardInput.h"
#include "Utilities.h"
#include <SDL2/SDL_mouse.h>
#include "Global_Player.h"
#include "Global_Canvas.h"
#include "Global_MapSize.h"
#include "Global_CurrentMap.h"
#include "ItemMoving.h"
#include "CMap.h"
#include "CPlayer.h"

void MouseInput::DoMouseDown(Uint8 button)
{

    coordMouseDown = CPoint(HOVERED_TILE);

    if (button == SDL_BUTTON_LEFT)
    {
        stateMouseButtonLeftDown = true;
        stateMouseButtonLeftPressed = true;


        if (GUISystemMenu::stateIsShown)
        {
            GUISystemMenu::HandleMouseClickInSystemMenu(stateMouseButtonLeftDown);
            stateMouseButtonLeftDown = false;
        }

        if (GUIWorldMenu::HandleLeftMouseClickInWorld())
            stateMouseButtonLeftPressed = false;
        else if (ItemMoving::TryStartDragingObjectFromGround(Utilities::GetHoveredMapx(),
                                                                Utilities::GetHoveredMapy()))
        {
            stateMouseButtonLeftPressed = false;
            stateMouseButtonLeftDown = false;
        }

        if (GUI::HandleMouseClickInGUI())
            stateMouseButtonLeftPressed = false;

    }

    if (button == SDL_BUTTON_RIGHT)
    {
        stateMouseButtonRightDown = true;
        stateMouseButtonRightPressed = true;

        GUIWorldMenu::HandleRightMouseClickInWorld();
    }

}

void MouseInput::DoMouseUp(Uint8 button)
{

    if (button == SDL_BUTTON_LEFT)
    {
        stateMouseButtonLeftDown = false;
        stateMouseButtonLeftReleased = true;
        stateMouseButtonLeftPressed = false;

        if (!GUI::HandleMouseReleaseInGUI())
            ItemMoving::DropnodupMovedObjectIfExists(Utilities::GetHoveredMapx(), Utilities::GetHoveredMapy());


        if (!stateMouseDownInGUI && !GUI::CheckMouseClickInGUI())
        {

            if (!KeyboardInput::statesPressedKeys[SDLK_LSHIFT]
                //&& !Combat::HandleMouseClickOnFoe()
            && coordMouseDown.Equals(CPoint(HOVERED_TILE)))
                Global::statePlayer->MouseClickToMove();

        }

    }

    if (button == SDL_BUTTON_RIGHT)
    {
        stateMouseButtonRightDown = false;
        stateMouseButtonRightReleased = true;
        stateMouseButtonRightPressed = false;
    }

}


void MouseInput::Update()
{

    stateMouseDownInGUI = GUI::CheckMouseClickInGUI();

    if (stateMouseButtonLeftPressed && !stateMouseDownInGUI && !GUI::CheckMouseClickInGUI())
        if (!KeyboardInput::statesPressedKeys[SDLK_LSHIFT]
            //&& !Combat::HandleMouseClickOnFoe() && ItemMoving::nodupMovedObject == NULL
            )
            Global::statePlayer->MouseClickToMove();

    if (KeyboardInput::statesPressedKeys[SDLK_LSHIFT] && stateMouseButtonLeftDown && !stateMouseDownInGUI &&
        !GUI::CheckMouseClickInGUI())
        Global::statePlayer->MouseClickToMove();

    ResetEventVariables();

}

void MouseInput::ResetEventVariables()
{

    stateMouseButtonLeftDown = false;
    stateMouseButtonRightDown = false;

    stateMouseButtonLeftReleased = false;
    stateMouseButtonRightReleased = false;

}