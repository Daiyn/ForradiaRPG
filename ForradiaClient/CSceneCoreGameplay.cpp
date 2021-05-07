#include "CSceneCoreGameplay.h"
#include "CoreGameRendering.h"
#include "GUI.h"
#include "AnimalMovement.h"
#include "CTrain.h"
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
#include "Global_Train.h"
#include <memory>
#include "CMap.h"
#include "CPlayer.h"
#include "FoodEating.h"
#include "GameConfiguration.h"
#include "KeyboardInput.h"

using std::make_unique;

CSceneCoreGameplay::CSceneCoreGameplay()
{
    Global::statePlayer = make_unique<CPlayer>(CPlayer(Global::tilesMapSize));
    GameConfiguration::AddPlayerStartingItems();
    Global::defaultTrain = make_unique<CTrain>(CTrain());
}

void CSceneCoreGameplay::DoKeyDown(SDL_Keycode key)
{

    KeyboardInput::DoKeyDown(key);

}

void CSceneCoreGameplay::DoKeyUp(SDL_Keycode key)
{

    KeyboardInput::DoKeyUp(key);

}

void CSceneCoreGameplay::DoMouseDown(Uint8 button)
{

    MouseInput::DoMouseDown(button);

}

void CSceneCoreGameplay::DoMouseUp(Uint8 button)
{

    MouseInput::DoMouseUp(button);

}

void CSceneCoreGameplay::Update()
{

    MouseInput::Update();
    Global::statePlayer->Update();
    PlayerActions::Update();
    AnimalMovement::Update();
    Global::defaultTrain->Update();
    GUI::Update();
    GUISystemMenu::Update();
    GUIWorldMenu::Update();
    Global::contentCurrentMap->UpdateNPCs();
    FoodEating::Update();

}

void CSceneCoreGameplay::Render()
{

    CoreGameRendering::Render();

}
