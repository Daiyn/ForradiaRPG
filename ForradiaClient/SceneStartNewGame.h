/*+===================================================================
  File:      CSCENESTARTNEWGAME.H

  Summary:   Describes class for one of the scenes coming from the
             main menu.

  Classes:   CSceneStartNewGame
             CScene
             CMap

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_SCENE_STARTNEWGAME_H
#define FORRADIAFORMATION_SCENE_STARTNEWGAME_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "Scene.h"
#include "Map.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CSceneStartNewGame

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

class SceneStartNewGame : public Scene
{
public:

    unique_ptr<Map> m_gamedataMap;
    bool m_doGenerateMapPreview = false;
    bool m_isMapGenerated = false;
    const int m_attrBoxBorderThickness = 30;

    SceneStartNewGame();

    void DoMouseDown(Uint8 button);
    void GenerateMapPreview();
    void Render();
    void RenderMapPreview();
    void Update();

protected:

private:

};


#endif //FORRADIAFORMATION_SCENE_STARTNEWGAME_H
