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
    inline CPoint pMouseDown = { -1, -1 };
    inline bool mouseButtonLeftDown = false;
    inline bool mouseButtonRightDown = false;
    inline bool mouseButtonLeftPressed = false;
    inline bool mouseButtonRightPressed = false;
    inline bool mouseButtonLeftReleased = false;
    inline bool mouseButtonRightReleased = false;
    inline bool mouseDownInGUI = false;

    void CheckMouseClickOnNPCs();
    void DoMouseDown(Uint8 button);
    void DoMouseUp(Uint8 button);
    void ResetEventVariables();
    void Update();
};


#endif
