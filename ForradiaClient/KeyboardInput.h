/*+===================================================================
  File:      KEYBOARDINPUT.H

  Summary:   Describes a free variable and functions for keyboard
             input handling.

  Classes:   

  Functions: DoKeyDown
             DoKeyUp

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_KEYBOARDINPUT_H
#define FORRADIACLIENT_KEYBOARDINPUT_H

#include <SDL2/SDL_keycode.h>
#include <map>

namespace KeyboardInput
{
    inline std::map<SDL_Keycode, bool> statesPressedKeys;

    void DoKeyDown(SDL_Keycode key);
    void DoKeyUp(SDL_Keycode key);

};


inline void KeyboardInput::DoKeyDown(SDL_Keycode key)
{
    statesPressedKeys[key] = true;

}

inline void KeyboardInput::DoKeyUp(SDL_Keycode key)
{
    statesPressedKeys[key] = false;
}



#endif //FORRADIACLIENT_KEYBOARDINPUT_H
