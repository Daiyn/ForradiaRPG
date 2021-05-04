/*+===================================================================
  File:      GUI.H

  Summary:   Describes constants, free variables and functions
             related to the GUI in the CoreGameplay scene.

  Classes:   CWindow
             CMap

  Functions: CheckMouseClickInGUI
             HandleMouseClickInGUI
             HandleMouseReleaseInGUI
             Update
             Render

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_GUI_H
#define FORRADIAFORMATION_GUI_H

#include <memory>
#include <vector>
#include "Constants.h"
#include "CWindow.h"

using std::vector;
using std::unique_ptr;

class CMap;

namespace GUI
{
    inline vector<unique_ptr<CWindow>> windows;
    const int NUMBER_OF_BUTTONS = 3;
    const int buttonImages[NUMBER_OF_BUTTONS] = { ID_ICON_INVENTORY, ID_ICON_CRAFTING, ID_ICON_SYSTEM };
    inline int wOrig = 120;

    bool CheckMouseClickInGUI();
    bool HandleMouseClickInGUI();
    bool HandleMouseReleaseInGUI();
    void Render();
    void Update();
};


#endif
