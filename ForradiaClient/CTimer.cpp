#include "CTimer.h"
#include <SDL2/SDL_timer.h>

CTimer::CTimer(int interval)
{

	m_tickLastUpdate = SDL_GetTicks();
	m_interval = interval;

}

bool CTimer::TimeForUpdate()
{

	if (SDL_GetTicks() - m_tickLastUpdate > m_interval)
	{
		m_tickLastUpdate = SDL_GetTicks();
		return true;
	}

	return false;

}