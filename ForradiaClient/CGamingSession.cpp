#include "CGamingSession.h"
#include "CoreGameRendering.h"
#include "GUI.h"
#include "FoeMovement.h"
#include "ObjectsDecay.h"
#include "CTrain.h"
#include "GUITerminal.h"
#include "GUIStatusPanel.h"
#include "MouseInput.h"
#include "PlayerActions.h"
#include "Combat.h"
#include "GUIWorldMenu.h"
#include "GUISystemMenu.h"
#include "GUICoordPanel.h"
#include "GUIMinimap.h"
#include "Global_Player.h"
#include "Global_SDL.h"
#include "Global_CurrentMap.h"
#include "Global_MapSize.h"
#include "Global_WorldMap.h"
#include "Global_Train.h"
#include "FoeDeathAndRespawnHandling.h"
#include <memory>
#include "CMap.h"
#include "CPlayer.h"
#include "FoodEating.h"

using std::unique_ptr;
using std::move;
using std::make_unique;

CGamingSession::CGamingSession()
{

    Global::statePlayer = make_unique<CPlayer>(CPlayer(Global::tilesMapSize));
    Global::train = make_unique<CTrain>(CTrain());

    //SDL_DestroyTexture(Global::texFullMapOverview);
    //Global::texFullMapOverview = NULL;

    GUITerminal::Print("Welcome to Forradia");

}



void CGamingSession::Update()
{

    MouseInput::Update();
    Global::statePlayer->Update();
    PlayerActions::Update();
    Combat::Update();
    FoeDeathAndRespawnHandling::Update();
    FoeMovement::Update();
    ObjectsDecay::Update();
    Global::train->Update();
    GUI::Update();
    GUISystemMenu::Update();
    GUIWorldMenu::Update();
    Global::contentCurrentMap->UpdateNPCs();
    FoodEating::Update();

}

void CGamingSession::Render()
{

    CoreGameRendering::Render();

}