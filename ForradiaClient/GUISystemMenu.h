/*+===================================================================
  File:      GUISYSTEMMENU.H

  Summary:   Describes free variables and functions related to the
             system menu which can shown in the CoreGameplay scene
             and contains menu options which can lead the player to 
             other scenes.

  Classes:   

  Functions: Update
             Show
             HandleMouseClickInSystemMenu
             RenderIfShown

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_SYSTEMMENU_H
#define FORRADIAFORMATION_SYSTEMMENU_H

#include <string>

using std::string;

namespace GUISystemMenu
{
    inline string menuOptions[2] =
    {
            "Main Menu",
            "Return to Game"
    };
    inline bool isShown = false;

    void HandleMouseClickInSystemMenu(bool leftMouseButtonDown);
    void RenderIfShown();
    void Show();
    void Update();
};


#endif //FORRADIAFORMATION_SYSTEMMENU_H
