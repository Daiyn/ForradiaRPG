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
    inline vector<unique_ptr<CWindow>> activeWindows;
    const int numberOfGUIButtons = 3;
    const int idxsButtonImages[numberOfGUIButtons] = { kIDIconInventory, kIDIconCrafting, kIDIconSystem };
    inline int pxWidthOriginal = 120;

    bool CheckMouseClickInGUI();
    bool HandleMouseClickInGUI();
    bool HandleMouseReleaseInGUI();
    void Render();
    void Update();
};


#endif
