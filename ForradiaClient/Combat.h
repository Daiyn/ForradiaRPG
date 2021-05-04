/*+===================================================================
  File:      COMBAT.H

  Summary:   Describes free varaiables and functions used in foe
             targeting and fighting, that need to be access from many
             different areas.

  Classes:   CFoe

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_COMBAT_H
#define FORRADIAFORMATION_COMBAT_H

#include <stdio.h>


class CFoe;

namespace Combat
{
    inline int idxTargetedFoe = -1;
    inline int tickSelectTarget = 0;
    inline int duraKeepTarget = 700;
    inline int tickCombatInitiated = 0;

    const int duraShowHitEffect = 200;

    bool HandleMouseClickOnFoe();
    void Update();
};


#endif
