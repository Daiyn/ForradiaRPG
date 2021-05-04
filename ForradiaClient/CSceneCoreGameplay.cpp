#include "CSceneCoreGameplay.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include <memory>

using std::make_unique;

CSceneCoreGameplay::CSceneCoreGameplay()
{
    m_gamingSession = make_unique<CGamingSession>(CGamingSession());
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

    m_gamingSession->Update();

}

void CSceneCoreGameplay::Render()
{

    m_gamingSession->Render();

}
