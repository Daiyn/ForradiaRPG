/*+===================================================================
  File:      MOUSEINPUT.H

  Summary:   Describes free variables and functions for keyboard
             mouse handling.

  Classes:   CPoint

  Functions: DoMouseDown
             DoMouseUp
             CheckMouseClickOnNPCs
             Update
             ResetEventVariables

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_MOUSEINPUT_H
#define FORRADIAFORMATION_MOUSEINPUT_H

#include <SDL2/SDL_stdinc.h>
#include "CPoint.h"

namespace MouseInput
{
    inline CPoint coordMouseDown = { -1, -1 };
    inline bool stateMouseButtonLeftDown = false;
    inline bool stateMouseButtonRightDown = false;
    inline bool stateMouseButtonLeftPressed = false;
    inline bool stateMouseButtonRightPressed = false;
    inline bool stateMouseButtonLeftReleased = false;
    inline bool stateMouseButtonRightReleased = false;
    inline bool stateMouseDownInGUI = false;

    void DoMouseDown(Uint8 button);
    void DoMouseUp(Uint8 button);
    void ResetEventVariables();
    void Update();
};


#endif
