/*+===================================================================
  File:      CSCENE.H

  Summary:   Describes the base CScene class of which specific scenes
             are inherited, such as the Start scene, MainMenu scene,
             StartNewGame scene and CoreGameplay scene.

  Classes:   CScene

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_SCENE_H
#define FORRADIAFORMATION_SCENE_H

#include <SDL2/SDL_keycode.h>

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CScene

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

class Scene
{
public:

    virtual void DoKeyDown(SDL_Keycode key) {};
    virtual void DoKeyUp(SDL_Keycode key) {};
    virtual void DoMouseDown(Uint8 button) {};
    virtual void DoMouseUp(Uint8 button) {};
    virtual void Render() {};
    virtual void Update() {}

protected:

private:

};


#endif