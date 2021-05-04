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

void RenderPlayerActions();

namespace PlayerActions
{
    inline std::vector<SDL_Point> skillAffectedTiles;
    inline CPoint hoveredTile;
    inline int tickStartSkillPerform = 0;
    inline int focusedObjectMapx = -1;
    inline int focusedObjectMapy = -1;
    inline int focusedObjectProgress = 0;
    inline int ticksFocusedObjectProgressIncrease = 0;
    inline int focusedObjectProgressIncreaseSpeed = 300;
    inline int skillElapseDuration = 500;
    inline float xStart;
    inline float yStart;
    inline float dxStep;
    inline float dyStep;
    inline bool skillInAction = false;

    void FocusOnObject(CPoint p);
    void Render();
    void StartPerformSkill();
    void Update();
    void UpdateFocusedObject();
    void UpdateHoveredTile();
    void UpdateSkillsPerformed();
};


#endif
