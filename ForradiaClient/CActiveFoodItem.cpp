#include "CActiveFoodItem.h"
#include "CPoint.h"
#include <SDL2/SDL_timer.h>

using std::move;

CActiveFoodItem::CActiveFoodItem(unique_ptr<CObject> foodItem)
{
	m_foodItem = move(foodItem);
	m_tickCreated = SDL_GetTicks();
}
