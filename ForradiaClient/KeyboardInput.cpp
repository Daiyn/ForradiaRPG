#include "KeyboardInput.h"
#include "PlayerActions.h"

void KeyboardInput::DoKeyDown(SDL_Keycode key)
{

    statesPressedKeys[key] = true;

    if (key == SDLK_1)
        PlayerActions::StartPerformSkill();

}

void KeyboardInput::DoKeyUp(SDL_Keycode key)
{

    statesPressedKeys[key] = false;

}