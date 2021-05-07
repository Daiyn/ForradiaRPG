/*+===================================================================
  File:      CSCENECOREGAMEPLAY.H

  Summary:   Describes the class representing the main scene in which 
             the player will spend the most of his/her game time.

  Classes:   CSceneCoreGameplay
             CScene
             CGamingSession
             CMap

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_SCENE_ACTUALPLAY_H
#define FORRADIAFORMATION_SCENE_ACTUALPLAY_H

#include "CScene.h"
#include <SDL2/SDL_keycode.h>
#include <memory>

using std::unique_ptr;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CSceneCoreGameplay

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

class CSceneCoreGameplay : public CScene
{
public:


    CSceneCoreGameplay();

    void DoKeyDown(SDL_Keycode key);
    void DoKeyUp(SDL_Keycode key);
    void DoMouseDown(Uint8 button);
    void DoMouseUp(Uint8 button);
    void Render();
    void Update();

protected:

private:

};


#endif
