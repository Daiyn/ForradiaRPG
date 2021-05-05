#include "MouseInput.h"
#include "CWindow.h"
#include "GUI.h"
#include "GUISystemMenu.h"
#include "GUIWorldMenu.h"
#include "KeyboardInput.h"
#include "Combat.h"
#include "Utilities.h"
#include <SDL2/SDL_mouse.h>
#include "Global_Player.h"
#include "Global_Canvas.h"
#include "Global_MapSize.h"
#include "Global_CurrentMap.h"
#include "ItemMoving.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CNPCDialog.h"

void MouseInput::DoMouseDown(Uint8 button)
{

    pMouseDown = CPoint(HOVERED_TILE);

    if (button == SDL_BUTTON_LEFT)
    {
        mouseButtonLeftDown = true;
        mouseButtonLeftPressed = true;


        if (GUISystemMenu::isShown)
        {
            GUISystemMenu::HandleMouseClickInSystemMenu(mouseButtonLeftDown);
            mouseButtonLeftDown = false;
        }

        if (GUIWorldMenu::HandleLeftMouseClickInWorld())
            mouseButtonLeftPressed = false;
        else if (ItemMoving::TryStartDragingObjectFromGround(Utilities::GetHoveredMapx(),
                                                                Utilities::GetHoveredMapy()))
        {
            mouseButtonLeftPressed = false;
            mouseButtonLeftDown = false;
        }

        if (GUI::HandleMouseClickInGUI())
            mouseButtonLeftPressed = false;

    }

    if (button == SDL_BUTTON_RIGHT)
    {
        mouseButtonRightDown = true;
        mouseButtonRightPressed = true;

        GUIWorldMenu::HandleRightMouseClickInWorld();
    }

}

void MouseInput::DoMouseUp(Uint8 button)
{

    if (button == SDL_BUTTON_LEFT)
    {
        mouseButtonLeftDown = false;
        mouseButtonLeftReleased = true;
        mouseButtonLeftPressed = false;

        if (!GUI::HandleMouseReleaseInGUI())
            ItemMoving::DropObjectInAirIfExists(Utilities::GetHoveredMapx(), Utilities::GetHoveredMapy());


        if (!mouseDownInGUI && !GUI::CheckMouseClickInGUI())
        {

            if (!KeyboardInput::pressedKeys[SDLK_LSHIFT] && !Combat::HandleMouseClickOnFoe()
            && pMouseDown.Equals(CPoint(HOVERED_TILE)))
                Global::player->MouseClickToMove();

        }

    }

    if (button == SDL_BUTTON_RIGHT)
    {
        mouseButtonRightDown = false;
        mouseButtonRightReleased = true;
        mouseButtonRightPressed = false;
    }

}

void MouseInput::CheckMouseClickOnNPCs()
{

    CPoint pHoveredTile(HOVERED_TILE);

    if (pHoveredTile.WithinMap())
    {
        if (mouseButtonLeftDown)
        {
            if (Global::contentCurrentMap->m_tilesGrid[pHoveredTile.m_x][pHoveredTile.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs.size() > 0)
            {
                CNPC& npc = *Global::contentCurrentMap->m_tilesGrid[pHoveredTile.m_x][pHoveredTile.m_y]->m_floorsArray[SURFACE_FLOOR]->m_containedNPCs[0].get();

                if (npc.m_stateCurrentActivity == CNPC::NPCActivites::StandingInPlazaTalkable)
                {

                    std::unique_ptr<CWindow> win(new CWindow(100, 100, 400, 300, npc.m_uniqueID, "Dialog"));
                    GUI::windows.push_back(move(win));

                }
            }
        }
    }
}

void MouseInput::Update()
{

    mouseDownInGUI = GUI::CheckMouseClickInGUI();

    if (mouseButtonLeftPressed && !mouseDownInGUI && !GUI::CheckMouseClickInGUI())
        if (!KeyboardInput::pressedKeys[SDLK_LSHIFT] && !Combat::HandleMouseClickOnFoe() && ItemMoving::objectInAir == NULL)
            Global::player->MouseClickToMove();

    if (KeyboardInput::pressedKeys[SDLK_LSHIFT] && mouseButtonLeftDown && !mouseDownInGUI &&
        !GUI::CheckMouseClickInGUI())
        Global::player->MouseClickToMove();

    CheckMouseClickOnNPCs();
    ResetEventVariables();

}

void MouseInput::ResetEventVariables()
{

    mouseButtonLeftDown = false;
    mouseButtonRightDown = false;

    mouseButtonLeftReleased = false;
    mouseButtonRightReleased = false;

}