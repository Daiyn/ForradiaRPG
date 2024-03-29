/*+===================================================================
  File:      GLOBAL_CURRENTSCENE.H

  Summary:   Describes functions and a free variable related to the
			 scene that the player is currently at.

  Classes:   CScene

  Functions: ChangeScene
			 DestroyCurrentScene

  Origin:    Written by Andreas �kerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include "Global_Gameloop.h"
#include <memory>

using std::unique_ptr;
using std::move;

class Scene;

namespace Global
{
	inline unique_ptr<Scene> stateCurrentScene;

	void ChangeScene(unique_ptr<Scene> newScene);
}


inline void Global::ChangeScene(unique_ptr<Scene> newScene)
{

	stateCurrentScene = move(newScene);
	Global::restartGameLoop = true;

}
