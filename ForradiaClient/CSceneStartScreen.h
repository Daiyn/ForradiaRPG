/*+===================================================================
  File:      CSCENESTARTSCREEN.H

  Summary:   Describes the class for the first scene shown when 
             starting the game.

  Classes:   CSceneStartScreen
             CScene

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_SCENE_STARTSCREEN_H
#define FORRADIAFORMATION_SCENE_STARTSCREEN_H

#include "CScene.h"
#include <SDL2/SDL_stdinc.h>

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CSceneStartScreen

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

class CSceneStartScreen : public CScene
{
public:

    void DoMouseDown(Uint8 button);
    void Render();

protected:

private:

};

#endif