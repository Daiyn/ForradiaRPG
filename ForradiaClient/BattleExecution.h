/*+===================================================================
  File:      BATTLEEXECUTION.H

  Summary:   Describes functions for executing a single battle between
			 Player and a foe which need to be accessed mainly from
			 the combat classs.

  Classes:   CFightableCharacter

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <memory>

using std::unique_ptr;

class CFightableCharacter;

namespace BattleExecution
{
	const int tickCombatSpeed = 30;
	inline int tickLastCombatIteration = 0;

	void HitFightableCharacter(CFightableCharacter& character, int maxDamage);
	void PerformCombat();
};

