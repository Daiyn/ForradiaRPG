#include "SceneCoreGameplay.h"
#include "CoreGameRendering.h"
#include "GUI.h"
#include "GUIStatusPanel.h"
#include "MouseInput.h"
#include "PlayerActions.h"
#include "GUIWorldMenu.h"
#include "GUISystemMenu.h"
#include "GUIMinimap.h"
#include "Global_Player.h"
#include "Global_SDL.h"
#include "Global_CurrentMap.h"
#include "Global_MapSize.h"
#include "Global_Worldmap.h"
#include <memory>
#include "Map.h"
#include "Player.h"
#include "FoodEating.h"
#include "GameConfiguration.h"
#include "KeyboardInput.h"

using std::make_unique;

SceneCoreGameplay::SceneCoreGameplay()
{
    Global::statePlayer = make_unique<Player>(Player(Global::tilesMapSize));
    GameConfiguration::AddPlayerStartingItems();
}

void SceneCoreGameplay::DoKeyDown(SDL_Keycode key)
{

    KeyboardInput::DoKeyDown(key);

}

void SceneCoreGameplay::DoKeyUp(SDL_Keycode key)
{

    KeyboardInput::DoKeyUp(key);

}

void SceneCoreGameplay::DoMouseDown(Uint8 button)
{

    MouseInput::DoMouseDown(button);

}

void SceneCoreGameplay::DoMouseUp(Uint8 button)
{

    MouseInput::DoMouseUp(button);

}

void SceneCoreGameplay::Update()
{

    MouseInput::Update();
    Global::statePlayer->Update();
    PlayerActions::Update();
    GUI::Update();
    GUISystemMenu::Update();
    GUIWorldMenu::Update();
    FoodEating::Update();

}

void SceneCoreGameplay::Render()
{

    CoreGameRendering::Render();

}
