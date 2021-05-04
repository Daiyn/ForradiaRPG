#pragma once

#include <vector>
#include "CActiveFoodItem.h"
#include "CPoint.h"
#include <SDL2/SDL_timer.h>

using std::vector;

namespace FoodEating
{
	inline vector<CActiveFoodItem> activeFoodItems;
	inline int tickLastUpdate = SDL_GetTicks();

	void EatAppleFromGround(CPoint p);
	void Render();
	void Update();
};

