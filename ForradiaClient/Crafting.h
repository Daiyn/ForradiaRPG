/*+===================================================================
  File:      CRAFTING.H

  Summary:   Describes the (for now hard coded) crafting actions
			 available to the player.

  Classes:   Classes declared or used (in source files).

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include "CPoint.h"

namespace Crafting
{

	const int MELTING_FURNACE_NUM_REQ_BRICKS = 3;

	void ChopDownTree(CPoint p);
	void ChopUpWoodLog(CPoint p);
	void CreateWoodplank(CPoint p);
	void CreateWoodfloor(CPoint p);
	void CreateUnloadedCampfire(CPoint p);
	void LoadCampfire(CPoint p);
	void LightCampfire(CPoint p);
	void DigClay(CPoint p);
	void CreateBrick(CPoint p);
	void CreateMeltingFurnace(CPoint p);
	void LoadMeltingFurnace(CPoint p);
};

