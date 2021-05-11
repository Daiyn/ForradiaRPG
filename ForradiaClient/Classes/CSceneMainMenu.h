/*+===================================================================
  File:     CSCENEMAINMENU.H

  Summary:   Describes the class representing the second scene in the
             game execution process showing the main menu which in 
             turn leads the player to one of several other scenes, or 
             the exiting of the game.

  Classes:   CSceneMainMenu
             CScene

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_SCENE_MAINMENU_H
#define FORRADIAFORMATION_SCENE_MAINMENU_H

#include <string>
#include <vector>
#include "CScene.h"
#include <SDL2/SDL_stdinc.h>

using std::string;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CSceneMainMenu

  Summary:  Short summary of purpose and content of CMyClass.
            Short summary of purpose and content of CMyClass.

  Methods:  MyMethodOne
              Short description of MyMethodOne.
            MyMethodTwo
              Short description of MyMethodTwo.
            CMyClass
              Constructor.
            ~CMyClass
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

class CSceneMainMenu : public CScene
{
public:

    std::vector<string> m_labelsMenuButtons = { "Start", "Quit" };

    void DoMouseDown(Uint8 button);
    void Render();
    void Update();

protected:

private:

};

#endif