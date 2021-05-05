#include "CPoint.h"
#include "Global_Player.h"
#include "Combat.h"
#include "Global_Canvas.h"
#include "Utilities.h"
#include "Global_MapSize.h"
#include <stdlib.h>
#include "CPlayer.h"
#include "Global_CurrentMap.h"
#include "CMap.h"

CPoint::CPoint(int _x, int _y)
{
	m_x = _x;
	m_y = _y;
}

CPoint::CPoint(int flags)
{
	m_x = 0;
	m_y = 0;

	if ((flags & RANDOM_WITHIN_MAP) != 0)
	{
		m_x = rand() % Global::mapSize;
		m_y = rand() % Global::mapSize;
	}

	if ((flags & MAP_CENTER) != 0)
	{
		m_x = Global::mapSize / 2;
		m_y = Global::mapSize / 2;
	}

	if ((flags & HOVERED_TILE) != 0)
	{
		m_x = Utilities::GetHoveredMapx();
		m_y = Utilities::GetHoveredMapy();
	}
}

void CPoint::JumpToHoveredTile()
{

	m_x = Global::player->m_coordPosition.m_x - (Global::GetNumberOfColumns() - 1) / 2 + Utilities::GetHoveredScreenMapx();
	m_y = Global::player->m_coordPosition.m_y - (Global::tilesNumberOfRows - 1) / 2 + Utilities::GetHoveredScreenMapy();

}

void CPoint::JumpToScreenStart()
{
	m_x = XSCREENSTART;
	m_y = YSCREENSTART;
}

void CPoint::JumpRight()
{
	m_x++;
}

void CPoint::JumpToNextRowStart()
{
	m_x = XSCREENSTART;
	m_y++;
}

void CPoint::Translate(int dx, int dy)
{
	m_x += dx;
	m_y += dy;
}

bool CPoint::WithinMap()
{
	return m_x >= 0 && m_y >= 0 && m_x < Global::mapSize && m_y < Global::mapSize;
}

bool CPoint::Equals(CPoint p)
{
	return m_x == p.m_x && m_y == p.m_y;
}

CPoint CPoint::GetAbsDistanceToPlayer()
{
	CFoe& targetedFoe = Global::contentCurrentMap->m_mirrorAllFoes[Combat::idxTargetedFoe];

	CPoint tc;
	tc.m_x = abs(Global::player->m_coordPosition.m_x - targetedFoe.m_coordPosition.m_x);
	tc.m_y = abs(Global::player->m_coordPosition.m_y - targetedFoe.m_coordPosition.m_y);
	return tc;
}
