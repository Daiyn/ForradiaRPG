/*+===================================================================
  File:      PLAYERACTIONS.H

  Summary:   Describing a function and namespace members related to
             timed events on the map, such as player skills and
             crafting actions that take time to perform such as
             chopping down a tree.

  Classes:   CPoint

  Functions: FocusOnObject
             Update
             Render
             UpdateHoveredTile
             StartPerformSkill
             UpdateSkillsPerformed
             UpdateFocusedObject

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_PLAYERACTIONS_H
#define FORRADIAFORMATION_PLAYERACTIONS_H

#include <SDL2/SDL_rect.h>
#include <vector>
#include "CPoint.h"
#include "CTimer.h"

void RenderPlayerActions();

namespace PlayerActions
{
    inline std::vector<SDL_Point> coordsSkillAffectedTiles;
    inline CPoint coordHoveredTile;
    inline int tickStartSkillPerform = 0;
    inline int coordFocusedObjectMapx = -1;
    inline int coordFocusedObjectMapy = -1;
    inline int stateFocusedObjectProgress = 0;
    const int spdFocusedObjectProgressIncrement = 300;
    inline CTimer tmrFocusedObjectProgressIncrease(spdFocusedObjectProgressIncrement);
    inline int timeSkillElapseDuration = 500;
    inline float coordStartX;
    inline float coordStartY;
    inline float coordDxStep;
    inline float coordDyStep;
    inline bool stateSkillInAction = false;

    void FocusOnObject(CPoint p);
    void Render();
    void StartPerformSkill();
    void Update();
    void UpdateFocusedObject();
    void UpdateHoveredTile();
    void UpdateSkillsPerformed();
};


#endif
