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

#include "Point.h"

namespace Crafting
{

	const int MELTING_FURNACE_NUM_REQ_BRICKS = 3;

	void ChopDownTree(Point p);
	void ChopUpWoodLog(Point p);
	void CreateWoodplank(Point p);
	void CreateWoodfloor(Point p);
	void CreateUnloadedCampfire(Point p);
	void LoadCampfire(Point p);
	void LightCampfire(Point p);
	void DigClay(Point p);
	void CreateBrick(Point p);
	void CreateMeltingFurnace(Point p);
	void LoadMeltingFurnace(Point p);
	void LightMeltingFurnace(Point p);
	void HeatIron(Point p);
	void CreateIronNail(Point p);
	void DigGround(Point p);
	void CreateWoodWallNS(Point p);
	void CreateWoodWallEW(Point p);
	void CreateWoodWallCorner(Point p);
	void HarvestStrawberry(Point p);
};

