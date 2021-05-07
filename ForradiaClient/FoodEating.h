#pragma once

#include <vector>
#include "CPoint.h"
#include <SDL2/SDL_timer.h>
#include <memory>
#include "CObject.h"

using std::unique_ptr;
using std::vector;

class CActiveFoodItem;

namespace FoodEating
{
	inline vector<CActiveFoodItem> activeFoodItems;
	inline int tickLastUpdate = SDL_GetTicks();

	void EatAppleFromGround(CPoint p);
	void Render();
	void Update();
};



class CActiveFoodItem
{
public:
	unique_ptr<CObject> m_foodItem;
	int m_tickCreated = 0;

	CActiveFoodItem(unique_ptr<CObject> foodItem);
};

