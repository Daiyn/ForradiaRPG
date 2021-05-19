#include "Timer.h"
#include <SDL2/SDL_timer.h>

Timer::Timer(int interval)
{

	m_tickLastUpdate = SDL_GetTicks();
	m_interval = interval;

}

bool Timer::TimeForUpdate()
{

	if (SDL_GetTicks() - m_tickLastUpdate > m_interval)
	{
		m_tickLastUpdate = SDL_GetTicks();
		return true;
	}

	return false;

}