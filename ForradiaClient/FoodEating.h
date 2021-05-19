#pragma once

#include <vector>
#include "Point.h"
#include <SDL2/SDL_timer.h>
#include <memory>
#include "Object.h"

using std::unique_ptr;
using std::vector;

class CActiveFoodItem;

namespace FoodEating
{
	inline vector<CActiveFoodItem> activeFoodItems;
	inline int tickLastUpdate = SDL_GetTicks();

	void EatAppleFromGround(Point p);
	void EatStrawberryFromGround(Point p);
	void Render();
	void Update();
};



class CActiveFoodItem
{
public:
	unique_ptr<Object> m_foodItem;
	int m_tickCreated = 0;

	CActiveFoodItem(unique_ptr<Object> foodItem);
};

